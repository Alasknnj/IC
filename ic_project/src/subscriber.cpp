#include <ros/ros.h>
#include <std_msgs/String.h>

void answer(std_msgs::String msg){
  ROS_INFO("Hello %s",msg.data.c_str());
}



int main(int argc, char **argv){
  
  ros::init(argc,argv,"subscriber");

  ros::NodeHandle n;
  ros::Subscriber sub;

  sub = n.subscribe("names",5,answer);

  ros::spin();

  return 0;
}
