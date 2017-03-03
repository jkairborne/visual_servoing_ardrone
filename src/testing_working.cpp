#include <iostream>

#include <ros/ros.h>
#include "geometry_msgs/TransformStamped.h"

class SubscribeAndPublish
{
    char msg2[40];
public:
  SubscribeAndPublish(char *msg)//const std::string& msg)
  {
    //Topic you want to publish
    pub_ = n_.advertise<geometry_msgs::TransformStamped>("/published_topic", 1);
    strcpy(msg2,msg);
    //Topic you want to subscribe
    sub_ = n_.subscribe("/chatter", 1, &SubscribeAndPublish::callback, this);
  }

  void callback(const geometry_msgs::TransformStamped& input)
  {
    geometry_msgs::TransformStamped output;
    output.transform.translation.x = input.transform.translation.x-1;
    output.header.seq = input.header.seq;
    //.... do something with the input and generate the output...
    pub_.publish(output);
    ROS_INFO("we are here %s",msg2);
  }

private:
  ros::NodeHandle n_; 
  ros::Publisher pub_;
  ros::Subscriber sub_;

};//End of class SubscribeAndPublish

int main(int argc, char **argv)
{
  //Initiate ROS
  ros::init(argc, argv, "subscribe_and_publish");

  //Create an object of class SubscribeAndPublish that will take care of everything
  SubscribeAndPublish SAPObject("testingishere");

  ros::spin();

  return 0;
}


/*
 *
 * #include "ros/ros.h"
#include "std_msgs/String.h"
#include "ros/master.h"
#include <vector>
#include <sstream>
#include <string>


int main(int argc, char **argv)
{

using namespace ros;
using namespace master;
  ros::init(argc, argv, "talker");
  ros::master::V_TopicInfo topics;
  NodeHandle n;

  ros::Publisher chatter_pub = n.advertise<std_msgs::String>("chatter", 1000);
  ros::Rate loop_rate(10);
  ros::master::getTopics(topics);


  int count = 0;
  while (ros::ok())
  {
    std_msgs::String msg;
//    ROS_INFO("%s",ros::master::V_TopicInfo::front(topics));
    std::stringstream ss;
    TopicInfo testing;
    int i=0;
    for (i=0;i<topics.size();i++){
        testing = topics.at(i);
        if (testing.name.find ("sout_") != std::string::npos)
            {ss << testing.name;}
    }

    //testing = topics.front();
   // std::string
  //  ROS_INFO("%s",testing.name);
    //ss << "hello world " << count <<"   " << testing.name;
    msg.data = ss.str();

    ROS_INFO("%s", msg.data.c_str());

    chatter_pub.publish(msg);

    spinOnce();

    loop_rate.sleep();
    ++count;
  }


  return 0;
}
*/
