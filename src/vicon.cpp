#include "ros/ros.h"
#include <math.h>
#include <sstream>
#include "geometry_msgs/TransformStamped.h"
#include "geometry_msgs/Vector3.h"
#include "geometry_msgs/Quaternion.h"
#include "std_msgs/Float64.h"
#include "tf/transform_datatypes.h"

// Define constants to be the paths to receive vicon data
#define VICON_ROOMBA "/chatter"
#define VICON_ARDRONE "/anythinghere"



// Define global variables because we can't have the callbacks return any values
geometry_msgs::Vector3 roomba_pos1, roomba_pos2, roomba_vel1, roomba_vel2, roomba_acc1;
geometry_msgs::Vector3 roomba_pos, ardrone_pos, roomba_vel, roomba_acc;
double posxdiff, posydiff, poszdiff, velxdiff, accxdiff, ardroneyaw = 0.0;
std_msgs::Float64 topid_x, topid_y, topid_z, topid_yaw;
ros::Time roomba_time, ardrone_time;
ros::Duration roomba_diff, roomba_diff2, ardrone_diff;
tf::Quaternion ardronequat;

// Create publishers to output position, velocity, and acceleration
ros::Publisher pid_xpub;
ros::Publisher pid_ypub;
ros::Publisher pid_zpub;
ros::Publisher pid_yawpub;

/*ros::Publisher posxpub;
ros::Publisher posypub;
ros::Publisher poszpub;
ros::Publisher velxpub;
ros::Publisher accxpub;
*/
/*
ros::Publisher velypub;
ros::Publisher accypub;
ros::Publisher velzpub;
ros::Publisher acczpub;
*/

//Prototype for the callback functions
void callback_roomba(const geometry_msgs::TransformStamped& vic_roomba); 
void callback_ardrone(const geometry_msgs::TransformStamped& vic_ardrone);

int main(int argc, char **argv)
{
    ROS_INFO("I am at the start");
    ros::init(argc, argv, "VICON_node");
    ros::NodeHandle n;

    ros::Subscriber subroomba, subardrone;


    // Initialize all vectors to zero - this should hopefully prevent too much funny business at the start
    geometry_msgs::Vector3 zerovector;
    zerovector.x = 0.0;
    zerovector.y = 0.0;
    zerovector.z = 0.0;
    roomba_pos = ardrone_pos = roomba_pos1 = roomba_pos2 = roomba_vel = roomba_vel1 = roomba_vel2 = roomba_acc = roomba_acc1 = zerovector;
 


    pid_xpub = n.advertise<std_msgs::Float64>("vicon_x",1000);
    pid_ypub = n.advertise<std_msgs::Float64>("vicon_y",1000);
    pid_zpub = n.advertise<std_msgs::Float64>("vicon_z",1000);
    pid_yawpub = n.advertise<std_msgs::Float64>("vicon_yaw",1000);


/*
    posxpub = n.advertise<std_msgs::Float64>("posx_diff",1000);
    velxpub = n.advertise<std_msgs::Float64>("velx_diff",1000);
    accxpub = n.advertise<std_msgs::Float64>("accx_diff",1000);
    posypub = n.advertise<std_msgs::Float64>("posy_diff",1000);
    poszpub = n.advertise<std_msgs::Float64>("posz_diff",1000);
    ROS_INFO("I before callback");
*/
    subroomba = n.subscribe(VICON_ROOMBA, 1000, callback_roomba);
    subardrone = n.subscribe(VICON_ARDRONE, 1000, callback_ardrone);
    

    ros::spin();
}


void callback_roomba(const geometry_msgs::TransformStamped& vic_roomba)
{

    ROS_INFO("I am at the start of callback");
   // Assign the time difference and time for the currenty position.
   roomba_diff = vic_roomba.header.stamp - roomba_time;
   roomba_time = vic_roomba.header.stamp;
   // Assign roomba_pos1 to be the position difference, here roomba_pos is the old velocity
    roomba_pos1.x = vic_roomba.transform.translation.x - roomba_pos.x;
    roomba_pos1.y = vic_roomba.transform.translation.y - roomba_pos.y;
    roomba_pos1.z = vic_roomba.transform.translation.z - roomba_pos.z;

   // Set roomba_pos to be the new position so it will be in position for next time
   roomba_pos = vic_roomba.transform.translation;

/* Pretty sure none of this is needed:
 * roomba_pos1.x = roomba_pos.x - roomba_pos2.x;
    roomba_pos1.y = roomba_pos.y - roomba_pos2.y;
    roomba_pos1.z = roomba_pos.z - roomba_pos2.z;
*/
   // Calculate most recent roomba velocity difference
   roomba_vel1.x = roomba_pos1.x/roomba_diff.toSec();
   roomba_vel1.y = roomba_pos1.y/roomba_diff.toSec();
   roomba_vel1.z = roomba_pos1.z/roomba_diff.toSec();
   roomba_acc1.x = (roomba_vel1.x-roomba_vel2.x)/(roomba_diff.toSec()+roomba_diff2.toSec());
   roomba_acc1.y = (roomba_vel1.y-roomba_vel2.y)/(roomba_diff.toSec()+roomba_diff2.toSec());
   roomba_acc1.z = (roomba_vel1.z-roomba_vel2.z)/(roomba_diff.toSec()+roomba_diff2.toSec());
   // Reset the roomba_diff and the roomba velocity for use for the next calculation
   roomba_diff2 = roomba_diff;
   roomba_vel2 = roomba_vel1;

   posxdiff = ardrone_pos.x - roomba_pos.x;
   posydiff = ardrone_pos.y - roomba_pos.y;
   poszdiff = ardrone_pos.z - roomba_pos.z;
   velxdiff = roomba_vel1.x;
   accxdiff = roomba_acc1.x;

    //Implement the three separate control designs - in x take advantage of additional information about the target motion
    //in y take only the position difference with saturation function. In z, simple position difference.
    topid_x.data = 0.5*accxdiff + velxdiff + posxdiff/(1 + abs(posxdiff));
    topid_y.data = posydiff/(1 + abs(posydiff));
    topid_z.data = poszdiff;

    pid_xpub.publish(topid_x);
    pid_ypub.publish(topid_y);
    pid_zpub.publish(topid_z);


/*
   //Publish position difference between ArDrone and Roomba
   //And the velocity and acceleration of the roomba.

   posxpub.publish(posxdiff);
   posxpub.publish(posxdiff);
   posypub.publish(posydiff);
   velxpub.publish(velxdiff);
   accxpub.publish(accxdiff);
*/
   } 


void callback_ardrone(const geometry_msgs::TransformStamped& vic_ardrone)
{
    ROS_INFO("In callback ardrone");
    ardrone_pos = vic_ardrone.transform.translation;

    // the incoming geometry_msgs::Quaternion is transformed to a tf::Quaterion
    tf::quaternionMsgToTF(vic_ardrone.transform.rotation, ardronequat);

    // the tf::Quaternion has a method to acess roll pitch and yaw
    double roll, pitch;
    tf::Matrix3x3(ardronequat).getRPY(roll, pitch, ardroneyaw);

// Reproduce what we had above - update the pid messages and then publish them, as in the roomba callback
    posxdiff = ardrone_pos.x - roomba_pos.x;
    posydiff = ardrone_pos.y - roomba_pos.y;
    poszdiff = ardrone_pos.z - roomba_pos.z;
    topid_x.data = 0.5*accxdiff + velxdiff + posxdiff/(1 + abs(posxdiff));
    topid_y.data = posydiff/(1 + abs(posydiff));
    topid_z.data = poszdiff;

    pid_xpub.publish(topid_x);
    pid_ypub.publish(topid_y);
    pid_zpub.publish(topid_z);
}

