#include "robot_navigation/tf_process.hpp"

#include <tf/transform_broadcaster.h>
#include <tf/tf.h>
#include <geometry_msgs/Quaternion.h>
#include <geometry_msgs/Point.h>
#include <ros/ros.h>
#include <tf/transform_datatypes.h>
#include <nav_msgs/Odometry.h>
#include <robot_tools/tools.hpp>

int main(int argc, char** argv)
{
    ros::init(argc, argv, "publisherOdomEncoder");
    ros::NodeHandle n;
    
    ros::Rate loop_rate(0.01);

    tf::Vector3 positionXYZ, orientationRPY;
    // ligne réserver à la fonction d'auto calibration et de mise en position sur les aires de départ du robot selon l'équipe sélectionner.

    initializeFrame( tf::Vector3(0.02, 0.02, 0.0), tf::Vector3(0.0, 0.0, 0.0));
    
    nav_msgs::Odometry odometry, previous_odometry;
    ros::Publisher pub = n.advertise<nav_msgs::Odometry>("/odom/encoder", 10);

    float duration = 0;

    ros::Time current_time, last_time;
    current_time = ros::Time::now();
    last_time = ros::Time::now(); 

    while (ros::ok())
    {
        std::string data;
        current_time = ros::Time::now();  
        float speed_X, speed_Y;   
           
        try
        {
            std::string port = "/dev/ttyAMA1";
            if(receiveUART(data, port, 9600))
            {
                duration = stringToFloat(getDataFromJson( data, "duration"));
                odometry.header.stamp = current_time;
                odometry.header.frame_id = "odom";
                odometry.child_frame_id = "footprint";
                speed_X = stringToFloat(getDataFromJson( data, "speed_X"));
                speed_Y = stringToFloat(getDataFromJson( data, "speed_Y"));
                
                odometry.twist.twist.linear.x = speed_X;
                odometry.twist.twist.linear.y = speed_Y;
                odometry.twist.twist.angular.z = 0;
                
                odometry.pose.pose.position.x = previous_odometry.pose.pose.position.x + speed_X*duration;
                odometry.pose.pose.position.y = previous_odometry.pose.pose.position.y + speed_Y*duration;
                odometry.pose.pose.position.z = 0;
                pub.publish(odometry); 
                
                // last_time = current_time;
                geometry_msgs::Point position;
                position.x = odometry.pose.pose.position.x;
                position.y = odometry.pose.pose.position.y;
                position.z = odometry.pose.pose.position.z;
                previous_odometry.pose.pose.position = position;
                previous_odometry.pose.pose.orientation = odometry.pose.pose.orientation;

                ROS_INFO("position: \n X: %f, Y: %f, theta: 0", odometry.pose.pose.position.x, 
                                                                odometry.pose.pose.position.y);

            }
            else
            {
                last_time = current_time;
                ROS_INFO("Unable to get data from i2c multiplexer, please check multiplexer is connected !!!");
                loop_rate.sleep();
            }
        }catch (const std::runtime_error& e)
        {
            last_time = current_time;
            std::cerr << "Runtime error: " << e.what() << std::endl;
            
            ROS_INFO("Receiver UART motor receiver module, Runtime error: %s", e.what());
            
        }
        catch(const std::exception& e)
        {
            last_time = current_time;
            std::cerr << "Exception: " << e.what() << std::endl;
            
            ROS_INFO("Receiver UART, motor receiver module, Exception error: %s", e.what());
            
        }
        
        
         
        ros::spinOnce();
        loop_rate.sleep();

    }
}






