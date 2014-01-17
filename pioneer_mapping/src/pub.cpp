#include<ros/ros.h>
#include<tf/transform_broadcaster.h>
#include<geometry_msgs/Twist.h>
#include <pthread.h>

int main(int argc,char **argv){

 ros::init(argc,argv,"pioneer_odom");
 ros::NodeHandle n;
 tf::TransformBroadcaster broadcaster;
 geometry_msgs::TransformStamped odom_trans;

 ros::Rate r(1);
 int i;

 for(i=0;i<1000;i++){
  odom_trans.header.stamp = ros::Time::now();
  odom_trans.transform.translation.x = i;
  odom_trans.header.frame_id = "map";
  odom_trans.child_frame_id = "base_link";
  broadcaster.sendTransform(odom_trans); 
  r.sleep();
 }

 ros::spin();
 
 return 0;
}
