#include "ros/ros.h"
#include "geometry_msgs/TwistStamped.h"
#include <math.h>
#include <sstream>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "vel_roomba");

  ros::NodeHandle n;

  ros::Publisher cmd2 = n.advertise<geometry_msgs::TwistStamped>("/cmd_vel_roomba", 1000);

  ros::Rate loop_rate(100);

  int count = 0;
  while (ros::ok())
  {
    geometry_msgs::TwistStamped cmdvel;
//    float cmdx = 1*sin(count/100.0);
    float cmdx = sin(count/50.0);
    float cmdz = 0.000;
    cmdvel.twist.linear.x = cmdx;
    cmdvel.twist.angular.z = cmdz;
    cmdvel.header.stamp = ros::Time::now();
//    cmdvel.header.stamp.nsec = count;
  //  cmdvel.header.stamp.sec = count;  
  
    ROS_INFO("we have received %i and %i, %i", cmdvel.header.stamp.sec, cmdvel.header.stamp.nsec, count);

    cmd2.publish(cmdvel);
    ros::spinOnce();

    loop_rate.sleep();
    ++count;
  }

  return 0;
}
