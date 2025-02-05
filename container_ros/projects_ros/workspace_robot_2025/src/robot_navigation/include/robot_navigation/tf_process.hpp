#include <tf/transform_broadcaster.h>
#include <tf/tf.h>
#include <geometry_msgs/Quaternion.h>
#include <geometry_msgs/Point.h>
// #include <geometry_msgs/Vector3.h>

#include <nav_msgs/Odometry.h>
#include <robot_tools/tools.hpp>



void initializeFrame(tf::Vector3 positionXYZ, tf::Vector3 orientationRPY);

void tfUpdate(const nav_msgs::Odometry::ConstPtr& msg);

nav_msgs::Odometry createOdometry(tf::Vector3 positionXYZ, tf::Vector3 orientationRPY);

