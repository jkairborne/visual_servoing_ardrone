
#include <iostream>
#include <string>
#include <ros/ros.h>
#include "geometry_msgs/PoseStamped.h"
#include <vector>

#include "geometry_msgs/TransformStamped.h"

class SubscribeAndPublish
{
    std::string msg2;
public:
  SubscribeAndPublish(const std::string& msg)
  {
    //Topic you want to publish
    pub_ = n_.advertise<geometry_msgs::TransformStamped>(("/rebroadcast/"+msg), 1);
    msg2 = msg;
    //Topic you want to subscribe
    ROS_INFO("Creating SubPub object for: %s",msg.c_str());
    sub_ = n_.subscribe(msg, 1, &SubscribeAndPublish::callback, this);
  }

  void callback(const geometry_msgs::TransformStamped& input)//const geometry_msgs::PoseStamped& input)
  {
    geometry_msgs::TransformStamped output;
    output = input;
    //.... do something with the input and generate the output...
    pub_.publish(output);
    ROS_INFO("we are here %s",msg2.c_str());
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


  int i=0;
  // Here we need to create a vector of SubPubs, so that we can create many objects
  std::vector<SubscribeAndPublish> SubPubVector;

  /*
for(i=0;i<4;++i){
  SubscribeAndPublish SAPObject("/chatter"+i);
}//end for
*/

  //Create an object of class SubscribeAndPublish that will take care of everything
  SubscribeAndPublish SAPObject2("/chatter2");

  SubscribeAndPublish SAPObject("/chatter1");

  SubPubVector.push_back(SAPObject2);
  SubPubVector.push_back(SAPObject);

  // Will I need a while ros::ok() loop?



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
