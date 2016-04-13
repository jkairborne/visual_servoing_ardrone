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

int main(int argc, char** argv){
  ros::init(argc, argv, "my_tf_listener");

  ros::NodeHandle node;
  tf::TransformListener listener;
  
  pubx = node.advertise<std_msgs::Float64>("/pose_x",1000);
  puby = node.advertise<std_msgs::Float64>("/pose_y",1000);
  pubz = node.advertise<std_msgs::Float64>("/pose_z",1000);
  pubquat = node.advertise<geometry_msgs::Quaternion>("/pose_quat",1000);

  ros::Rate rate(10.0);
  while (node.ok()){
    tf::StampedTransform transform;
    try{
      listener.lookupTransform("/ar_marker_0", "/ardrone_base_bottomcam",  
                               ros::Time(0), transform);
	std_msgs::Float64 ypos, xpos, zpos;
	tf::Quaternion tfquat;
	geometry_msgs::Quaternion quat;
	ypos.data = transform.getOrigin().y();
	xpos.data = transform.getOrigin().x();
	zpos.data = transform.getOrigin().z();
	tfquat = transform.getRotation();
	tf::quaternionTFToMsg(tfquat, quat); 
	ROS_INFO("I see the transform x is %f and the y is %f",xpos.data,ypos.data);
	pubx.publish(xpos);
       puby.publish(ypos);
       pubz.publish(zpos);
       pubquat.publish(quat);
    }
    catch (tf::TransformException ex){
      ROS_ERROR("%s",ex.what());
      ros::Duration(1.0).sleep();
    }

    rate.sleep();
  }
  return 0;
};
