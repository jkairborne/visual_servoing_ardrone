#include "ros/ros.h"
#include "std_msgs/String.h"
#include "ardrone_autonomy/Navdata.h"
#include "std_msgs/Float64.h"
#include "geometry_msgs/Vector3.h"
#include "std_msgs/Int16.h"
#include "geometry_msgs/Quaternion.h"
#include "tf/transform_datatypes.h"
#include "tf/transform_listener.h"

ros::Publisher pubx;
/*
ros::Publisher puby;
ros::Publisher pubz;
ros::Publisher pubquat;
*/
ros::Subscriber sub;

void chatterCallback(const ardrone_autonomy::Navdata& msg)
{
ROS_INFO("I here");
if (msg.tags_count==0)
return;

ROS_INFO("I heard: [%d]", msg.tags_xc[1]);

        std_msgs::Int16 msgx;
        msgx.data = msg.tags_xc[0];
        ROS_INFO("%d", msgx.data);

       pubx.publish(msgx);
   	ros::Rate loop_rate(10);
	ros::spinOnce();
	loop_rate.sleep(); 
  }

int main(int argc, char **argv)
{
  ros::init(argc, argv, "listener");
  ros::NodeHandle n;

  pubx = n.advertise<std_msgs::Float64>("/pose_x",1000);

  sub = n.subscribe("/ardrone/navdata", 1000, chatterCallback);

  ros::spin();
  return 0;
}
