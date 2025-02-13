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

extern ros::Timer timer1;
extern ros::Timer timer2;
extern ros::Timer timer3;

void detect_launch();// fonction pour détecter le lancement manuel

void init_timer(ros::NodeHandle& nh);// fonction pour initialiser les timers

void timerCallback_Waiting_Camera_Capture(const ros::TimerEvent&);

void timerCallback_Warning_Time_Alarm(const ros::TimerEvent&);

void timerCallback_Stop_Time_Alarm(const ros::TimerEvent&);
