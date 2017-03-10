
#include <iostream>
#include <string>
#include <ros/ros.h>
#include "geometry_msgs/PoseStamped.h"
#include <vector>

#include "geometry_msgs/TransformStamped.h"

/*
int main()
{
    int i;
    i = 0;
    for(i=0;i<10;i++)
    {
        int someNewInt = i+5;
        vecInt.push_back(someNewInt);
        std::cout << "we have hit: " << vecInt.back() << '\n';
    }
return 0;
}
*/

class SubscribeAndPublish
{
    std::string msg2;
public:
  SubscribeAndPublish(const std::string& msg)
  {
    //Topic you want to publish
    pub_ = n_.advertise<geometry_msgs::PoseStamped>(("/rebroadcast/"+msg), 1);
    msg2 = msg;
    //Topic you want to subscribe
    sub_ = n_.subscribe("/vrpn_client_node/"+msg, 1, &SubscribeAndPublish::callback, this);
  }

  void callback(const geometry_msgs::PoseStamped& input)//const geometry_msgs::PoseStamped& input)
  {
    geometry_msgs::PoseStamped output;
    output.pose.position.x = input.pose.position.x+100;
    output.header= input.header;
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

  // Create the vector of topics that will be used to store the list of current topics
  ros::master::V_TopicInfo topics;
  ros::master::getTopics(topics);

  // Create the string that will be searched for in the topics:
  std::string searchString = "/vrpn_client_node/";

  //Create an object of class SubscribeAndPublish that will take care of everything
  SubscribeAndPublish SAPObject("testingishere");
  SubscribeAndPublish SAPObject2("testingishere2");



// Will I need a while ros::ok() loop?


  ros::master::TopicInfo testing;
  int i=0;
  std::string topicToCreate;
  // Here we need to create a vector of SubPubs, so that we can create many objects
  std::vector<SubscribeAndPublish> SubPubVector;
  //for (i=0;i<topics.size();i++){
  for (i=(topics.size()-1);i>0;i--){
      ROS_INFO("we are at %d", i);
      testing = topics.at(i);
      std::size_t pos = testing.name.find(searchString);
      if (pos != std::string::npos){
	// Need to create a Subscribe and Publish
    // The topics we are looking for in this case will look something like:
    // /vrpn_client_node/Ardrone/pose
    // Generically, they could look like anything in the searchString
        
        topicToCreate = (testing.name.substr(pos+searchString.length()));// The pos is there in case the search string doesn't start at the beginning of the topic name
        ROS_INFO("We are going to create %s", topicToCreate.c_str());
        SubscribeAndPublish SAPObject(topicToCreate);
        SubPubVector.push_back(SAPObject);

      } // end if
  } // end for


  ros::spin();

  return 0;
}
