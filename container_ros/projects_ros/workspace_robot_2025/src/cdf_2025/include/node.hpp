#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>

#ifndef NODE_H
#define NODE_H

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

#endif // NOM_FICHIER_H