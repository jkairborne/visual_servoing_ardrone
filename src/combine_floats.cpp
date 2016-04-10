#include <ros/ros.h>
#include <std_msgs/Float64.h>
#include <geometry_msgs/Twist.h>

geometry_msgs::Twist vs_output;


void callbackx(const std_msgs::Float64& input1)
{
  vs_output.linear.x = input1.data;
}


void callbacky(const std_msgs::Float64& input2)
{
  vs_output.linear.y = input2.data;
}

void callbackz(const std_msgs::Float64& input3)
{
  vs_output.linear.z = input3.data;
}


void callbackyaw(const std_msgs::Float64& input4)
{
  vs_output.angular.z = input4.data;
}



int main(int argc, char** argv)
{
  
  vs_output.linear.x = 0.0;
  vs_output.linear.y = 0.0;
  vs_output.linear.z = 0.0;
  vs_output.angular.x = 0.1; // to prevent auto-hover mode
  vs_output.angular.y = 0.1; // to prevent auto-hover mode
  vs_output.angular.z = 0.0;


  ros::init(argc, argv, "combination_node");



  ros::NodeHandle nh;
  ros::Subscriber subx;
  ros::Subscriber suby;
  ros::Subscriber subz;
  ros::Subscriber subyaw;

  subx = nh.subscribe("vs_output_x", 1000, callbackx);
  suby = nh.subscribe("vs_output_y", 1000, callbacky);
  subz = nh.subscribe("vs_output_z", 1000, callbackz);
  subyaw = nh.subscribe("yaw_angle", 1000, callbackyaw);

  ros::Publisher pub;
  pub = nh.advertise<geometry_msgs::Twist>("/vs_output",1000);

  ros::spin();

  return 0;
}
