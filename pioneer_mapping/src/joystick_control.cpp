#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/Joy.h>


class Joystick_teleop{
public:
 Joystick_teleop();
private:
 void joyCallback(const sensor_msgs::Joy joy);
 
 ros::NodeHandle n;
 ros::Publisher pub;
 ros::Subscriber sub;
};

 Joystick_teleop::Joystick_teleop(){
 pub = n.advertise<geometry_msgs::Twist>("cmd_vel",1);
 sub = n.subscribe<sensor_msgs::Joy>("joy",10,&Joystick_teleop::joyCallback,this);

 }

 void Joystick_teleop::joyCallback(const sensor_msgs::Joy joy){
 geometry_msgs::Twist vel;
 if(joy.buttons[0]==1){
  float angular_scale = 2.5*(joy.axes[2]+1);
  float linear_scale = 2.5*(joy.axes[2]+1);
  vel.angular.z = angular_scale*joy.axes[0];
  vel.linear.x = linear_scale*joy.axes[1];
  }
  else{
  vel.angular.z = 0;
  vel.linear.x = 0;
  }
  pub.publish(vel);
 
 } 


int main(int argc, char **argv){

ros::init(argc,argv,"joystick_teleop");

Joystick_teleop joy_tel;

ros::spin();
return 0;
}
