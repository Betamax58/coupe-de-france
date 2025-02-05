#ifndef MOTION_TOOLS_H
#define MOTION_TOOLS_H

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

#include <MotionService/MotionService.h>

#define SPEED_FILTER_LIMIT_VALUE 0.05

extern bool sub_movebase_bool, sub_moveride_bool, motionMode, motionServerService_bool;

extern bool motionMode;

extern MotionService::MotionService::Request last_req; 
extern MotionService::MotionService::Response last_res;

extern geometry_msgs::Twist movebase_twist, moveride_twist;

void motionClient(tf::Vector3 motionRequest, tf::Vector3& motionResponse, std::vector<std_msgs::Bool>& stuckResponse, ros::NodeHandle& n);

void motionServer(ros::NodeHandle& n);

bool motionServerServiceCallback(MotionService::MotionService::Request &req,
                   MotionService::MotionService::Response &res);


void motionServerSubscriberCallback(const geometry_msgs::Twist::ConstPtr& msg);


void moverideSubscriberCallback(const geometry_msgs::Twist::ConstPtr& msg);

void movebaseSubscriberCallback(const geometry_msgs::Twist::ConstPtr& msg);


geometry_msgs::Twist motionCommand(double cmd_x=0, double cmd_y=0, double cmd_z=0, double time=1);


#endif
