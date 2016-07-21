#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "std_msgs/Float64.h"
#include <math.h>
#include <sstream>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "roomba_vel");

  ros::NodeHandle n;

  ros::Publisher cmd_to_roomba = n.advertise<geometry_msgs::Twist>("/cmd_vel_mux/input/teleop", 1000);
  ros::Publisher cmdxvel = n.advertise<std_msgs::Float64>("/roomba_vel_x", 1000);

  ros::Rate loop_rate(100);

  int count = 0;
  while (ros::ok())
  {
    geometry_msgs::Twist cmdvel;
    std_msgs::Float64 xvel_control;
//    float cmdx = 1*sin(count/100.0);
    float cmdx = 0.5*sin(count/100.0);
    float cmdz = 0.000;
    cmdvel.linear.x = cmdx;
    cmdvel.angular.z = cmdz;
    xvel_control.data = cmdx;
//    cmdvel.header.stamp = ros::Time::now();
//    cmdvel.header.stamp.nsec = count;
//    cmdvel.header.stamp.sec = count;  
  
//    ROS_INFO("we have received %i and %i, %i", cmdvel.header.stamp.sec, cmdvel.header.stamp.nsec, count);

    ROS_INFO("we have received %f and %f, %i", cmdvel.linear.x, cmdvel.angular.z, count);

    cmd_to_roomba.publish(cmdvel);
    cmdxvel.publish(xvel_control);
    ros::spinOnce();

    loop_rate.sleep();
    ++count;
  }

  return 0;
}
