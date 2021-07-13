#include "ros/ros.h"
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/PoseWithCovariance.h>
#include <nav_msgs/Odometry.h>
#include <cmath>
#include <algorithm>
#include <random>
#include <cmath>

ros::Publisher pub;
void scanCallback(
		const nav_msgs::Odometry::ConstPtr &msg) {
            
            nav_msgs::Odometry msg1;
            
            std::random_device rd;
	    std::default_random_engine generator1;
            generator1.seed( rd() ); //Now this is seeded differently each time.
            std::normal_distribution<double> distribution1(0,0.05);
            
	    std::default_random_engine generator2;
            generator2.seed( rd() ); //Now this is seeded differently each time.
            std::normal_distribution<double> distribution2(0,5*(M_PI)/180);
            
            /*std::default_random_engine generator1;
	    std::normal_distribution<double> distribution1(0.20,0.05);
	    
	    std::default_random_engine generator2;
	    std::normal_distribution<double> distribution2(5*(M_PI)/180,2*(M_PI)/180);*/
            
            double a,b,c,x,y,z,w ;
            a= msg->pose.pose.position.x;
            b= msg->pose.pose.position.y;
            c= msg->pose.pose.position.z;
            
            x= msg->pose.pose.orientation.x;
            y= msg->pose.pose.orientation.y;
            z= msg->pose.pose.orientation.z;
            w= msg->pose.pose.orientation.w;
            
            double A,B,C,X,Y,Z;
            A= msg->twist.twist.linear.x;
            B= msg->twist.twist.linear.y;
            C= msg->twist.twist.linear.z;
            
            X= msg->twist.twist.angular.x;
            Y= msg->twist.twist.angular.y;
            Z= msg->twist.twist.angular.z;       
            
            double error1=distribution1(generator1);
            double error2=distribution2(generator2);
            
            a+=error1;
            b+=error1;
            c+=error1;
            
            x+=error2;
            y+=error2;
            z+=error2;
            w+=error2;
            
            /*A+=error1;
            B+=error1;
            C+=error1;
            
            X+=error2;
            Y+=error2;
            Z+=error2;*/      
            
            msg1.pose.pose.position.x=a;    
            msg1.pose.pose.position.y=b;
            msg1.pose.pose.position.z=c;
            
            msg1.pose.pose.orientation.x=x;
            msg1.pose.pose.orientation.y=y;
            msg1.pose.pose.orientation.z=z;
            msg1.pose.pose.orientation.w=w;
            
            msg1.twist.twist.linear.x=A;
            msg1.twist.twist.linear.y=B;
            msg1.twist.twist.linear.z=C;
            
            msg1.twist.twist.angular.x=X;
            msg1.twist.twist.angular.y=Y;
            msg1.twist.twist.angular.z=Z;
            
            msg1.header.seq = msg->header.seq;
            msg1.header.stamp = msg->header.stamp;
            msg1.header.frame_id = msg->header.frame_id;
	    msg1.child_frame_id = msg->child_frame_id;
            
            pub.publish(msg1);

	//ROS_INFO_STREAM_THROTTLE(2.0,"Working: " <<a<<" ");
        ROS_INFO("I heard: %lf",a);
}

int main(int argc, char** argv) {
  ros::init(argc, argv, "indy_odom_node");
  ros::NodeHandle nh("~");
  pub =nh.advertise<nav_msgs::Odometry>("noise_added", 100);
  ros::Subscriber sub = nh.subscribe("/carla/vehicle/086/odometry", 1000, scanCallback);
  

  ros::spin();
  return 0;
}
