#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <geometry_msgs/Twist.h>

int main(int argc, char **argv){

 ros::init(argc,argv,"teleop_keyboard");
 ros::NodeHandle n;
 ros::Publisher pub = n.advertise<geometry_msgs::Twist>("cmd_vel",1);


  
 char ch = 'a';
 system("/bin/stty raw");


 while(ros::ok()&&ch!='.'){
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
      case 65 : msg.linear.x = 1.5;
                break;
      case 66 : msg.linear.x = -1;5;
                break;
      case 67 : msg.angular.z = -1.5;
                break;
      case 68 : msg.angular.z = 1.5;
                break;
      case 'p': msg.linear.x = 0;
		break;
     }
     
     pub.publish(msg);
    }

   }


 
 }

 system("/bin/stty cooked");
return 0;
}
