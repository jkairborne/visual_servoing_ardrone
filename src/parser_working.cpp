#include "ros/ros.h"
#include "std_msgs/String.h"
#include "ar_track_alvar_msgs/AlvarMarkers.h"
#include "std_msgs/Float64.h"
#include "publ_subs/test.h"
#include "geometry_msgs/Vector3.h"
#include "geometry_msgs/Quaternion.h"
#include "tf/transform_datatypes.h"
#include "tf/transform_listener.h"

ros::Publisher pubx;
ros::Publisher puby;
ros::Publisher pubz;
ros::Publisher pubquat;

ros::Subscriber sub;

void chatterCallback(const ar_track_alvar_msgs::AlvarMarkers& msg)
{
ROS_INFO("I here");
if (msg.markers.size()==0)
return;

ROS_INFO("I heard: [%f]", msg.markers[0].pose.pose.position.x);

        std_msgs::Float64 msgx;
        std_msgs::Float64 msgy;
        std_msgs::Float64 msgz;
        geometry_msgs::Quaternion msgquat;
        msgx.data = msg.markers[0].pose.pose.position.x/msg.markers[0].pose.pose.position.z;
        msgy.data = msg.markers[0].pose.pose.position.y/msg.markers[0].pose.pose.position.z;
        msgz.data = msg.markers[0].pose.pose.position.z;
        msgquat = msg.markers[0].pose.pose.orientation;
        ROS_INFO("%f", msgx.data);

       pubx.publish(msgx);
       puby.publish(msgy);
       pubz.publish(msgz);
       pubquat.publish(msgquat);
   	ros::Rate loop_rate(10);
	ros::spinOnce();
	loop_rate.sleep(); 
  }

int main(int argc, char **argv)
{
  ros::init(argc, argv, "listener");
  ros::NodeHandle n;

  pubx = n.advertise<std_msgs::Float64>("/pose_x",1000);
  puby = n.advertise<std_msgs::Float64>("/pose_y",1000);
  pubz = n.advertise<std_msgs::Float64>("/pose_z",1000);
  pubquat = n.advertise<geometry_msgs::Quaternion>("/pose_quat",1000);

  sub = n.subscribe("/ar_pose_marker", 1000, chatterCallback);

  ros::spin();
  return 0;
}
