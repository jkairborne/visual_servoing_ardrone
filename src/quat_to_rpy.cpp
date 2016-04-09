/****************************************************************************

Conversion from a quaternion to roll, pitch and yaw.

Nodes:
subscribed /rotation_quaternion (message of type geometry_msgs::Quaternion)
published /rpy_angles (message oftype geometry_msgs::Vector3.h)

****************************************************************************/

#include "ros/ros.h"
#include "geometry_msgs/Vector3.h"
#include "geometry_msgs/Quaternion.h"
#include "tf/transform_datatypes.h"
#include "std_msgs/Float64.h"
/*
#include "tf/LinearMath/btMatrix3x3.h"
*/
// Here I use global publisher and subscriber, since I want to access the
// publisher in the function MsgCallback:
ros::Publisher rpy_publisher;
ros::Subscriber quat_subscriber;

// Function for conversion of quaternion to roll pitch and yaw. The angles
// are published here too.
void MsgCallback(const geometry_msgs::Quaternion msg)
{
    // the incoming geometry_msgs::Quaternion is transformed to a tf::Quaterion
    tf::Quaternion quat;
    tf::quaternionMsgToTF(msg, quat);

    // the tf::Quaternion has a method to acess roll pitch and yaw
    double roll, pitch, yaw;
    tf::Matrix3x3(quat).getRPY(roll, pitch, yaw);

    // the found angles are written in a geometry_msgs::Vector3
    std_msgs::Float64 yawmsg;
    yawmsg.data = yaw;

    // this Vector is then published:
    rpy_publisher.publish(yawmsg);
    ROS_INFO("published yaw=%f", yawmsg.data);
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "talker");
    ros::NodeHandle n;
    rpy_publisher = n.advertise<std_msgs::Float64>("yaw_angle", 1000);
    quat_subscriber = n.subscribe("pose_quat", 1000, MsgCallback);

    // check for incoming quaternions untill ctrl+c is pressed
    ROS_INFO("waiting for quaternion");
    ros::spin();
    return 0;
}
