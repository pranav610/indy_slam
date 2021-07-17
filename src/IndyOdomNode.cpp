/*#include "indy_slam/IndySlam.hpp"
#include <cmath>
#include <algorithm>
#include <random>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/PoseWithCovariance.h>
#include <nav_msgs/Odometry.h>

namespace indy_slam{
IndySlam::IndySlam(ros::NodeHandle& nh):
	 nodeHandle_(nh)
{
	if(!readParameters()){
	ROS_ERROR("Could not read parameters.");
        ros::requestShutdown();
	}
	
	pub_=nodeHandle_.advertise<nav_msgs::Odometry>("noise_added", 100);
	
	subscriber_=nodeHandle_.subscribe("/carla/vehicle/086/odometry", 100, &IndySlam::scanCallback,this);
	
	ROS_INFO("Successfully launched node.");
}

IndySlam::~IndySlam()
{
}

bool IndySlam::readParameters()
{
	bool success = true;
	success &= nodeHandle_.getParam("/indy_slam/transalational_mean", mean_translational);
	success &= nodeHandle_.getParam("/indy_slam/rotational_mean", mean_rotational);	
	success &= nodeHandle_.getParam("/indy_slam/transalation_stddev", stddev_translational);
	success &= nodeHandle_.getParam("/indy_slam/rotational_stddev", stddev_rotational);
	
	return success; 
}

void IndySlam::scanCallback(const nav_msgs::Odometry::ConstPtr &msg)
{
	nav_msgs::Odometry msg1;
	msg1.pose=msg->pose;
	
	std::random_device rd;
	
    	std::default_random_engine generator1;
        generator1.seed( rd() ); //Now this is seeded differently each time.
        std::normal_distribution<double> distribution1(mean_translational,stddev_translational);
            
	std::default_random_engine generator2;
        generator2.seed( rd() ); //Now this is seeded differently each time.
        std::normal_distribution<double> distribution2(mean_rotational,stddev_rotational);
        
        float error1=distribution1(generator1);
        float error2=distribution2(generator2);
        
        msg1.pose.pose.position.x+=error1;
        msg1.pose.pose.position.y+=error1;
        msg1.pose.pose.position.z+=error1;
        
        msg1.pose.pose.orientation.x+=error2;
        msg1.pose.pose.orientation.y+=error2;
        msg1.pose.pose.orientation.z+=error2;
        msg1.pose.pose.orientation.w+=error2;
        
        pub_.publish(msg1);

        ROS_INFO("I heard: %f",msg1.pose.pose.position.x);
}

}*/






