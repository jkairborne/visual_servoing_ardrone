#include "ros/ros.h"
#include "std_msgs/String.h"
#include "ar_track_alvar_msgs/AlvarMarkers.h"
#include "std_msgs/Float64.h"
#include "publ_subs/test.h"
#include "geometry_msgs/Vector3.h"
#include "geometry_msgs/Quaternion.h"
#include "tf/transform_datatypes.h"

ros::Subscriber sub;

void chatterCallback(const ar_track_alvar_msgs::AlvarMarkers& msg)
{
        double msgx;
        double msgy;
        double msgz;
        msgx = msg.markers[0].pose.pose.position.x;
        msgy = msg.markers[0].pose.pose.position.y;
        msgz = msg.markers[0].pose.pose.position.z;
	tf::Quaternion quat;
	tf::quaternionMsgToTF(msg.markers[0].pose.pose.orientation, quat);
	double roll, pitch, yaw;
        tf::Matrix3x3(quat).getRPY(roll, pitch, yaw);

ROS_INFO("x: %f", msg.markers[0].pose.pose.position.x);
ROS_INFO("y: %f", msg.markers[0].pose.pose.position.y);
ROS_INFO("z: %f", msg.markers[0].pose.pose.position.z);
ROS_INFO("roll:   %f", roll);
ROS_INFO("pitch:  %f", pitch);
ROS_INFO("yaw:    %f", yaw);
   	ros::Rate loop_rate(10);
	ros::spinOnce();
	loop_rate.sleep(); 
  }




int main(int argc, char **argv)
{
  ros::init(argc, argv, "listener");

  ros::NodeHandle n;

  sub = n.subscribe("/ar_pose_marker", 1000, chatterCallback);

  ros::spin();

  return 0;
}
