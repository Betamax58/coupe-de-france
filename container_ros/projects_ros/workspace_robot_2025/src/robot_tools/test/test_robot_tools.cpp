#include <gtest/gtest.h>
#include <tf/transform_broadcaster.h>
#include <tf/tf.h>
#include <geometry_msgs/Quaternion.h>
#include <geometry_msgs/Point.h>
#include "robot_tools/tools.h"
// #include "robot_navigation/tf_process.hpp"


nav_msgs::Odometry createOdometry(tf::Vector3 positionXYZ, tf::Vector3 orientationRPY);

TEST(MyProgramTest, TestFunction_getPositionPointFromParentFrame) {
    
    nav_msgs::Odometry odometryTransform = createOdometry(tf::Vector3(1,1,1), tf::Vector3(0,0,0));
    tf::Transform frameTransform;
    tf::TransformBroadcaster broadcaster;
    
    // Translation entre les 2 repères et les axes (x, y, z).
    //< mise en place des offsets sur les axes x,y,z.
    frameTransform.setOrigin(tf::Vector3(
                        odometryTransform.pose.pose.position.x,
                        odometryTransform.pose.pose.position.y,
                        odometryTransform.pose.pose.position.z ));

    // rotation autour de X, Y, Z avec le quaternion entre les 2 repères.
    tf::Quaternion tf_quat;
    tf::quaternionMsgToTF(odometryTransform.pose.pose.orientation, tf_quat);
    frameTransform.setRotation(tf_quat);

    broadcaster.sendTransform(tf::StampedTransform(frameTransform, 
                                                    ros::Time::now(), 
                                                    "map", 
                                                    "odom"));
    
    geometry_msgs::PointStamped pointStamped; 
    pointStamped = getPositionPointFromParentFrame("map", "odom", tf::Vector3(0,0,0))

    EXPECT_EQ(1, pointStamped.point.x);
    EXPECT_EQ(1, pointStamped.point.Y);
    EXPECT_EQ(1, pointStamped.point.Z);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

nav_msgs::Odometry createOdometry(tf::Vector3 positionXYZ, tf::Vector3 orientationRPY)
{
    nav_msgs::Odometry odometry;

    geometry_msgs::Point position;
    position.x = positionXYZ.x();
    position.y = positionXYZ.y();
    position.z = positionXYZ.z();
    odometry.pose.pose.position = position;
    
    tf::Quaternion quaternion;
    quaternion.setRPY(orientationRPY.x(), orientationRPY.y(), orientationRPY.z());
    geometry_msgs::Quaternion odom_quat;
    tf::quaternionTFToMsg(quaternion, odom_quat);
    odometry.pose.pose.orientation = odom_quat;
    
    return odometry;
}