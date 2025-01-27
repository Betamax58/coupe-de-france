#include <thread>

#include <queue>

#include <mutex>

#include <ros/ros.h>

#include <condition_variable>

#include <cdf_2025/MotionService.h>

#include <move_base_msgs/MoveBaseAction.h>

#include <actionlib/client/simple_action_client.h>

void feedbackCb(const move_base_msgs::MoveBaseFeedback::ConstPtr& feedback);

void moveBaseThread();

void secondProgramThread();
