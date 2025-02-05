#ifndef STANDALONE_MOTION_H
#define STANDALONE_MOTION_H

#include <ros/ros.h>

#include <std_msgs/String.h>

#include <nav_msgs/Odometry.h>

#include <tf/transform_datatypes.h>

#include <geometry_msgs/Quaternion.h> 
#include <geometry_msgs/PointStamped.h>
#include <sensor_msgs/PointCloud2.h>
#include <sensor_msgs/point_cloud2_iterator.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <robot_tools/tools.hpp> 
#include <vector>


// fonction d'envoi des cibles à moveBase
void moveBaseClient(ros::NodeHandle& nh);

// Fonction de rappel pour les feedbacks
void feedbackCb(const move_base_msgs::MoveBaseFeedback::ConstPtr& feedback);

#endif
