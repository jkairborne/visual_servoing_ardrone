#include "ros/ros.h"
#include "std_msgs/String.h"
#include "ardrone_autonomy/Navdata.h"
#include "std_msgs/Float64.h"

ros::Publisher pubx;
ros::Publisher puby;
ros::Publisher pubwidth;
ros::Publisher pubheight;
ros::Subscriber sub;

void chatterCallback(const ardrone_autonomy::Navdata& msg)
{
if (msg.tags_count==0)
return;
        std_msgs::Float64 msgx;
        std_msgs::Float64 msgy;
        std_msgs::Float64 msgwidth;
        std_msgs::Float64 msgheight;
	
        msgx.data = msg.tags_xc[0];
        msgy.data = msg.tags_yc[0];
        msgwidth.data = msg.tags_width[0];
        msgheight.data = msg.tags_height[0];
        pubx.publish(msgx);
        puby.publish(msgy);
        pubwidth.publish(msgwidth);
        pubheight.publish(msgheight);

   	ros::Rate loop_rate(250);
	ros::spinOnce();
	loop_rate.sleep(); 
  }

int main(int argc, char **argv)
{
  ros::init(argc, argv, "listener");
  ros::NodeHandle n;

  pubx = n.advertise<std_msgs::Float64>("/pose_x",1000);
  puby = n.advertise<std_msgs::Float64>("/pose_y",1000);
  pubwidth = n.advertise<std_msgs::Float64>("/pose_width",1000);
  pubheight = n.advertise<std_msgs::Float64>("/pose_height",1000);

  sub = n.subscribe("/ardrone/navdata", 1000, chatterCallback);

  ros::spin();
  return 0;
}
