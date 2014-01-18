#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>

int main (int argc, char **argv){

ros::init(argc,argv,"laser_node");
ros::NodeHandle n;
ros::Subscriber sub =n.subscribe("/scan");

ros::spin();
return 0;
}
