#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <geometry_msgs/Twist.h>

double odomX, odomFi;

void callBack(const geometry_msgs::Twist msg){
ROS_INFO("SHAUSAH");
geometry_msgs::TransformStamped tf;
 tf.header.frame_id = "map";
 tf.child_frame_id = "base_box";

double dt = 0.01;

 odomX+=msg.linear.x*dt;
 odomFi+=msg.angular.z*dt;
 tf::TransformBroadcaster broadcaster;
 tf.header.stamp = ros::Time::now();
 tf.transform.translation.x = odomX;
 tf.transform.translation.z = 0.5;
 tf.transform.rotation = tf::createQuaternionMsgFromYaw(odomFi);
ROS_INFO("%f",tf.transform.translation.x);
ROS_INFO("%f",msg.linear.x);
 
 broadcaster.sendTransform(tf);
ROS_INFO("SENT");
}


int main(int argc, char** argv) {
 ros::init(argc,argv,"control_box");
 ros::NodeHandle n;

 ros::Subscriber sub = n.subscribe("vel",1,callBack);
 ros::spin();

return 0;
}

