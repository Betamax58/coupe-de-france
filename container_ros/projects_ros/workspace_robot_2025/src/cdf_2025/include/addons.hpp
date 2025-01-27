#include <thread>
#include <queue>
#include <mutex>
#include <vector>
#include <sstream>
#include <fcntl.h>
#include <unistd.h>
#include <ros/ros.h>
#include <termios.h>
#include <std_msgs/Bool.h>
#include <nlohmann/json.hpp>
#include <condition_variable>
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Pose2D.h>
#include <geometry_msgs/Vector3.h>
#include <geometry_msgs/Point32.h>
#include <tf/transform_datatypes.h>
#include <sensor_msgs/PointCloud.h>
#include <cdf_2025/MotionService.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <tf/transform_broadcaster.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/TransformStamped.h>

#define SPEED_FILTER_LIMIT_VALUE 0.05

using json = nlohmann::json;

extern std::queue<std::string> message_queue_capture;
extern std::queue<std::string> message_queue_mode;
extern std::queue<std::string> message_queue_move_base;
extern std::queue<std::string> message_queue_subpub_TOF;
extern std::queue<std::string> message_queue;
extern std::mutex queue_mutex;
extern std::mutex motion_mutex;
extern std::mutex uart_mutex_motor;
extern std::mutex uart_mutex_gripper;
extern std::mutex uart_mutex_sensor;
extern std::condition_variable queue_cond_var;
extern bool motionMode;
extern geometry_msgs::Twist cmdVelocity;


void feedbackCb(const move_base_msgs::MoveBaseFeedback::ConstPtr& feedback);

void moveBaseThread();

void guiProgramThread();

void mainProgramThread();

void objectCaptureProgramThread();

void monitoringModeProgramThread();

std::string getDataFromJson(const std::string& jsonString, const std::string& key);

std::string convertStringIntoJson(const std::vector<std::string>& keys, const std::vector<std::string>& values);

std::string floatToString(float value);

float stringToFloat(const std::string& str);

void callbackItemPose(const geometry_msgs::Pose::ConstPtr& msg);

void callbackTOF(const sensor_msgs::PointCloud::ConstPtr& msg);

void subscriberItemPose(int argc, char** argv);

void subscriberTOF(int argc, char** argv);

geometry_msgs::Pose2D createPose2D(double x, double y, double theta);

std::vector<geometry_msgs::Pose2D> createPose2DList();

std::string pose2DListToJson(const std::vector<geometry_msgs::Pose2D>& pose_list);

void sendJsonToQueue(const std::string& json_str, std::queue<std::string>& queue);

geometry_msgs::Pose2D getPose2DFromJson(const std::string& json_str, size_t index);

std::string getUserInputAndConvertToJson();

void motionServer();

void motionClient(tf::Vector3 motionRequest, tf::Vector3& motionResponse, std::vector<std_msgs::Bool>& stuckResponse);


bool motionServerServiceCallback(cdf_2025::MotionService::Request &req,
                   cdf_2025::MotionService::Response &res);

void motionServerSubscriberCallback(const geometry_msgs::Twist::ConstPtr& msg);

void stabilizer();

void tfUpdate(const nav_msgs::Odometry::ConstPtr& msg);


