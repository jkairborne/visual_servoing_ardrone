#include "ros/ros.h"
#include "ardrone_autonomy/Navdata.h"
#include "std_msgs/Float64.h"
#include "cmath"
#include "ar_track_alvar_msgs/AlvarMarkers.h"


double rotx, roty, rotz;
double xpos1, ypos1, zpos1;

void posCallback(const ar_track_alvar_msgs::AlvarMarkers& msg)
{
  xpos1 = msg.markers[0].pose.pose.position.x;
  ypos1 = msg.markers[0].pose.pose.position.y;
  zpos1 = msg.markers[0].pose.pose.position.z;
  ROS_INFO("posCallback, %f, %f, %f",xpos1,ypos1,zpos1);
}

void chatterCallback(const ardrone_autonomy::Navdata& msg)
{
  rotx = msg.rotX*M_PI/180;
  roty = msg.rotY*M_PI/180;
  rotz = msg.rotZ*M_PI/180;
  double derotx, deroty, derotz;
    
  derotx = (cos(rotz)*cos(roty))*xpos1 + (cos(rotz)*sin(roty)*sin(rotx)-sin(rotz)*cos(rotx))*ypos1 + (cos(rotz)*sin(roty)*cos(rotx)+sin(rotz)*sin(rotx))*zpos1;
  
  deroty = sin(rotz)*cos(roty)*xpos1 + (sin(rotz)*sin(roty)*sin(rotx)+cos(rotz)*cos(rotx))*ypos1 + (sin(rotz)*sin(roty)*cos(rotx)-cos(rotz)*sin(rotx))*zpos1;

  derotz = -sin(roty)*xpos1+cos(roty)*sin(rotx)*ypos1+cos(roty)*cos(rotx)*zpos1;

  ROS_INFO("I heard: [%f %f %f]", derotx, deroty, derotz);
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "listener2");

  ros::NodeHandle n; 

  ros::Subscriber subpos = n.subscribe("ar_pose_marker",1000,posCallback);
  ros::Subscriber sub = n.subscribe("ardrone/navdata", 1000, chatterCallback);
  ros::spin();

  return 0;
}



