#include <ros/ros.h>
#include <laser_assembler/AssembleScans.h>
#include <sensor_msgs/Joy.h>

class MapManager{
  public:
    MapManager();
  private:
    ros::NodeHandle n;
    ros::ServiceClient client;
    ros::Publisher pub;
    ros::Subscriber sub;
    laser_assembler::AssembleScans srv;

    void joyCallback(sensor_msgs::Joy msg);
};

MapManager::MapManager(){
  ros::service::waitForService("assemble_scans");
  client = n.serviceClient<laser_assembler::AssembleScans>("assemble_scans");
  pub = n.advertise<sensor_msgs::PointCloud>("agregated_map",1);
  sub = n.subscribe<sensor_msgs::Joy>("joy",5,&MapManager::joyCallback,this);

}


void MapManager::joyCallback(sensor_msgs::Joy msg){

  if(msg.buttons[2]==1){
    srv.request.begin = ros::Time(0,0);
    srv.request.end = ros::Time::now();

    if (client.call(srv))
        printf("Got cloud with %u points\n", srv.response.cloud.points.size());
    else
        printf("Service call failed\n");

    pub.publish(srv.response.cloud);

  }

}


int main(int argc, char **argv)
{
  
  ros::init(argc, argv, "laser_mapper");
  
  MapManager mapman;

  ros::spin();
  return 0;
}


