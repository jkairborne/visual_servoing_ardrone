#include "ros/ros.h"
#include "std_msgs/String.h"
#include "visual_servoing_ardrone/StampedFloat.h"

#include <sstream>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "talker");

  ros::NodeHandle n;

  ros::Publisher chatter_pub = n.advertise<visual_servoing_ardrone::StampedFloat>("chatter", 1000);

  ros::Rate loop_rate(10);

  int count = 0;
  while (ros::ok())
  {
    visual_servoing_ardrone::StampedFloat msg;

    msg.imgtime = ros::Time::now();
    msg.num = count;

    ROS_INFO("%f", msg.num);

    chatter_pub.publish(msg);

    ros::spinOnce();

    loop_rate.sleep();
    ++count;
  }


  return 0;
}
