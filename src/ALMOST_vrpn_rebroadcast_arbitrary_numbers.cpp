/****************************************************************************

Conversion from a quaternion to roll, pitch and yaw.

Nodes:
subscribed /rotation_quaternion (message of type geometry_msgs::Quaternion)
published /rpy_angles (message oftype geometry_msgs::Vector3.h)

****************************************************************************/

#include "ros/ros.h"
#include "ros/master.h"
#include "geometry_msgs/PoseStamped.h"
#include "geometry_msgs/Vector3.h"
#include "geometry_msgs/Quaternion.h"
#include "tf/transform_datatypes.h"
#include "std_msgs/Float64.h"
#include "std_msgs/String.h"

#include <sstream>
#include <string>

// Here I use global publisher and subscriber, since I want to access the
// publisher in the function MsgCallback:
ros::Publisher rpy_publisher;
ros::Subscriber quat_subscriber;

// Function for conversion of quaternion to roll pitch and yaw. The angles
// are published here too.
void MsgCallback(const geometry_msgs::PoseStamped msg)
{
    geometry_msgs::Quaternion GMquat;
    GMquat = msg.pose.orientation;

    // the incoming geometry_msgs::Quaternion is transformed to a tf::Quaterion
    tf::Quaternion quat, quattemp;
    tf::quaternionMsgToTF(GMquat, quattemp);
//    ROS_INFO("quat.x =%f, quat.y=%f, quat.z=%f, quat.w=%f", quattemp.x(), quattemp.y(), quattemp.z(),quattemp.w());
    quat = tf::Quaternion(quattemp.x(),-quattemp.z(),quattemp.y(),quattemp.w());

    // the tf::Quaternion has a method to acess roll pitch and yaw
    double roll, pitch, yaw;
    tf::Matrix3x3(quat).getRPY(roll, pitch, yaw);

    // the found angles are written in a geometry_msgs::Vector3
    geometry_msgs::Vector3 anglesmsg;
    anglesmsg.z = yaw;
    anglesmsg.y = roll;
    anglesmsg.x = -pitch;

    // this Vector is then published:
    rpy_publisher.publish(anglesmsg);
    ROS_INFO("published pitch=%.1f, roll=%.1f,  yaw=%.1f", anglesmsg.x*180/3.1415926, anglesmsg.y*180/3.1415926, anglesmsg.z*180/3.1415926);

    }

int main(int argc, char **argv)
{
    ros::init(argc, argv, "talker");
    ros::NodeHandle n;
    rpy_publisher = n.advertise<geometry_msgs::Vector3>("angles_output", 1000);
    ros::Publisher chatter_pub = n.advertise<std_msgs::String>("chatter", 1000);
    quat_subscriber = n.subscribe("vrpn_client_node/Ardrone/pose", 1000, MsgCallback);

    // check for incoming quaternions untill ctrl+c is pressed
    ROS_INFO("waiting for quaternion");
  ros::master::V_TopicInfo topics;
  ros::master::getTopics(topics);
 //   ros::spin();
  int count = 0;
  ros::Rate loop_rate(10);
  while (ros::ok())
  {
    std_msgs::String msg;
//    ROS_INFO("%s",ros::master::V_TopicInfo::front(topics));
    std::stringstream ss;
    ros::master::TopicInfo testing;
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

    ros::spinOnce();

    loop_rate.sleep();
    ++count;
  }

    return 0;
}
