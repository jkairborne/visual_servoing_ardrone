#include "ros/ros.h"
#include "std_msgs/String.h"
#include "ar_track_alvar_msgs/AlvarMarkers.h"
#include "std_msgs/Float64.h"
#include "publ_subs/test.h"

void chatterCallback(const &msg); /* prototype */

  ros::init(argc, argv, "listener");
  ros::NodeHandle n;



int main(int argc, char **argv)
{

  ros::init(argc, argv, "listener");
  ros::NodeHandle n;
  ros::Subscriber sub = n.subscribe("/ar_pose_marker", 1000, chatterCallback);

  ros::spin();

  return 0;
}


void chatterCallback(const ar_track_alvar_msgs::AlvarMarkers& msg)
{

ROS_INFO("I heard: [%f]", msg.markers[0].pose.pose.orientation.x);

ros::Publisher chatter_pub = n.advertise<std_msgs::Float64>("cmd_vel2", 1000);
ros::Rate loop_rate(100);
  while (ros::ok())
	{
	std_msgs::Float64 pubmsg;
	pubmsg.data = msg.markers[0].pose.pose.orientation.x;
	ROS_INFO("We are rebroadcasting to cmd_vel2: %f", pubmsg);
	chatter_pub.publish(pubmsg);
	ros::spinOnce;
	}
}


