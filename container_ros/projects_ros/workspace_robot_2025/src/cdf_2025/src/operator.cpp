#include "../include/operator.hpp"


void FrameOperator::setFrameName(std_msgs::String name)
{
    this->frameName = name;
}


void FrameOperator::setParentFrameName(std_msgs::String name)
{
    this->parentFrameName = name;
}


void FrameOperator::setPositionPoint(geometry_msg::vector3 vector)
{
    this->x_position_point = vector.x;
    this->y_position_point = vector.y;
    this->z_position_point = vector.z;
}


geometry_msg::vector3 FrameOperator::getPositionPointFromParentFrame(void)
{
    geometry_msgs::PointStamped point_child_frame;
    point_child_frame.header.frame_id = this->parentFrameName;

    point_child_frame.header.stamp = ros::Time();

    point_child_frame.point.x = this->x_position_point;
    point_child_frame.point.y = this->y_position_point;
    point_child_frame.point.z = this->z_position_point;

    try
    {
        geometry_msgs::PointStamped point_parent_frame;
        this->listener.transformPoint(this->parentFrameName, point_child_frame, point_parent_frame);

        ROS_INFO("point_child_frame: (%.2f, %.2f. %.2f) -----> point_parent_frame: (%.2f, %.2f, %.2f) at time %.2f",
                point_child_frame.point.x, 
                point_child_frame.point.y, 
                point_child_frame.point.z,
                point_parent_frame.point.x, 
                point_parent_frame.point.y, 
                point_parent_frame.point.z, 
                point_parent_frame.header.stamp.toSec());
    }
    catch(tf::TransformException& ex)
    {
        ROS_ERROR("Received an exception trying to transform a point from \"point_child_frame\" to \"point_parent_frame\": %s", ex.what());
    }
}


std_msgs::String FrameOperator::getParentFrameName(void)
{
    return this->parentFrameName;
}


std_msgs::String FrameOperator::getFrameName(void)
{
    return this->frameName;
}


void FrameOperator::setFrameTransform(tf::Transform transform)
{
    this->frameTransform = transform;
}


nav_msgs::Odometry MotionOperator::getWheelsOdometry(void)
{

}


void MotionOperator::setMotionMode(std_msgs::Bool motionMode)
{
    this->motionMode = motionMode;
}


void MotionOperator::updateWheelsOdometry(void)
{

}


tf::StampTransform TransformOperator::getFrameTransformation(void)
{
    tf::StampTransform transform;
    
    try
    {
        // determination d'un objet tf::StampTransform entre child frame et parent frame
        this->listener.lookupTransform(this->parentFrame.getFrameName(), 
                                        this->childFrame.getFrameName(), 
                                        ros::Time(0), transform);
     
    }
    catch (tf::TransformException &ex) 
    {
        ROS_ERROR("%s",ex.what());
        ros::Duration(1.0).sleep();
    //   continue;
    }
    
    return transform;
}


void TransformOperator::setChildFrame(FrameOperator childFrame)
{
    this->childFrame = childFrame;
}


void TransformOperator::setParentFrame(FrameOperator parentFrame)
{
    this->parentFrame = parentFrame;
}


void TransformOperator::setOdometryTransform(nav_msgs::Odometry odometryTransform)
{
    this->odometryTransform = odometryTransform;
}

tf::Transform TransformOperator::updateChildFrame(void)
{
    tf::Transform transform;

    // Translation entre les 2 repères et les axes (x, y, z).
    //< mise en place des offsets sur les axes x,y,z.
    transform.setOrigin(tf::Vector3(
                        this->odometryTransform.pose.pose.position.x,
                        this->odometryTransform.pose.pose.position.y,
                        this->odometryTransform.pose.pose.position.z ));
    
    // rotation autour de X, Y, Z avec le quaternion entre les 2 repères.
    transform.setRotation(this->odometryTransform.pose.pose.orientation);
    
    this->odometryTransform.pose.pose.position.x = 0;
    this->odometryTransform.pose.pose.position.x = 0;
    this->odometryTransform.pose.pose.position.x = 0;
    this->odometryTransform.pose.pose.orientation = tf::Quaternion(0,0,0,1);

    return transform;
}


void TransformOperator::broadcastTransform(void)
{
    

    // publication d'objet de type tf::Transform concernant un child frame et parent frame.
    this->broadcaster.sendTransform(tf::StampedTransform(TransformOperator::updateChildFrame(), 
                                                        ros::Time::now(), 
                                                        this->parentFrame, 
                                                        this->childFrame));
}

