#include <ros/ros.h>
#include <std_msgs/Float64.h>
#include <geometry_msgs/Twist.h>

geometry_msgs::Twist vs_output;

ros::Publisher pub;




void callbackz(const std_msgs::Float64& input3)
{
  vs_output.linear.z = input3.data;
  pub.publish(vs_output);
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

  pub = nh.advertise<geometry_msgs::Twist>("/vs_output",1000);

  ros::Subscriber subx;
  ros::Subscriber suby;
  ros::Subscriber subz;
  ros::Subscriber subyaw;

  subz = nh.subscribe("/ArDrone_pid_z/vs_output_z", 1000, callbackz);

  ros::spin();

  return 0;
}
