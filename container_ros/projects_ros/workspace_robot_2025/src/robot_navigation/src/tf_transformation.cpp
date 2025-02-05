#include <ros/ros.h>

#include <std_msgs/String.h>

#include <nav_msgs/Odometry.h>

#include <tf/transform_datatypes.h>

#include <geometry_msgs/Quaternion.h> 
#include <geometry_msgs/PointStamped.h>
#include <sensor_msgs/PointCloud2.h>
#include <sensor_msgs/point_cloud2_iterator.h>

#include <robot_tools/tools.hpp> 

#include "robot_navigation/tf_process.hpp"

int main(int argc, char** argv)
{
    ros::init(argc, argv, "publisherTF");
    ros::NodeHandle n;
    
    ros::Rate loop_rate(0.1);

    tf::Vector3 positionXYZ, orientationRPY;
    // ligne réserver à la fonction d'auto calibration et de mise en position sur les aires de départ du robot selon l'équipe sélectionner.

    initializeFrame( tf::Vector3(0.02, 0.02, 0.0), tf::Vector3(0.0, 0.0, 0.0));
    ros::Subscriber sub = n.subscribe("/odom/robot", 10, tfUpdate);
       

    while (ros::ok())
    {
        
                
        // try
        // {
        //     if(receiveUART(data, "/dev/ttyAMA1", 9600))
        //     {
                
                
                
                

        //     }
        //     else
        //     {
        //         ROS_INFO("Unable to get data from i2c multiplexer, please check multiplexer is connected !!!");
        //         loop_rate.sleep();
        //     }
        // }catch (const std::runtime_error& e)
        // {
        //     std::cerr << "Runtime error: " << e.what() << std::endl;
            
        //     ROS_INFO("Receiver UART Runtime error: %s", e.what());
            
        // }
        // catch(const std::exception& e)
        // {
        //     std::cerr << "Exception: " << e.what() << std::endl;
            
        //     ROS_INFO("Receiver UART Exception error: %s", e.what());
            
        // }
        
        ros::spinOnce();
        loop_rate.sleep();

    }
}
