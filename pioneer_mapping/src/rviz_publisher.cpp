#include <ros/ros.h>
#include <sensor_msgs/JointState.h>
#include <tf/transform_broadcaster.h>
#include <nav_msgs/Odometry.h>

class Odom{
  public:
    Odom(); 

   private:  
     void odomCallback(const nav_msgs::Odometry msg);

     double odomX;
     double odomY;
     double odomZ;
     double odomA;
     double odomB;
     double odomC;
     double odomD;

     ros::NodeHandle n;
     tf::TransformBroadcaster broadcaster;
     sensor_msgs::JointState joint_state;
     geometry_msgs::TransformStamped tf;
};

Odom::Odom(){
  ros::Publisher joint_pub = n.advertise<sensor_msgs::JointState>("joint_states", 1);
  ros::Subscriber sub = n.subscribe("odom",5,&Odom::odomCallback,this);

  odomX = 0;
  odomY = 0;
  odomZ = 0;
  odomA = 0;
  odomB = 0;
  odomC = 0;
  odomD = 0;
  ros::Rate r(50);

  tf.header.frame_id = "odom";
  tf.child_frame_id = "base_link";

  while(ros::ok()){

    joint_state.header.stamp = ros::Time::now();
    joint_state.name.resize(4); 
    joint_state.position.resize(4);

    joint_state.name[0] = "p3at_back_right_wheel_joint";
    joint_state.position[0] = 0;

    joint_state.name[1] = "p3at_back_left_wheel_joint";
    joint_state.position[1] = 0;

    joint_state.name[2] = "p3at_front_right_wheel_joint";
    joint_state.position[2] = 0;

    joint_state.name[3] = "p3at_front_left_wheel_joint";
    joint_state.position[3] = 0;

    tf.header.stamp = ros::Time::now();
    tf.transform.translation.x = odomX;
    tf.transform.translation.y = odomY;
    tf.transform.translation.z = odomZ;
    tf.transform.rotation.x = odomA;
    tf.transform.rotation.y = odomB;
    tf.transform.rotation.z = odomC;
    tf.transform.rotation.w = odomD;
    joint_pub.publish(joint_state);
    broadcaster.sendTransform(tf);
    ros::spinOnce();
    r.sleep();
 } 

}

void Odom::odomCallback(const nav_msgs::Odometry msg){
  odomX = msg.pose.pose.position.x;
  odomY = msg.pose.pose.position.y;
  odomZ = msg.pose.pose.position.z;
  odomA = msg.pose.pose.orientation.x;
  odomB = msg.pose.pose.orientation.y;
  odomC = msg.pose.pose.orientation.z;
  odomD = msg.pose.pose.orientation.w;

}




int main( int argc, char* argv[] ){
  ros::init(argc, argv, "rviz_pioneer_publisher");
  
  Odom odom;  
	
  return 0; 
}
