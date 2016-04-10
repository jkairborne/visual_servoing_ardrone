#include <ros/ros.h>
#include <std_msgs/Float64.h>
#include <geometry_msgs/Twist.h>

geometry_msgs::Twist vs123456;


void callbackx(const std_msgs::Float64& input1)
{
  vs123456.linear.x = input1.data;
}


void callbacky(const std_msgs::Float64& input2)
{
  vs123456.linear.y = input2.data;
}

void callbackz(const std_msgs::Float64& input3)
{
  vs123456.linear.z = input3.data;
}


void callbackyaw(const std_msgs::Float64& input4)
{
  vs123456.angular.z = input4.data;
}



int main(int argc, char** argv)
{
  
  vs123456.linear.x = 0.0;
  vs123456.linear.y = 0.0;
  vs123456.linear.z = 0.0;
  vs123456.angular.x = 0.1; // to prevent auto-hover mode
  vs123456.angular.y = 0.1; // to prevent auto-hover mode
  vs123456.angular.z = 0.0;


  ros::init(argc, argv, "combination_node");



  ros::NodeHandle nh;
  ros::Subscriber subx;
  ros::Subscriber suby;
  ros::Subscriber subz;
  ros::Subscriber subyaw;

  subx = nh.subscribe("/vs123456_x", 1000, callbackx);
  suby = nh.subscribe("/vs123456_y", 1000, callbacky);
  subz = nh.subscribe("/vs123456_z", 1000, callbackz);
  subyaw = nh.subscribe("/yaw_angle", 1000, callbackyaw);

  ros::Publisher pub;
  pub = nh.advertise<geometry_msgs::Twist>("/vs123456",1000);

  ros::spin();

  return 0;
}
