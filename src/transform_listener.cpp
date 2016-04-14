#include "ros/ros.h"
#include "std_msgs/String.h"
#include "ar_track_alvar_msgs/AlvarMarkers.h"
#include "std_msgs/Float64.h"
#include "geometry_msgs/Quaternion.h"
#include "tf/transform_datatypes.h"
#include "tf/transform_listener.h"

bool arpose = false;

void publishitall()
{
  tf::TransformListener listener;

tf::StampedTransform transform;
    try{
      listener.lookupTransform("/odom", "/ardrone_base_bottomcam",
                               ros::Time(0), transform);
        ROS_INFO("I made it past the lookuptransform");
    }
    catch (tf::TransformException ex){
      ROS_ERROR("%s",ex.what());
      ros::Duration(1.0).sleep();
    }

}//end publishitall

void arpose_callback(const ar_track_alvar_msgs::AlvarMarkers& msg) 
{
if (msg.markers.size()==0){
	arpose == false;
	ROS_INFO("setting arpose to false");
	} //end if
else{
	arpose == true;
	ROS_INFO("setting arpose to true");
	publishitall();	
	} //end else
}//end arpose_callback


int main(int argc, char** argv){
  ros::init(argc, argv, "my_tf_listener");

  ros::NodeHandle nh;


  ros::Publisher cmdx = 
    nh.advertise<std_msgs::Float64>("/pose_c", 10);

  tf::TransformListener listener;

  ros::Rate rate(10.0);
  while (nh.ok()){
  ros::Subscriber sub = nh.subscribe("/ar_pose_marker", 1, arpose_callback);
    tf::StampedTransform transform;
    try{
      listener.lookupTransform("/ardrone_base_bottomcam", "/ar_marker_0",  
                               ros::Time(0), transform);
	ROS_INFO("I made it past the lookuptransform");
    }
    catch (tf::TransformException ex){
      ROS_ERROR("%s",ex.what());
      ros::Duration(1.0).sleep();
    }
    if (arpose == true){
	ROS_INFO("We made it into the true loop");
	} //end if
    else{
	ROS_INFO("We made it into the false loop");
	} //end else

	ROS_INFO("I made it to the end");
    ros::spin();
    rate.sleep();
  }
  return 0;
};
