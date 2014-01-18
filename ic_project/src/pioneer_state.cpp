#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/JointState.h>
#include <tf/transform_broadcaster.h>

class Odom{
 public:
  Odom(); 

 private:  
  void odomCallback(const geometry_msgs::Twist msg);

  double dt;
  double odomX;
  double odomY;
  double odomAngle;
  double velX;
  double velAng;
  ros::NodeHandle n;
  tf::TransformBroadcaster broadcaster;

  
  sensor_msgs::JointState joint_state;
  geometry_msgs::TransformStamped tf;
};

Odom::Odom(){
 ros::Publisher joint_pub = n.advertise<sensor_msgs::JointState>("joint_states", 1);
 ros::Subscriber sub = n.subscribe("cmd_vel",5,&Odom::odomCallback,this);

 dt = (double) 1/20;
 odomX = 0;
 odomY = 0;
 odomAngle = 0;
 ros::Rate r(20);

 tf.header.frame_id = "odom";
 tf.child_frame_id = "base_link";

 while(ros::ok()){
  joint_state.header.stamp = ros::Time::now();
  joint_state.name.resize(4);
  joint_state.position.resize(4);
  joint_state.name[0] ="wheelConnect1";
  joint_state.position[0] = 0;
  joint_state.name[1] ="wheelConnect2";
  joint_state.position[1] = 0;
  joint_state.name[2] ="wheelConnect3";
  joint_state.position[2] = 0;
  joint_state.name[3] ="wheelConnect4";
  joint_state.position[3] = 0;

  odomX += cos(odomAngle)*velX*dt;
  odomY += sin(odomAngle)*velX*dt;
  odomAngle += velAng*dt;
  tf.header.stamp = ros::Time::now();
  tf.transform.translation.x = odomX;
  tf.transform.translation.y = odomY;
  tf.transform.translation.z = 0.205;
  tf.transform.rotation = tf::createQuaternionMsgFromYaw(odomAngle);
  joint_pub.publish(joint_state);
  broadcaster.sendTransform(tf);

  ros::spinOnce();
  r.sleep();
 } 

}

void Odom::odomCallback(const geometry_msgs::Twist msg){
 velX = msg.linear.x;
 velAng = msg.angular.z;
 

}



int main(int argc, char** argv) {
 ros::init(argc,argv,"pioneer_control");

 Odom odom;

 return 0;
}
