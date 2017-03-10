#include "ros/ros.h"
#include "geometry_msgs/TransformStamped.h"
#include <math.h>



int main(int argc, char **argv)
{

  ros::init(argc, argv, "talker");

  ros::NodeHandle n;


  ros::Publisher chatter_pub = n.advertise<geometry_msgs::TransformStamped>("chatter1", 1000);
  ros::Publisher chatter_pub2 = n.advertise<geometry_msgs::TransformStamped>("chatter2", 1000);

  ros::Rate loop_rate(10);


  int count = 1;
  while (ros::ok())
  {

    geometry_msgs::TransformStamped msg, msg2;

    msg.header.stamp = ros::Time::now();
    msg.transform.translation.x = count*count;
    msg2.header.stamp = ros::Time::now();
    msg2.transform.translation.x = count*count;


    chatter_pub.publish(msg);
    chatter_pub2.publish(msg2);

    ros::spinOnce();

    loop_rate.sleep();
    ++count;
  }


  return 0;
}
