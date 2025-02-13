#include <ros/ros.h>

#include <std_msgs/String.h>

#include <nav_msgs/Odometry.h>

#include <tf/transform_datatypes.h>

#include <geometry_msgs/Quaternion.h> 
#include <geometry_msgs/PointStamped.h>
#include <sensor_msgs/PointCloud2.h>
#include <sensor_msgs/point_cloud2_iterator.h>

#include <robot_tools/tools.hpp> 

#define SECURITY_DISTANCE 0.08 // distance de sécurité pour la détection d'obstacle signaler par le système de capteur tof

int main(int argc, char** argv)
{
    ros::init(argc, argv, "publisherTOF");
    ros::NodeHandle n;
    ros::Publisher pub = n.advertise<sensor_msgs::PointCloud2>("/tof_points", 1);
    ros::Rate loop_rate(0.1);


    std::string data, stringValue;
    float distance;

    while (ros::ok())
    {
        
        geometry_msgs::PointStamped pointInParentFrame;

        sensor_msgs::PointCloud2 cloud_msg;
        cloud_msg.header.stamp = ros::Time::now();
        cloud_msg.header.frame_id = "base_link";
        cloud_msg.height = 1;
        cloud_msg.width = 6; // 6 points
        // Définir les champs de données
        sensor_msgs::PointCloud2Modifier modifier(cloud_msg);

        modifier.setPointCloud2FieldsByString(2, "xyz", "rgb");

        // Remplir les données du point
        sensor_msgs::PointCloud2Iterator<float> iter_x(cloud_msg, "x");
        sensor_msgs::PointCloud2Iterator<float> iter_y(cloud_msg, "y");
        sensor_msgs::PointCloud2Iterator<float> iter_z(cloud_msg, "z");
        sensor_msgs::PointCloud2Iterator<uint8_t> iter_r(cloud_msg, "r");
        sensor_msgs::PointCloud2Iterator<uint8_t> iter_g(cloud_msg, "g");
        sensor_msgs::PointCloud2Iterator<uint8_t> iter_b(cloud_msg, "b");

        double securityDistance;
        try
        {
            std::string port = "/dev/ttyAMA1";
            if(receiveUART(data, port, 9600))
            {
                stringValue = getDataFromJson(data, "tof1");
                pointInParentFrame = getPositionPointFromParentFrame( "base_link", "tof_frameA", tf::Vector3( stringToFloat(stringValue), 0, 0));
                *iter_x = pointInParentFrame.point.x; // Coordonnée x
                *iter_y = pointInParentFrame.point.y; // Coordonnée y
                *iter_z = pointInParentFrame.point.z; // Coordonnée z
                *iter_r = 255; // Rouge
                *iter_g = 0;   // Vert
                *iter_b = 0;   // Bleu
                ++iter_x, ++iter_y, ++iter_z, ++iter_r, ++iter_g, ++iter_b;
                
                securityDistance = computeDistance(*iter_x, *iter_y, *iter_z);
                if(SECURITY_DISTANCE >= securityDistance)
                {n.setParam("/stuckForward", true);}
                else {
                    n.setParam("/stuckForward", false);
                }

                
                stringValue = getDataFromJson(data, "tof2");
                pointInParentFrame = getPositionPointFromParentFrame( "base_link", "tof_frameB", tf::Vector3( stringToFloat(stringValue), 0, 0));
                *iter_x = pointInParentFrame.point.x; // Coordonnée x
                *iter_y = pointInParentFrame.point.y; // Coordonnée y
                *iter_z = pointInParentFrame.point.z; // Coordonnée z
                *iter_r = 255; // Rouge
                *iter_g = 0;   // Vert
                *iter_b = 0;   // Bleu
                ++iter_x, ++iter_y, ++iter_z, ++iter_r, ++iter_g, ++iter_b;
                
                securityDistance = computeDistance(*iter_x, *iter_y, *iter_z);
                if(SECURITY_DISTANCE >= securityDistance)
                {n.setParam("/stuckForward", true);}
                else {
                    n.setParam("/stuckForward", false);
                }

                stringValue = getDataFromJson(data, "tof3");
                pointInParentFrame = getPositionPointFromParentFrame( "base_link", "tof_frameC", tf::Vector3( stringToFloat(stringValue), 0, 0));
                *iter_x = pointInParentFrame.point.x; // Coordonnée x
                *iter_y = pointInParentFrame.point.y; // Coordonnée y
                *iter_z = pointInParentFrame.point.z; // Coordonnée z
                *iter_r = 255; // Rouge
                *iter_g = 0;   // Vert
                *iter_b = 0;   // Bleu
                ++iter_x, ++iter_y, ++iter_z, ++iter_r, ++iter_g, ++iter_b;
                
                securityDistance = computeDistance(*iter_x, *iter_y, *iter_z);
                if(SECURITY_DISTANCE >= securityDistance)
                {n.setParam("/stuckRight", true);}
                else {
                    n.setParam("/stuckRight", false);
                }
                
                
                stringValue = getDataFromJson(data, "tof4");
                pointInParentFrame = getPositionPointFromParentFrame( "base_link", "tof_frameD", tf::Vector3( stringToFloat(stringValue), 0, 0));
                *iter_x = pointInParentFrame.point.x; // Coordonnée x
                *iter_y = pointInParentFrame.point.y; // Coordonnée y
                *iter_z = pointInParentFrame.point.z; // Coordonnée z
                *iter_r = 255; // Rouge
                *iter_g = 0;   // Vert
                *iter_b = 0;   // Bleu
                ++iter_x, ++iter_y, ++iter_z, ++iter_r, ++iter_g, ++iter_b;
                
                securityDistance = computeDistance(*iter_x, *iter_y, *iter_z);
                if(SECURITY_DISTANCE >= securityDistance)
                {n.setParam("/stuckBackward", true);}
                else {
                    n.setParam("/stuckBackward", false);
                }

                stringValue = getDataFromJson(data, "tof5");
                pointInParentFrame = getPositionPointFromParentFrame( "base_link", "tof_frameE", tf::Vector3( stringToFloat(stringValue), 0, 0));
                *iter_x = pointInParentFrame.point.x; // Coordonnée x
                *iter_y = pointInParentFrame.point.y; // Coordonnée y
                *iter_z = pointInParentFrame.point.z; // Coordonnée z
                *iter_r = 255; // Rouge
                *iter_g = 0;   // Vert
                *iter_b = 0;   // Bleu
                ++iter_x, ++iter_y, ++iter_z, ++iter_r, ++iter_g, ++iter_b;
                
                securityDistance = computeDistance(*iter_x, *iter_y, *iter_z);
                if(SECURITY_DISTANCE >= securityDistance)
                {n.setParam("/stuckBackward", true);}
                else {
                    n.setParam("/stuckBackward", false);
                }

                stringValue = getDataFromJson(data, "tof6");
                pointInParentFrame = getPositionPointFromParentFrame( "base_link", "tof_frameF", tf::Vector3( stringToFloat(stringValue), 0, 0));
                *iter_x = pointInParentFrame.point.x; // Coordonnée x
                *iter_y = pointInParentFrame.point.y; // Coordonnée y
                *iter_z = pointInParentFrame.point.z; // Coordonnée z
                *iter_r = 255; // Rouge
                *iter_g = 0;   // Vert
                *iter_b = 0;   // Bleu
                
                securityDistance = computeDistance(*iter_x, *iter_y, *iter_z);
                if(SECURITY_DISTANCE >= securityDistance)
                {n.setParam("/stuckLeft", true);}
                else {
                    n.setParam("/stuckLeft", false);
                }

                pub.publish(cloud_msg);
                ros::spin();
                loop_rate.sleep();

            }
            else
            {
                ROS_INFO("Unable to get data from i2c multiplexer, please check multiplexer is connected !!!");
                loop_rate.sleep();
            }
        }catch (const std::runtime_error& e)
        {
            std::cerr << "Runtime error: " << e.what() << std::endl;
            
            ROS_INFO("Receiver UART Runtime error: %s", e.what());
            
        }
        catch(const std::exception& e)
        {
            std::cerr << "Exception: " << e.what() << std::endl;
            
            ROS_INFO("Receiver UART Exception error: %s", e.what());
            
        }
        
    }
}
