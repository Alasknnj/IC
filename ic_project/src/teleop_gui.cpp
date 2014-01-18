#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <geometry_msgs/Twist.h>

int main(int argc, char **argv){

 ros::init(argc,argv,"teleop_keyboard");
 ros::NodeHandle n;
 ros::Publisher pub = n.advertise<geometry_msgs::Twist>("vel",1);


  
 char ch;
 ch = getchar();
 while(ros::ok()){
  geometry_msgs::Twist msg;
 //rotina de reset da msg
  msg.linear.x = 0;
  msg.linear.y = 0;
  msg.linear.z = 0;
  msg.angular.x = 0;
  msg.angular.y = 0;
  msg.angular.z = 0;

   ch = getchar();
 // cadeia de ifs para identificar arrow keys
   if(ch == 27){

    ch = getchar();

    if(ch == 91){

     ch = getchar();   
  
     switch(ch){
      case 65 : msg.linear.x = 10;
                break;
      case 66 : msg.linear.x = -10;
                break;
      case 67 : msg.angular.z = -10;
                break;
      case 68 : msg.angular.z = 10;
                break;
     }
     
     pub.publish(msg);
    }

   }


 
 }

return 0;
}
