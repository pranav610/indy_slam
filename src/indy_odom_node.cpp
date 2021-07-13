#include "ros/ros.h"
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/PoseWithCovariance.h>
#include <nav_msgs/Odometry.h>
#include <cmath>
#include <algorithm>

void scanCallback(
		const nav_msgs::Odometry::ConstPtr &msg) {
            float a = msg->pose.pose.position.x;
            a+=10;

	
	//ROS_INFO_STREAM_THROTTLE(2.0,"Working: " <<a<<" ");
        ROS_INFO("I heard: %f",a);
}

int main(int argc, char** argv) {
  ros::init(argc, argv, "indy_odom_node");
  ros::NodeHandle nh("~");

  ros::Subscriber sub = nh.subscribe("/carla/vehicle/086/odometry", 1000, scanCallback);

  ros::spin();
  return 0;
}
