#include "ros/ros.h"
#include "std_msgs/Float64.h"
#include "geometry_msgs/Twist.h"
#include <math.h>
#include <sstream>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "sinusoidal");

  ros::NodeHandle n;

  ros::Publisher spt_x = n.advertise<std_msgs::Float64>("/spt_x", 1000);
  ros::Publisher spt_y = n.advertise<std_msgs::Float64>("/spt_y", 1000);
  ros::Publisher spt_z = n.advertise<std_msgs::Float64>("/spt_z", 1000);
  ros::Publisher spt_yaw = n.advertise<std_msgs::Float64>("/spt_yaw", 1000);

  ros::Rate loop_rate(100);

  int count = 0;
  while (ros::ok())
  {
    std_msgs::Float64 msgx;
    std_msgs::Float64 msgy;
    std_msgs::Float64 msgz;
    std_msgs::Float64 msgyaw;
    float cmdx = 500;
    float cmdy = 500;
    float cmdz = 120;
    float cmdyaw = 270;
    msgx.data = cmdx;
    msgy.data = cmdy;
    msgz.data = cmdz;
    msgyaw.data = cmdyaw;
    
    ROS_INFO("we have received %f, cmdy as %f, cmdz as %f, count %d", cmdy, cmdy, cmdz, count);

    spt_x.publish(msgx);
    spt_y.publish(msgy);
    spt_z.publish(msgz);
    spt_yaw.publish(msgz);
    ros::spinOnce();

    loop_rate.sleep();
    ++count;
  }

  return 0;
}
