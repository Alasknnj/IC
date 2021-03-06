#include <ros/ros.h>
#include <string>
#include <tf/transform_broadcaster.h>

int main(int argc, char** argv) {
 ros::init(argc,argv,"circle_fool");
 ros::NodeHandle n;
 tf::TransformBroadcaster broadcaster;
 ros::Rate r(30);


 geometry_msgs::TransformStamped tf;
 tf.header.frame_id = "odom";
 tf.child_frame_id = "box";

 double teta = M_PI/180;
 double dist = 0;
 double R = 3.0;
 while(ros::ok()){


 tf.header.stamp = ros::Time::now();
 tf.transform.translation.x=R*cos(teta);
 tf.transform.translation.y=R*sin(teta);
 tf.transform.translation.z=0.5;
 tf.transform.rotation = tf::createQuaternionMsgFromYaw(teta);

 broadcaster.sendTransform(tf);

 dist+= 0.05;
 teta+=M_PI/180;
 r.sleep();
 } 






return 0;
}
