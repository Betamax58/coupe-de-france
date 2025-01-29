#ifndef NODE_H
#define NODE_H

#include "addons.hpp"
#include "process.hpp"
#include "operator.hpp"
#include "tf_process.hpp"

#include <sstream>
#include <stdexcept>

#include <ros/ros.h>

#include <std_msgs/String.h>

#include <nav_msgs/Odometry.h>

#include <tf/transform_datatypes.h>

#include <geometry_msgs/Quaternion.h>

#include <sensor_msgs/LaserScan.h>

#include <sensor_msgs/PointCloud2.h>
#include <sensor_msgs/point_cloud2_iterator.h>

void publisherOdometry(int argc, char** argv);
void publisherTF(int argc, char** argv);
void publisherCameraData(int argc, char** argv);
void publisherTOFData(int argc, char** argv);
void publisherLidarData(int argc, char** argv);
void publisherVelocity(int argc, char** argv);
void publisherMotion(int argc, char** argv);
void publisherMonitoring(int argc, char** argv);
void subscriberOdometry(int argc, char** argv);
void subscriberTF(int argc, char** argv);
void subscriberMotionControl(int argc, char** argv);
void subscriberSensor(int argc, char** argv);
void chatterCallback(const std_msgs::String::ConstPtr& msg);
void laserScanCallback(const sensor_msgs::LaserScan::ConstPtr& scan);

#endif // NOM_FICHIER_H