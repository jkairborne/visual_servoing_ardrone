#include "ros/ros.h"
#include "ardrone_autonomy/Navdata.h"
#include "std_msgs/Float64.h"

ros::Publisher pubx;
ros::Publisher puby;
ros::Publisher pubz;

void chatterCallback(const ardrone_autonomy::Navdata& msg)
{
  ROS_INFO("I heard: [%f]", msg.rotX);
  std_msgs::Float64 msgx, msgy, msgz;
  msgx.data = msg.rotX;
  msgy.data = msg.rotY;
  msgz.data = msg.rotZ;
  pubx.publish(msgx);
  puby.publish(msgy);
  pubz.publish(msgz);
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "listener2");

  ros::NodeHandle n; 

  pubx = n.advertise<std_msgs::Float64>("/rotx",1000);
  puby = n.advertise<std_msgs::Float64>("/roty",1000);
  pubz = n.advertise<std_msgs::Float64>("/rotz",1000);
  ros::Subscriber sub = n.subscribe("ardrone/navdata", 1000, chatterCallback);
  ros::spin();

  return 0;
}



