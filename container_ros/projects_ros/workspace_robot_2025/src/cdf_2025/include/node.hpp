#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>

#ifndef NODE_H
#define NODE_H

void publisherOdometry(void);
void publisherTF(void);
void publisherCameraData(void);
void publisherTOFData(void);
void publisherLidarData(void);
void publisherVelocity(void);
void publisherMotion(void);
void publisherMonitoring(void);
void subscriberOdometry(void);
void subscriberTF(void);
void subscriberMotionControl(void);
void subscriberSensor(void);

#endif // NOM_FICHIER_H