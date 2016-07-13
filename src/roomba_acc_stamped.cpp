#include "ros/ros.h"
#include "geometry_msgs/TwistStamped.h"
#include "ros/time.h"
#include <math.h>
#include <sstream>
#include "visual_servoing_ardrone/StampedFloat.h"

ros::Publisher pub;
float oldvel, newvel;
ros::Time oldtime, newtime;
ros::Duration timediff;

void callbackacc(const geometry_msgs::TwistStamped& velcmd)
{
	visual_servoing_ardrone::StampedFloat acc;
	oldvel = newvel;
	newvel = velcmd.twist.linear.x;
	oldtime = newtime;
	newtime = velcmd.header.stamp;
	timediff = newtime - oldtime;
	acc.num = (newvel - oldvel)/timediff.toSec();
	ROS_INFO("old and new vel: %f %f, times: %d %d %d %d, timediff: %f acc: %f", oldvel, newvel, oldtime.sec, oldtime.nsec, newtime.sec, newtime.nsec, timediff.toSec(), acc.num);
	acc.imgtime = newtime;
	pub.publish(acc);
} //end callbackacc

int main(int argc, char **argv)
{
  ros::init(argc, argv, "acceleration");
  ros::NodeHandle n;

  pub = n.advertise<visual_servoing_ardrone::StampedFloat>("/acc_roomba", 1000);
	
  ros::Subscriber roomba_vel;
  newtime = ros::Time::now();
  roomba_vel  = n.subscribe("/cmd_vel_roomba", 1000, callbackacc);

  ros::Rate loop_rate(100);

  ros::spin();
//  ros::spinOnce();

//  loop_rate.sleep();

  return 0;
}
