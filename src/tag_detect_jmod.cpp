#include "ros/ros.h"
#include "std_msgs/String.h"
#include "ardrone_autonomy/Navdata.h"
#include "std_msgs/Float64.h"
#include "visual_servoing_ardrone/StampedFloat.h"
#include "cmath"

ros::Publisher pubx;
ros::Publisher puby;
ros::Publisher pubyaw;
ros::Publisher pubz;
ros::Subscriber sub;

// These values will be global, which means we could have problems for the first three values at times (i.e. when target is lost for a while then re-acquired);
double xold2, xold3, yold2, yold3;

void chatterCallback(const ardrone_autonomy::Navdata& msg)
{
if (msg.tags_count==0)
return;
        visual_servoing_ardrone::StampedFloat msgx;
        visual_servoing_ardrone::StampedFloat msgy;
        visual_servoing_ardrone::StampedFloat msgyaw;
        visual_servoing_ardrone::StampedFloat msgz;

	double xpos1, ypos1, zpos1;
	double xpos0, ypos0;
	double rotx, roty, rotz;


	xpos1 = xpos0 * msg.tags_distance[0];
	ypos1 = ypos0 * msg.tags_distance[0];

	rotx = msg.rotX*M_PI/180.0;
	roty = msg.rotY*M_PI/180.0;
	rotz = msg.rotZ*M_PI/180.0;
	double derotx, deroty, derotz, xprime, yprime;

	xprime = msg.tags_distance[0]*sin(rotx - atan((msg.tags_xc[0]-500.0)/878.41)); // the 878.41 is the focal length in the x direction in units of pixels
	yprime = msg.tags_distance[0]*sin(roty - atan((msg.tags_yc[0]-500.0)/917.19)); // the 878.41 is the focal length in the x direction in units of pixels

	msgx.imgtime = msg.header.stamp;
	msgy.imgtime = msg.header.stamp;
	msgyaw.imgtime = msg.header.stamp;
	msgz.imgtime = msg.header.stamp;

	xold3 = xold2;
	yold3 = yold2;
	xold2 = xprime;
	yold2 = yprime;

	if (((ros::Time::now().toSec() - msg.header.stamp.sec)) > 1.0){
        	msgx.num = xprime;
        	msgy.num = yprime;
		ROS_INFO("Made it into the if statement!");
	} // end if
	else{
		msgx.num = (xprime + xold2 + xold3)/3.0;
		msgy.num = (yprime + yold2 + yold3)/3.0;
		ROS_INFO("Made it into the else");	
	} //end else 
 ROS_INFO("%f %f %f: %f  ; %f %f %f: %f", xprime, xold2, xold3, msgx.num, yprime, yold2, yold3, msgy.num);
       msgyaw.num = msg.tags_orientation[0];
       msgz.num = msg.tags_distance[0];


	

//	ROS_INFO("x: %f, xprime: %f, rotx %f, tags_xc %d, distance %f\n",msgx.data,xprime, rotx, msg.tags_xc[0], msg.tags_distance[0]);
//	ROS_INFO("tag-500: %f, atan(): %f, rotx-atan: %f, xprime: %f",((msg.tags_xc[0]-500.0)/878.4),atan((msg.tags_xc[0]-500.0)/878.4), (rotx-atan((msg.tags_xc[0]-500)/878.4)), xprime);
	ROS_INFO("xprime %f, y: %f, yprime: %f\n", xprime, msgy.num, yprime); 
        pubx.publish(msgx);
        puby.publish(msgy);
        pubyaw.publish(msgyaw);
        pubz.publish(msgz);

   	ros::Rate loop_rate(250);
	ros::spinOnce();
	loop_rate.sleep(); 
  }

int main(int argc, char **argv)
{
  ros::init(argc, argv, "listener");
  ros::NodeHandle n;

  pubx = n.advertise<visual_servoing_ardrone::StampedFloat>("/pose_x",1000);
  puby = n.advertise<visual_servoing_ardrone::StampedFloat>("/pose_y",1000);
  pubyaw = n.advertise<visual_servoing_ardrone::StampedFloat>("/pose_yaw",1000);
  pubz = n.advertise<visual_servoing_ardrone::StampedFloat>("/pose_z",1000);

  sub = n.subscribe("/ardrone/navdata", 1000, chatterCallback);

  ros::spin();
  return 0;
}
