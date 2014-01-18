#include <ros/ros.h>

int main(int argc , char **argv){

ros::init(argc,argv,"dummy publisher");
ros::NodeHandle n;

ros::Publisher pub = n.advertise<geometry_msgs::Twist>("cmd_vel",50);
ros::Rate r(0.2);

while(ros::ok()){
ros::geometry_msgs::Twist msg;
msg.linear.x = 0.5;
msg.angular.z = 0.1;

pub.publish(msg);
r.sleep();
}




return 0;
}

