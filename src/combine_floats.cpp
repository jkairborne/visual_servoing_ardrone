#include <ros/ros.h>
#include <std_msgs/Float64.h>
#include <geometry_msgs/Twist.h>
#include <visual_servoing_ardrone/StampedFloat.h>
#include <ros/time.h>

geometry_msgs::Twist vs_output;
ros::Time lasttime;

ros::Publisher pub;
// ros::Publisher pubtime;

void callbackx(const visual_servoing_ardrone::StampedFloat& input1)
{
  vs_output.linear.y = input1.num;
  pub.publish(vs_output);
  lasttime = input1.imgtime;
//  pubtime.publish(lasttime);
  ROS_INFO("I have made it into callback x, now publishing time %i", lasttime.nsec);
}



void callbacky(const visual_servoing_ardrone::StampedFloat& input2)
{
  vs_output.linear.x = input2.num;
  pub.publish(vs_output);
}

void callbackz(const visual_servoing_ardrone::StampedFloat& input3)
{
  vs_output.linear.z = input3.num;
  pub.publish(vs_output);
}


void callbackyaw(const visual_servoing_ardrone::StampedFloat& input4)
{
  vs_output.angular.z = input4.num;
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
//  pubtime = nh.advertise<ros::Time>("/something",1000);

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
