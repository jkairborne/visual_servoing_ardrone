#include <ros/ros.h>
#include <std_msgs/Float64.h>
#include <geometry_msgs/Twist.h>

geometry_msgs::Twist vs_output;

ros::Publisher pub;

void callbackx(const std_msgs::Float64& input1)
{
  vs_output.linear.y = input1.data;
  pub.publish(vs_output);
}


void callbacky(const std_msgs::Float64& input2)
{
  vs_output.linear.x = input2.data;
  pub.publish(vs_output);
}

void callbackz(const std_msgs::Float64& input3)
{
  vs_output.linear.z = input3.data;
  pub.publish(vs_output);
}


void callbackyaw(const std_msgs::Float64& input4)
{
  vs_output.angular.z = input4.data;
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

  subx = nh.subscribe("/ArDrone_pid_x/vs_output_x", 1000, callbackx);
  suby = nh.subscribe("/ArDrone_pid_y/vs_output_y", 1000, callbacky);
  subz = nh.subscribe("/ArDrone_pid_z/vs_output_z", 1000, callbackz);
  subyaw = nh.subscribe("/ArDrone_pid_yaw/vs_output_yaw", 1000, callbackyaw);


  ros::spin();

  return 0;
}
