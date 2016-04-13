#include <ros/ros.h>
#include <tf/transform_listener.h>

int main(int argc, char** argv){
  ros::init(argc, argv, "my_tf_listener");

  ros::NodeHandle node;
/*
  ros::service::waitForService("spawn");
  ros::ServiceClient add_turtle = 
    node.serviceClient<turtlesim::Spawn>("spawn");
  turtlesim::Spawn srv;
  add_turtle.call(srv);

  ros::Publisher turtle_vel = 
    node.advertise<turtlesim::Velocity>("turtle2/command_velocity", 10);
*/
  tf::TransformListener listener;

  ros::Rate rate(10.0);
  while (node.ok()){
    tf::StampedTransform transform;
    try{
      listener.lookupTransform("/ardrone_base_bottomcam", "/ar_marker_0",  
                               ros::Time(0), transform);
	ypos = transform.getOrigin().y();
	xpos = transform.getOrigin().x();
	ROS_INFO("I see the transform x is %f and the y is %f",xpos,ypos);
    }
    catch (tf::TransformException ex){
      ROS_ERROR("%s",ex.what());
      ros::Duration(1.0).sleep();
    }

    rate.sleep();
  }
  return 0;
};
