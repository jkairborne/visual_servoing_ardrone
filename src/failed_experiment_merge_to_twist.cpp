#include "ros/ros.h"
#include "std_msgs/String.h"
#include "ar_track_alvar_msgs/AlvarMarkers.h"
#include "std_msgs/Float64.h"
#include "publ_subs/test.h"
#include "geometry_msgs/Vector3.h"
#include "geometry_msgs/Twist.h"
#include "geometry_msgs/Quaternion.h"
#include "tf/transform_datatypes.h"
/*
#include "LinearMath/btMatrix3x3.h"
*/
/**
 * This tutorial demonstrates simple receipt of messages over the ROS system.
 */
ros::Subscriber subx;
ros::Subscriber suby;
ros::Subscriber subz;
ros::Subscriber subquat;

ros::Publisher pub;

void chatterCallbackx(const std_msgs::Float64& msgx)
{
ROS_INFO("I heard: [%f]", msg.data);
        std_msgs::Float64 msgx;
        std_msgs::Float64 msgy;
        std_msgs::Float64 msgz;
        geometry_msgs::Quaternion msgquat;
        msgx.data = msg.markers[0].pose.pose.position.x;
        msgy.data = msg.markers[0].pose.pose.position.y;
        msgz.data = msg.markers[0].pose.pose.position.z;
        msgquat = msg.markers[0].pose.pose.orientation;
        ROS_INFO("%f", msgx.data);

    
   	ros::Rate loop_rate(10);
	ros::spinOnce();
	loop_rate.sleep(); 
  }




int main(int argc, char **argv)
{
  /**
   * The ros::init() function needs to see argc and argv so that it can perform
   * any ROS arguments and name remapping that were provided at the command line.
   * For programmatic remappings you can use a different version of init() which takes
   * remappings directly, but for most command-line programs, passing argc and argv is
   * the easiest way to do it.  The third argument to init() is the name of the node.
   *
   * You must call one of the versions of ros::init() before using any other
   * part of the ROS system.
   */
  ros::init(argc, argv, "listener");

  /**
   * NodeHandle is the main access point to communications with the ROS system.
   * The first NodeHandle constructed will fully initialize this node, and the last
   * NodeHandle destructed will close down the node.
   */
  ros::NodeHandle n;

  /**
   * The subscribe() call is how you tell ROS that you want to receive messages
   * on a given topic.  This invokes a call to the ROS
   * master node, which keeps a registry of who is publishing and who
   * is subscribing.  Messages are passed to a callback function, here
   * called chatterCallback.  subscribe() returns a Publisher object that you
   * must hold on to until you want to unsubscribe.  When all copies of the Publisher
   * object go out of scope, this callback will automatically be unsubscribed from
   * this topic.
   *
   * The second parameter to the subscribe() function is the size of the message
   * queue.  If messages are arriving faster than they are being processed, this
   * is the number of messages that will be buffered up before beginning to throw
   * away the oldest ones.
   */
  subx = n.subscribe<std_msgs::Float64>("/pose_x",1000,chatterCallbackx);
  suby = n.subscribe<std_msgs::Float64>("/pose_y",1000);
  subz = n.subscribe<std_msgs::Float64>("/pose_z",1000);
  subquat = n.subscribe<geometry_msgs::Float64>("/pose_quat",1000);
  pub = n.advertise("/vs_output", 1000);

  /**
   * ros::spin() will enter a loop, pumping callbacks.  With this version, all
   * callbacks will be called from within this thread (the main one).  ros::spin()
   * will exit when Ctrl-C is pressed, or the node is shutdown by the master.
   */
  ros::spin();

  return 0;
}
