#include "ros/ros.h"
#include "std_msgs/String.h"
#include "ar_track_alvar_msgs/AlvarMarkers.h"
#include "std_msgs/Float64.h"
#include "publ_subs/test.h"
#include "geometry_msgs/Vector3.h"
#include "geometry_msgs/Quaternion.h"
#include "tf/transform_datatypes.h"
/*
#include "LinearMath/btMatrix3x3.h"
*/
/**
 * This tutorial demonstrates simple receipt of messages over the ROS system.
 */

ros::Subscriber sub;

void chatterCallback(const ar_track_alvar_msgs::AlvarMarkers& msg)
{
/*  
ROS_INFO("I heard: [%d]", msg.ar_track_alvar_msgs.AlvarMarkers.marker.id);

  ROS_INFO("I heard: [%d], %i, and d%cd", msg.header.seq, msg.header.stamp.sec, msg.header.frame_id[0]);
*/

/*
	ros::Publisher chattery = nh.advertise<std_msgs::Float64>("pose_y", 1000);
	ros::Publisher chatterz = nh.advertise<std_msgs::Float64>("pose_z", 1000);
*/
        double msgx;
        double msgy;
        double msgz;
        geometry_msgs::Quaternion msgquat;
/*  
        msgx.data = msg.markers[0].pose.pose.position.x;
        msgy.data = msg.markers[0].pose.pose.position.y;
 */
        msgx = msg.markers[0].pose.pose.position.x;
        msgy = msg.markers[0].pose.pose.position.y;
        msgz = msg.markers[0].pose.pose.position.z;
        msgquat = msg.markers[0].pose.pose.orientation;
/*   
     msgy.data = msg.markers[0].pose.pose.position.y;
        msgz.data = msg.markers[0].pose.pose.position.z;
*/
	tf::Quaternion quat;
	tf::quaternionMsgToTF(msg.markers[0].pose.pose.orientation, quat);
	double roll, pitch, yaw;
        tf::Matrix3x3(quat).getRPY(roll, pitch, yaw);

    /**
     * The publish() function is how you send messages. The parameter
     * is the message object. The type of this object must agree with the type
     * given as a template parameter to the advertise<>() call, as was done
     * in the constructor above.
     */
ROS_INFO("x: %f", msg.markers[0].pose.pose.position.x);
ROS_INFO("y: %f", msg.markers[0].pose.pose.position.y);
ROS_INFO("z: %f", msg.markers[0].pose.pose.position.z);
ROS_INFO("roll:   %f", roll);
ROS_INFO("pitch:  %f", pitch);
ROS_INFO("yaw:    %f", yaw);
/*
       chattery.publish(msgy);
       chatterz.publish(msgz);
  */ 	ros::Rate loop_rate(10);
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
   * called chatterCallback.  subscribe() returns a Subscriber object that you
   * must hold on to until you want to unsubscribe.  When all copies of the Subscriber
   * object go out of scope, this callback will automatically be unsubscribed from
   * this topic.
   *
   * The second parameter to the subscribe() function is the size of the message
   * queue.  If messages are arriving faster than they are being processed, this
   * is the number of messages that will be buffered up before beginning to throw
   * away the oldest ones.
   */
  sub = n.subscribe("/ar_pose_marker", 1000, chatterCallback);

  /**
   * ros::spin() will enter a loop, pumping callbacks.  With this version, all
   * callbacks will be called from within this thread (the main one).  ros::spin()
   * will exit when Ctrl-C is pressed, or the node is shutdown by the master.
   */
  ros::spin();

  return 0;
}
