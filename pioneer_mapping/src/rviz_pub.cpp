#include<ros/ros.h>
#include<tf/transform_broadcaster.h>
#include<geometry_msgs/Twist.h>
#include <pthread.h>

class Test {
    public:

        }

    private:
        void RunMe() {
            printf("%p: %p is running.\n", pthread_self(), this);
        }
};



class MapTransform{
  public:
    MapTransform();
    void odomStart();
    static void* Run(void* me) {
      static_cast<Test*>(me)->RunMe();
      return NULL;

  private:
    void velCallback(const geometry_msgs::Twist msg);

    float odomX,odomY,odomA,dt,velX,velA;
    ros::NodeHandle n;
    ros::Subscriber vel_sub;
    tf::TransformBroadcaster broadcaster;
    geometry_msgs::TransformStamped odom_trans;


};


MapTransform::MapTransform(){
  odomX = odomY = odomA = 0;
  dt = 1/30;
  vel_sub = n.subscribe<geometry_msgs::Twist>("cmd_vel",100,&MapTransform::velCallback,this);
  ROS_INFO("constructor check");


}

void MapTransform::odomStart(){
  //ros::Rate r(30);
  ROS_INFO("into odomStart");

    odomX += cos(odomA)*velX*dt;
    odomY += sin(odomA)*velX*dt;
    odomA += velA*dt;

    odom_trans.header.frame_id = "Map";
    odom_trans.child_frame_id = "base_link";
    odom_trans.header.stamp = ros::Time::now();

    odom_trans.transform.translation.x = odomX;
    odom_trans.transform.translation.y = odomY;
    odom_trans.transform.rotation = tf::createQuaternionMsgFromYaw(odomA);
    ROS_INFO("in the odomStart loop");
    broadcaster.sendTransform(odom_trans);
    //r.sleep();
  

}

void MapTransform::velCallback(const geometry_msgs::Twist msg){
  velX = msg.linear.x;
  velA = msg.angular.z;
  ROS_INFO("into velCallback");
}


int main(int argc, char **argv){

  ros::init(argc,argv,"rviz_publisher");

  pthread_t tid;
  Test test;

  ROS_INFO("in main");
  MapTransform mapTransform;

  ROS_INFO("after creating object");
  ros::spin();

  return 0;
}
