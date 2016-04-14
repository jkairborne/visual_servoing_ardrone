#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <geometry_msgs/Twist.h>
#include <turtlesim/Spawn.h>
#include "ar_track_alvar_msgs/AlvarMarkers.h"

int main(int argc, char** argv){
  ros::init(argc, argv, "my_tf_listener");

  ros::NodeHandle node;

  ros::Publisher turtle_vel =
    node.advertise<geometry_msgs::Twist>("turtle2/cmd_vel", 10);

  tf::TransformListener listener;

  ros::Rate rate(10.0);
  while (node.ok()){
    tf::StampedTransform transform;
    try{
      ros::Time now = ros::Time::now();
      listener.lookupTransform("/odom", "/ar_marker_0",
                               ros::Time(0), transform);
    }
    catch (tf::TransformException &ex) {
      ROS_ERROR("%s",ex.what());
      ros::Duration(1.0).sleep();
      continue;
    }
    ros::Time zxc = transform.stamp_;
/*
    if ((ros::Time::now().toSec() - zxc.toSec())<5.0)
    {
    ROS_INFO("seems the timestamp was %f",zxc.toSec());

    ROS_INFO("we made it into the if statement!");    
    }//endif
*/

    ROS_INFO("timestamp, %f. Time, %f",zxc.toSec(), ros::Time::now().toSec());

    geometry_msgs::Twist vel_msg;
    vel_msg.linear.y = transform.getOrigin().y();
    vel_msg.linear.x = transform.getOrigin().x();
    vel_msg.linear.z = transform.getOrigin().z();
    turtle_vel.publish(vel_msg);
    ROS_INFO("just about to go to sleep");
    rate.sleep();
  }
  return 0;
};
