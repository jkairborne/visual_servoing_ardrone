#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/Float64.h"
#include "geometry_msgs/Twist.h"
#include "tf/transform_datatypes.h"
/*
#include "LinearMath/btMatrix3x3.h"
*/
/**
 * This tutorial demonstrates simple receipt of messages over the ROS system.
 */
ros::Publisher PassedThrough;

ros::Subscriber sub;

void chatterCallback(const geometry_msgs::Twist msg)
{
/*  
ROS_INFO("I heard: [%d]", msg.ar_track_alvar_msgs.AlvarMarkers.marker.id);

  ROS_INFO("I heard: [%d], %i, and d%cd", msg.header.seq, msg.header.stamp.sec, msg.header.frame_id[0]);
*/
ROS_INFO("I heard: [%f, %f, %f]", msg.linear.x,msg.linear.y,msg.linear.z);

/*
	ros::Publisher chattery = nh.advertise<std_msgs::Float64>("pose_y", 1000);
	ros::Publisher chatterz = nh.advertise<std_msgs::Float64>("pose_z", 1000);  
      std_msgs::Float64 msgy;
        std_msgs::Float64 msgz;
 */
		if (msg.linear.x != 0 or msg.linear.y != 0 or msg.linear.z != 0 or msg.angular.z !=0)
			{
			PassedThrough.publish(msg);
			}
/*   
     msgy.data = msg.markers[0].pose.pose.position.y;
        msgz.data = msg.markers[0].pose.pose.position.z;
*/

    /**
     * The publish() function is how you send messages. The parameter
     * is the message object. The type of this object must agree with the type
     * given as a template parameter to the advertise<>() call, as was done
     * in the constructor above.
     */
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
  PassedThrough = n.advertise<geometry_msgs::Twist>("/key_filtered",1000);
  sub = n.subscribe("/cmd_vel", 1000, chatterCallback);

  /**
   * ros::spin() will enter a loop, pumping callbacks.  With this version, all
   * callbacks will be called from within this thread (the main one).  ros::spin()
   * will exit when Ctrl-C is pressed, or the node is shutdown by the master.
   */
  ros::spin();

  return 0;
}
