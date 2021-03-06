#include <ros/ros.h>
#include <std_msgs/String.h>

int main (int argc, char **argv){

  ros::init(argc,argv,"publisher");

  ros::NodeHandle n;
  ros::Publisher pub;

  pub = n.advertise<std_msgs::String>("names",5);

  ros::Rate r(1);
  std::string names[4] = {"Ana","Maria","Pedro","Carlos"}; 
  std_msgs::String msg;
  int i=0;
  while(ros::ok()){
    msg.data = names[i%4];
    pub.publish(msg);
    r.sleep();
    i++;
  }

  return 0;
}
