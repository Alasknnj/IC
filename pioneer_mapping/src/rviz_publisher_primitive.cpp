#include <ros/ros.h>
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

  dt = (double) 1/50;
  odomX = 0;
  odomY = 0;
  odomAngle = 0;
  ros::Rate r(50);

  tf.header.frame_id = "odom";
  tf.child_frame_id = "base_link";

  while(ros::ok()){

    joint_state.header.stamp = ros::Time::now();
    joint_state.name.resize(10); //Pioneer has 6 joint state definitions. 
    joint_state.position.resize(10);

    joint_state.name[0] = "base_top_joint";
    joint_state.position[0] = 0;

    joint_state.name[1] = "base_swivel_joint";
    joint_state.position[1] = 0;

    joint_state.name[2] = "swivel_hubcap_joint";
    joint_state.position[2] = 0;

    joint_state.name[3] = "center_wheel_joint";
    joint_state.position[3] = 0; 

    joint_state.name[4] = "base_front_joint";
    joint_state.position[4] = 0;

    joint_state.name[5] = "base_back_joint";
    joint_state.position[5] = 0;

    joint_state.name[6] = "p3at_back_right_wheel_joint";
    joint_state.position[6] = 0;

    joint_state.name[7] = "p3at_back_left_wheel_joint";
    joint_state.position[7] = 0;

    joint_state.name[8] = "p3at_front_right_wheel_joint";
    joint_state.position[8] = 0;

    joint_state.name[9] = "p3at_front_left_wheel_joint";
    joint_state.position[9] = 0;

    odomX += cos(odomAngle)*velX*dt;
    odomY += sin(odomAngle)*velX*dt;
    odomAngle += velAng*dt;

    tf.header.stamp = ros::Time::now();
    tf.transform.translation.x = odomX;
    tf.transform.translation.y = odomY;
    tf.transform.translation.z = 0;
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




int main( int argc, char* argv[] ){
  ros::init(argc, argv, "rviz_pioneer_publisher");
  
  Odom odom;  
	
  return 0; 
}
