#include "ros/ros.h"
#include "std_msgs/String.h"
#include "ardrone_autonomy/Navdata.h"
#include "std_msgs/Float64.h"
#include "geometry_msgs/Twist.h"
#include "cmath"

ros::Publisher pubx;
ros::Publisher puby;
ros::Publisher pubyaw;
ros::Publisher pubz;
ros::Publisher pubnotag;
ros::Subscriber sub;


void chatterCallback(const ardrone_autonomy::Navdata& msg)
{
//  geometry_msgs::Twist zerotwist;
if (msg.tags_count==0)
/*  zerotwist.linear.x = 0.0;
  zerotwist.linear.y = 0.0;
  zerotwist.linear.z = 0.0;
  zerotwist.angular.x = 0.1; // To enable autohover
  zerotwist.angular.y = 0.1; // To enable autohover
  zerotwist.angular.z = 0.0;
	pubnotag.publish(zerotwist);
*/
return;
        std_msgs::Float64 msgx;
        std_msgs::Float64 msgy;
        std_msgs::Float64 msgyaw;
        std_msgs::Float64 msgz;

	double xpos1, ypos1, zpos1;
	double xpos0, ypos0;
	double rotx, roty, rotz;

        msgyaw.data = msg.tags_orientation[0];
        msgz.data = msg.tags_distance[0];

	xpos1 = xpos0 * msgz.data;
	ypos1 = ypos0 * msgz.data;

	rotx = msg.rotX*M_PI/180.0;
	roty = msg.rotY*M_PI/180.0;
	rotz = msg.rotZ*M_PI/180.0;
	double derotx, deroty, derotz, xprime, yprime;

	xprime = msg.tags_distance[0]*sin(rotx - atan((msg.tags_xc[0]-500.0)/878.41)); // the 878.41 is the focal length in the x direction in units of pixels
	yprime = msg.tags_distance[0]*sin(roty - atan((msg.tags_yc[0]-500.0)/917.19)); // the 878.41 is the focal length in the x direction in units of pixels

        msgx.data = xprime;
        msgy.data = yprime;
//	ROS_INFO("x: %f, xprime: %f, rotx %f, tags_xc %d, distance %f\n",msgx.data,xprime, rotx, msg.tags_xc[0], msg.tags_distance[0]);
//	ROS_INFO("tag-500: %f, atan(): %f, rotx-atan: %f, xprime: %f",((msg.tags_xc[0]-500.0)/878.4),atan((msg.tags_xc[0]-500.0)/878.4), (rotx-atan((msg.tags_xc[0]-500)/878.4)), xprime);
	ROS_INFO("xprime %f, y: %f, yprime: %f\n", xprime, msgy.data, yprime); 
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
//  pubnotag = n.advertise<geometry_msgs::Twist>("/notag_zerotwist",1000);

  sub = n.subscribe("/ardrone/navdata", 1000, chatterCallback);

  ros::spin();
  return 0;
}
