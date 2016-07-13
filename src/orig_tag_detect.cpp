#include "ros/ros.h"
#include "std_msgs/String.h"
#include "ardrone_autonomy/Navdata.h"
#include "std_msgs/Float64.h"
#include "cmath"

ros::Publisher pubx;
ros::Publisher puby;
ros::Publisher pubyaw;
ros::Publisher pubz;
ros::Subscriber sub;

void chatterCallback(const ardrone_autonomy::Navdata& msg)
{
if (msg.tags_count==0)
return;
        std_msgs::Float64 msgx;
        std_msgs::Float64 msgy;
        std_msgs::Float64 msgyaw;
        std_msgs::Float64 msgz;

	double xpos1, ypos1, zpos1;
	double xpos0, ypos0;
	double rotx, roty, rotz;

/*
        xpos1 = (msg.tags_xc[0]-500)/1000;
        ypos1 = (msg.tags_yc[0]-500)/1000;
        msgyaw.data = msg.tags_orientation[0];
        zpos1 = msg.tags_distance[0];
*/

        msgx.data = (msg.tags_xc[0]-500.0)/1000.0;
        msgy.data = (msg.tags_yc[0]-500.0)/1000.0;

/*
        xpos0 = (msg.tags_xc[0]-500.0)/1000.0;
        ypos0 = (msg.tags_yc[0]-500.0)/1000.0;
*/

        msgyaw.data = msg.tags_orientation[0];
        msgz.data = msg.tags_distance[0];

	xpos1 = xpos0 * msgz.data;
	ypos1 = ypos0 * msgz.data;

	rotx = msg.rotX*M_PI/180;
	roty = msg.rotY*M_PI/180;
	rotz = msg.rotZ*M_PI/180;
	double derotx, deroty, derotz;

/*
  msgx.data = (cos(rotz)*cos(roty))*xpos1 - cos(roty)*sin(rotz)*ypos1 + sin(roty)*zpos1;
  msgy.data =  (cos(rotx)*sin(rotz) + cos(rotz)*sin(roty)*sin(rotx))*xpos1 + (cos(rotz)*cos(rotx) - sin(rotz)*sin(roty)*sin(rotx))*ypos1 - cos(roty)*sin(rotx)*zpos1;

  msgz.data = (sin(rotz)*sin(rotx) - cos(rotz)*cos(rotx)*sin(roty))*xpos1 + (cos(rotz)*sin(rotx) + cos(rotx)*sin(rotz)*sin(roty))*ypos1 + cos(roty)*cos(rotx)*zpos1;
*/

/*
	double random2 = cos(rotx);
	ROS_INFO("%f %f %f", rotx, roty, random2); 
*/
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

  pubx = n.advertise<std_msgs::Float64>("/pose_x",1000);
  puby = n.advertise<std_msgs::Float64>("/pose_y",1000);
  pubyaw = n.advertise<std_msgs::Float64>("/pose_yaw",1000);
  pubz = n.advertise<std_msgs::Float64>("/pose_z",1000);

  sub = n.subscribe("/ardrone/navdata", 1000, chatterCallback);

  ros::spin();
  return 0;
}



/*
  msgx.data = (cos(rotz)*cos(roty))*xpos1 + (cos(rotz)*sin(roty)*sin(rotx)-sin(rotz)*cos(rotx))*ypos1 + (cos(rotz)*sin(roty)*cos(rotx)+sin(rotz)*sin(rotx))*zpos1;
  msgy.data = sin(rotz)*cos(roty)*xpos1 + (sin(rotz)*sin(roty)*sin(rotx)+cos(rotz)*cos(rotx))*ypos1 + (sin(rotz)*sin(roty)*cos(rotx)-cos(rotz)*sin(rotx))*zpos1;
  msgz.data = -sin(roty)*xpos1+cos(roty)*sin(rotx)*ypos1+cos(roty)*cos(rotx)*zpos1;	
*/
