#include "ros/ros.h"
#include "std_msgs/String.h"
#include "ar_track_alvar_msgs/AlvarMarkers.h"
#include "std_msgs/Float64.h"
#include "geometry_msgs/Quaternion.h"
#include "tf/transform_datatypes.h"
#include "tf/transform_listener.h"

#include "geometry_msgs/Vector3.h"
#include "geometry_msgs/Quaternion.h"


int main(int argc, char** argv){
  ros::init(argc, argv, "my_tf_listener");

  ros::NodeHandle node;

  ros::Publisher posex = node.advertise<std_msgs::Float64>("/pose_x", 10);
  ros::Publisher posey = node.advertise<std_msgs::Float64>("/pose_y", 10);
  ros::Publisher posez = node.advertise<std_msgs::Float64>("/pose_z", 10);

  ros::Publisher posequat = node.advertise<std_msgs::Float64>("/yaw_angle", 10);

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
/*
    ros::Time zxc = transform.stamp_;
    if ((ros::Time::now().toSec() - zxc.toSec())<5.0)
    {
    ROS_INFO("seems the timestamp was %f",zxc.toSec());

    ROS_INFO("we made it into the if statement!");    
    }//endif
*/

    std_msgs::Float64 msgx, msgy, msgz, yawmsg;
    tf::Quaternion tfquat;
    msgy.data = transform.getOrigin().y();
    msgx.data = transform.getOrigin().x();
    msgz.data = transform.getOrigin().z();
    tfquat = transform.getRotation();

    double roll, pitch, yaw;
    tf::Matrix3x3(tfquat).getRPY(roll, pitch, yaw);

    posex.publish(msgx);
    posey.publish(msgy);
    posez.publish(msgz);
    yawmsg.data = yaw;
    posequat.publish(yawmsg);

    rate.sleep();
  }
  return 0;
};
