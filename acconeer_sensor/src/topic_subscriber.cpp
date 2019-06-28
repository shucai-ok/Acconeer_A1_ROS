#include "ros/ros.h"
#include "ros_tutorials_topic/sensData.h"

void chatterCallback(const ros_tutorials_topic::sensData::ConstPtr& msg)
{
  ROS_INFO("Sensor 1:");
	for (int i = 0; i<620;i++){
		printf("%u, ", (unsigned int)msg->sensor1[i]);
		if (i && !(i%8)){
			printf("\n");
		}
	}
	ROS_INFO("Sensor 2:");
	for (int i = 0; i<620;i++){
		printf("%u, ", (unsigned int)msg->sensor2[i]);
		if (i && !(i%8)){
			printf("\n");
		}
	}
	ROS_INFO("Sensor 3:");
	for (int i = 0; i<620;i++){
		printf("%u, ", (unsigned int)msg->sensor3[i]);
		if (i && !(i%8)){
			printf("\n");
		}
	}
	ROS_INFO("Sensor 4:");
	for (int i = 0; i<620;i++){
		printf("%u, ", (unsigned int)msg->sensor4[i]);
		if (i && !(i%8)){
			printf("\n");
		}
	}
}

int main(int argc, char **argv)
{

  ros::init(argc, argv, "listener");

  ros::NodeHandle n;

  ros::Subscriber sub = n.subscribe("chatter", 1000, chatterCallback);

  ros::spin();

  return 0;
}


