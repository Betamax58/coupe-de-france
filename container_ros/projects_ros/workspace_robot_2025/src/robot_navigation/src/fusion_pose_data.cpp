#include "robot_navigation/fusion_pose_data.hpp"


geometry_msgs::PoseWithCovarianceStamped robotPoseFromAruco, robotPoseFromAMCL;
bool robotPoseFromAruco_bool, robotPoseFromAMCL_bool;
nav_msgs::Odometry wheelOdometry, robotOdometry;


int main(int argc, char** argv)
{
    ros::init(argc, argv, "fusionOdomData");
    ros::NodeHandle n;
    
    ros::Rate loop_rate(0.01);

    tf::Vector3 positionXYZ, orientationRPY;
    // ligne réserver à la fonction d'auto calibration et de mise en position sur les aires de départ du robot selon l'équipe sélectionner.

    initializeFrame( tf::Vector3(0.02, 0.02, 0.0), tf::Vector3(0.0, 0.0, 0.0));
    
    nav_msgs::Odometry odometry, previous_odometry;
    
    ros::Subscriber sub_pose_AMCL = n.subscribe("amcl_pose", 10, pose_AMCL_Callback);
    ros::Subscriber sub_pose_camera = n.subscribe("/pose/camera", 10, poseCameraCallback);
    ros::Subscriber sub_pose_encoder = n.subscribe("/odom/encoder", 10, poseEncoderCallback);
    ros::Publisher pub = n.advertise<nav_msgs::Odometry>("/odom/robot", 10);
    
    
    float duration = 0;
    

    ros::Time current_time, last_time;
    current_time = ros::Time::now();
    last_time = ros::Time::now(); 

    while (ros::ok())
    {
        std::string data;
        current_time = ros::Time::now();  
        // float speed_X, speed_Y;   
        // n.getParam("/movebase_online", movebase_online);   
        
        if(processFusionPoseData(odometry, n))
        {
            pub.publish(odometry);
            n.setParam("/currentPosition_x", odometry.pose.pose.position.x);// coordonnée X courante
            n.setParam("/currentPosition_y", odometry.pose.pose.position.y);// coordonnée Y courante
            
            // Conversion du quaternion en angles de lacet, tangage, roulis
            tf::Quaternion tf_quat;
            tf::quaternionMsgToTF(odometry.pose.pose.orientation, tf_quat);
            double roll, pitch, yaw;
            tf::Matrix3x3(tf_quat).getRPY(roll, pitch, yaw);
            n.setParam("/currentOrientation", yaw);// orientation courante 
        }
        else {
            ROS_INFO("position processing fusion data problem");
        }
        
        
        ros::spinOnce();
        loop_rate.sleep();
    }
}

void pose_AMCL_Callback(const geometry_msgs::PoseWithCovarianceStamped::ConstPtr& msg)
{
    if(!robotPoseFromAMCL_bool)
    {
        robotPoseFromAMCL = *msg;
        robotPoseFromAMCL_bool = true;
    }
    
}

void poseCameraCallback(const geometry_msgs::PoseWithCovarianceStamped::ConstPtr& msg)
{
    if(!robotPoseFromAruco_bool)
    {
        robotPoseFromAruco = *msg;
        geometry_msgs::PointStamped getPositionPointFromParentFrame(const std::string& parentFrameName, const std::string& childFrameName, tf::Vector3 pointInChildFrame);
        robotPoseFromAruco_bool = true;
    }
    
}

void poseEncoderCallback(const nav_msgs::Odometry::ConstPtr& msg)
{
    wheelOdometry = *msg;
}


bool processFusionPoseData(nav_msgs::Odometry& msg, ros::NodeHandle& nh)
{
    bool movebase_online;
    
    try
    {
        nh.getParam("/movebase_online", movebase_online); 
        
        if ((msg.twist.twist.linear.x == 0)&&(msg.twist.twist.linear.y == 0)) 
        {
            ROS_INFO("no motion detect by encoder");
            
            return false;
        }else if(movebase_online)
        {
            if(robotPoseFromAruco_bool && robotPoseFromAMCL_bool)
            {
                geometry_msgs::PointStamped robotPose;
                robotPose = getPositionPointFromParentFrame("base_link", "cameraFrameA", tf::Vector3(robotPoseFromAruco.pose.pose.position.x, robotPoseFromAruco.pose.pose.position.y, robotPoseFromAruco.pose.pose.position.z));

                
                wheelOdometry.pose.pose.position.x = 0.1*(wheelOdometry.pose.pose.position.x + (wheelOdometry.twist.twist.linear.x)*(wheelOdometry.header.stamp).toSec()) + 0.7*(robotPose.point.x) + 0.2*(robotPoseFromAMCL.pose.pose.position.x);
                wheelOdometry.pose.pose.position.y = 0.1*(wheelOdometry.pose.pose.position.y + (wheelOdometry.twist.twist.linear.y)*(wheelOdometry.header.stamp).toSec()) + 0.7*(robotPose.point.y) + 0.2*(robotPoseFromAMCL.pose.pose.position.y);
                wheelOdometry.pose.pose.position.z = 0;
                
            }
            else if (robotPoseFromAruco_bool) 
            {
                geometry_msgs::PointStamped robotPose;
                robotPose = getPositionPointFromParentFrame("base_link", "cameraFrameA", tf::Vector3(robotPoseFromAruco.pose.pose.position.x, robotPoseFromAruco.pose.pose.position.y, robotPoseFromAruco.pose.pose.position.z));

                
                wheelOdometry.pose.pose.position.x = 0.1*(wheelOdometry.pose.pose.position.x + (wheelOdometry.twist.twist.linear.x)*(wheelOdometry.header.stamp).toSec()) + 0.9*(robotPose.point.x);
                wheelOdometry.pose.pose.position.y = 0.1*(wheelOdometry.pose.pose.position.y + (wheelOdometry.twist.twist.linear.y)*(wheelOdometry.header.stamp).toSec()) + 0.9*(robotPose.point.y);
                wheelOdometry.pose.pose.position.z = 0;


            }
            else if (robotPoseFromAMCL_bool) 
            {
                wheelOdometry.pose.pose.position.x = 0.4*(wheelOdometry.pose.pose.position.x + (wheelOdometry.twist.twist.linear.x)*(wheelOdometry.header.stamp).toSec()) + 0.6*(robotPoseFromAMCL.pose.pose.position.x);
                wheelOdometry.pose.pose.position.y = 0.4*(wheelOdometry.pose.pose.position.x + (wheelOdometry.twist.twist.linear.y)*(wheelOdometry.header.stamp).toSec()) + 0.6*(robotPoseFromAMCL.pose.pose.position.y);
                wheelOdometry.pose.pose.position.z = 0;
            }
            
            
            msg.pose.pose.position = wheelOdometry.pose.pose.position;
            msg.twist.twist.linear = wheelOdometry.twist.twist.linear;
            msg.twist.twist.angular = wheelOdometry.twist.twist.angular;
            msg.pose.pose.orientation = wheelOdometry.pose.pose.orientation;
                
            ROS_INFO("position: \n X: %f, Y: %f, theta: unknow", wheelOdometry.pose.pose.position.x, 
                                                            wheelOdometry.pose.pose.position.y);
            

        }
        else 
        {
            if (robotPoseFromAruco_bool) 
            {
                geometry_msgs::PointStamped robotPose;
                robotPose = getPositionPointFromParentFrame("base_link", "cameraFrameA", tf::Vector3(robotPoseFromAruco.pose.pose.position.x, robotPoseFromAruco.pose.pose.position.y, robotPoseFromAruco.pose.pose.position.z));

                
                wheelOdometry.pose.pose.position.x = 0.1*(wheelOdometry.pose.pose.position.x + (wheelOdometry.twist.twist.linear.x)*(wheelOdometry.header.stamp).toSec()) + 0.9*(robotPose.point.x);
                wheelOdometry.pose.pose.position.y = 0.1*(wheelOdometry.pose.pose.position.x + (wheelOdometry.twist.twist.linear.y)*(wheelOdometry.header.stamp).toSec()) + 0.9*(robotPose.point.y);
                wheelOdometry.pose.pose.position.z = 0;
                msg.pose.pose.position = wheelOdometry.pose.pose.position;
                msg.twist.twist.linear = wheelOdometry.twist.twist.linear;
                msg.twist.twist.angular = wheelOdometry.twist.twist.angular;
                msg.pose.pose.orientation = wheelOdometry.pose.pose.orientation;
                 ROS_INFO("position: \n X: %f, Y: %f, theta: unknow", wheelOdometry.pose.pose.position.x, 
                                                            wheelOdometry.pose.pose.position.y);
            
                

            }
            else
            {
                wheelOdometry.pose.pose.position.x = wheelOdometry.pose.pose.position.x + (wheelOdometry.twist.twist.linear.x)*((wheelOdometry.header.stamp).toSec());
                wheelOdometry.pose.pose.position.y = wheelOdometry.pose.pose.position.y + (wheelOdometry.twist.twist.linear.y)*((wheelOdometry.header.stamp).toSec());
                wheelOdometry.pose.pose.position.z = 0;
                msg.pose.pose.position = wheelOdometry.pose.pose.position;
                msg.twist.twist.linear = wheelOdometry.twist.twist.linear;
                msg.twist.twist.angular = wheelOdometry.twist.twist.angular;
                msg.pose.pose.orientation = wheelOdometry.pose.pose.orientation;
                 ROS_INFO("position: \n X: %f, Y: %f, theta: unknow", wheelOdometry.pose.pose.position.x, 
                                                            wheelOdometry.pose.pose.position.y);
                
            }

            
           
            

        }
         return true;   
        
    }catch (const std::runtime_error& e)
    {
        
        std::cerr << "Runtime error: " << e.what() << std::endl;
        
        ROS_INFO("fusion pose data module, Runtime error: %s", e.what());
        return false; 
        
    }
    catch(const std::exception& e)
    {
        
        std::cerr << "Exception: " << e.what() << std::endl;
        
        ROS_INFO("fusion pose data module, Exception error: %s", e.what());
        return false; 
        
    }

    
}

