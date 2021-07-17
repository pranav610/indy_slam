#pragma once

// ROS
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/PoseWithCovariance.h>
#include <nav_msgs/Odometry.h>

#include <cmath>
#include <algorithm>
#include <random>

namespace indy_slam {

/*!
 * Main class for the node to handle the ROS interfacing.
 */
class IndySlam
{
 public:
  /*!
   * Constructor.
   * @param nodeHandle the ROS node handle.
   */
  IndySlam(ros::NodeHandle& nh);

  /*!
   * Destructor.
   */
  virtual ~IndySlam();

 private:
  /*!
   * Reads and verifies the ROS parameters.
   * @return true if successful.
   */
  bool readParameters();

  /*!
   * ROS topic callback method.
   * @param message the received message.
   */
  void scanCallback(const nav_msgs::Odometry::ConstPtr &msg);

  //! ROS node handle.
  ros::NodeHandle& nodeHandle_;

  //! ROS topic subscriber.
  ros::Subscriber subscriber_;
  
  //! ROS topic publisher.
  ros::Publisher pub_;
  
  float mean_translational;
  float mean_rotational;
  float stddev_translational;
  float stddev_rotational;
};

} /* namespace */
