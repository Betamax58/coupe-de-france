#include "robot_navigation/tf_process.hpp"

#include <tf/transform_broadcaster.h>
#include <tf/tf.h>
#include <geometry_msgs/Quaternion.h>
#include <geometry_msgs/Point.h>
#include <ros/ros.h>
#include <tf/transform_datatypes.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <robot_tools/tools.hpp>


extern geometry_msgs::PoseWithCovarianceStamped robotPoseFromAruco;
extern geometry_msgs::PoseWithCovarianceStamped robotPoseFromAMCL;
extern nav_msgs::Odometry wheelOdometry, robotOdometry;


void poseEncoderCallback(const nav_msgs::Odometry::ConstPtr& msg);

void poseCameraCallback(const geometry_msgs::PoseWithCovarianceStamped::ConstPtr& msg);

void pose_AMCL_Callback(const geometry_msgs::PoseWithCovarianceStamped::ConstPtr& msg);

bool processFusionPoseData(nav_msgs::Odometry& msg, ros::NodeHandle& nh);
