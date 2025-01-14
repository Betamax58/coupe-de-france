#include "../include/tf_process.hpp"


void tf_process::init(void)
        {
            frameOperatorMap.setPositionPoint(tf::vector3(0,0,0));
            frameOperatorMap.setFrameName("map");
            frameOperatorMap.setParentFrameName("map");
            frameOperatorOdom.setPositionPoint(tf::vector3(0,0,0));
            frameOperatorOdom.setFrameName("odom");
            frameOperatorOdom.setParentFrameName("map");
            frameOperatorFootprint.setPositionPoint(tf::vector3(0,0,0));
            frameOperatorFootprint.setFrameName("footprint");
            frameOperatorFootprint.setParentFrameName("odom");
            frameOperatorBase_link.setPositionPoint(tf::vector3(0,0,0));
            frameOperatorBase_link.setFrameName("base_link");
            frameOperatorBase_link.setParentFrameName("footprint");
            frameOperatorBase_laser.setPositionPoint(tf::vector3(0,0,0));
            frameOperatorBase_laser.setFrameName("base_laser");
            frameOperatorBase_laser.setParentFrameName("base_link");
            frameOperatorCameraFrameA.setPositionPoint(tf::vector3(0,0,0));
            frameOperatorCameraFrameA.setFrameName("cameraFrameA");
            frameOperatorCameraFrameA.setParentFrameName("base_link");
            frameOperatorCameraFrameB.setPositionPoint(tf::vector3(0,0,0));
            frameOperatorCameraFrameB.setFrameName("cameraFrameB");
            frameOperatorCameraFrameB.setParentFrameName("base_link");
            frameOperatorCameraFrameC.setPositionPoint(tf::vector3(0,0,0));
            frameOperatorCameraFrameC.setFrameName("cameraFrameC");
            frameOperatorCameraFrameC.setParentFrameName("base_link");
            frameOperatorTOF_frameA.setPositionPoint(tf::vector3(0,0,0));
            frameOperatorTOF_frameA.setFrameName("tof_frameA");
            frameOperatorTOF_frameA.setParentFrameName("base_link");
            frameOperatorTOF_frameB.setPositionPoint(tf::vector3(0,0,0));
            frameOperatorTOF_frameB.setFrameName("tof_frameB");
            frameOperatorTOF_frameB.setParentFrameName("base_link");
            frameOperatorTOF_frameC.setPositionPoint(tf::vector3(0,0,0));
            frameOperatorTOF_frameC.setFrameName("tof_frameC");
            frameOperatorTOF_frameC.setParentFrameName("base_link");
            frameOperatorTOF_frameD.setPositionPoint(tf::vector3(0,0,0));
            frameOperatorTOF_frameD.setFrameName("tof_frameD");
            frameOperatorTOF_frameD.setParentFrameName("base_link");
            frameOperatorTOF_frameE.setPositionPoint(tf::vector3(0,0,0));
            frameOperatorTOF_frameE.setFrameName("tof_frameE");
            frameOperatorTOF_frameE.setParentFrameName("base_link");
            frameOperatorTOF_frameF.setPositionPoint(tf::vector3(0,0,0));
            frameOperatorTOF_frameF.setFrameName("tof_frameF");
            frameOperatorTOF_frameF.setParentFrameName("base_link");
            frameOperatorTOF_frameG.setPositionPoint(tf::vector3(0,0,0));
            frameOperatorTOF_frameG.setFrameName("tof_frameG");
            frameOperatorTOF_frameG.setParentFrameName("base_link");
            frameOperatorTOF_frameH.setPositionPoint(tf::vector3(0,0,0));
            frameOperatorTOF_frameH.setFrameName("tof_frameH");
            frameOperatorTOF_frameH.setParentFrameName("base_link");
        }

void tf_process::initializeFrame()
{
    transformOperator.setChildFrame(this->frameOperatorFootprint);
    transformOperator.setParentFrame(this->frameOperatorOdom);
    this->frameOdometry = createOdometry(tf::vector3(0, 0, 0), tf::vector3(0, 0, 0));
    transformOperator.setOdometryTransform(this->frameOdometry);
    transformOperator.updateChildFrame();
    transformOperator.broadcastTransform();
    
    transformOperator.setChildFrame(this->frameOperatorBase_link);
    transformOperator.setParentFrame(this->frameOperatorFootprint);
    this->frameOdometry = createOdometry(tf::vector3(0, 0, 0), tf::vector3(0, 0, 0));
    transformOperator.setOdometryTransform(this->frameOdometry);
    transformOperator.updateChildFrame();
    transformOperator.broadcastTransform();

    transformOperator.setChildFrame(this->frameOperatorCameraFrameA);
    transformOperator.setParentFrame(this->frameOperatorBase_link);
    this->frameOdometry = createOdometry(tf::vector3(0, 0, 0), tf::vector3(0, 0, 0));
    transformOperator.setOdometryTransform(this->frameOdometry);
    transformOperator.updateChildFrame();
    transformOperator.broadcastTransform();

    transformOperator.setChildFrame(this->frameOperatorBase_link);
    transformOperator.setParentFrame(this->frameOperatorCameraFrameA);
    this->frameOdometry = createOdometry(tf::vector3(0, 0, 0), tf::vector3(0, 0, 0));
    transformOperator.setOdometryTransform(this->frameOdometry);
    transformOperator.updateChildFrame();
    transformOperator.broadcastTransform();

    transformOperator.setChildFrame(this->frameOperatorBase_link);
    transformOperator.setParentFrame(this->frameOperatorCameraFrameB);
    this->frameOdometry = createOdometry(tf::vector3(0, 0, 0), tf::vector3(0, 0, 0));
    transformOperator.setOdometryTransform(this->frameOdometry);
    transformOperator.updateChildFrame();
    transformOperator.broadcastTransform();

    transformOperator.setChildFrame(this->frameOperatorBase_link);
    transformOperator.setParentFrame(this->frameOperatorCameraFrameC);
    this->frameOdometry = createOdometry(tf::vector3(0, 0, 0), tf::vector3(0, 0, 0));
    transformOperator.setOdometryTransform(this->frameOdometry);
    transformOperator.updateChildFrame();
    transformOperator.broadcastTransform();

    transformOperator.setChildFrame(this->frameOperatorBase_link);
    transformOperator.setParentFrame(this->frameOperatorTOF_frameA);
    this->frameOdometry = createOdometry(tf::vector3(0, 0, 0), tf::vector3(0, 0, 0));
    transformOperator.setOdometryTransform(this->frameOdometry);
    transformOperator.updateChildFrame();
    transformOperator.broadcastTransform();

    transformOperator.setChildFrame(this->frameOperatorBase_link);
    transformOperator.setParentFrame(this->frameOperatorTOF_frameB);
    this->frameOdometry = createOdometry(tf::vector3(0, 0, 0), tf::vector3(0, 0, 0));
    transformOperator.setOdometryTransform(this->frameOdometry);
    transformOperator.updateChildFrame();
    transformOperator.broadcastTransform();

}


void tf_process::transformFrame(nav_msgs::Odometry frameOdometry)
{
    transformOperator.setChildFrame(this->frameOperatorFootprint);
    transformOperator.setParentFrame(this->frameOperatorOdom);
    this->frameOdometry = createOdometry(tf::vector3(0, 0, 0), tf::vector3(0, 0, 0));
    transformOperator.setOdometryTransform(frameOdometry);
    transformOperator.broadcastTransform();
    
    transformOperator.setChildFrame(this->frameOperatorBase_link);
    transformOperator.setParentFrame(this->frameOperatorFootprint);
    this->frameOdometry = createOdometry(tf::vector3(0, 0, 0), tf::vector3(0, 0, 0));
    transformOperator.setOdometryTransform(frameOdometry);
    transformOperator.broadcastTransform();

    transformOperator.setChildFrame(this->frameOperatorCameraFrameA);
    transformOperator.setParentFrame(this->frameOperatorBase_link);
    this->frameOdometry = createOdometry(tf::vector3(0, 0, 0), tf::vector3(0, 0, 0));
    transformOperator.setOdometryTransform(frameOdometry);
    transformOperator.broadcastTransform();

    transformOperator.setChildFrame(this->frameOperatorBase_link);
    transformOperator.setParentFrame(this->frameOperatorCameraFrameA);
    this->frameOdometry = createOdometry(tf::vector3(0, 0, 0), tf::vector3(0, 0, 0));
    transformOperator.setOdometryTransform(frameOdometry);
    transformOperator.broadcastTransform();

    transformOperator.setChildFrame(this->frameOperatorBase_link);
    transformOperator.setParentFrame(this->frameOperatorCameraFrameB);
    this->frameOdometry = createOdometry(tf::vector3(0, 0, 0), tf::vector3(0, 0, 0));
    transformOperator.setOdometryTransform(frameOdometry);
    transformOperator.broadcastTransform();

    transformOperator.setChildFrame(this->frameOperatorBase_link);
    transformOperator.setParentFrame(this->frameOperatorCameraFrameC);
    this->frameOdometry = createOdometry(tf::vector3(0, 0, 0), tf::vector3(0, 0, 0));
    transformOperator.setOdometryTransform(frameOdometry);
    transformOperator.broadcastTransform();

    transformOperator.setChildFrame(this->frameOperatorBase_link);
    transformOperator.setParentFrame(this->frameOperatorTOF_frameA);
    this->frameOdometry = createOdometry(tf::vector3(0, 0, 0), tf::vector3(0, 0, 0));
    transformOperator.setOdometryTransform(frameOdometry);
    transformOperator.broadcastTransform();

    transformOperator.setChildFrame(this->frameOperatorBase_link);
    transformOperator.setParentFrame(this->frameOperatorTOF_frameB);
    this->frameOdometry = createOdometry(tf::vector3(0, 0, 0), tf::vector3(0, 0, 0));
    transformOperator.setOdometryTransform(frameOdometry);
    transformOperator.broadcastTransform();

}


nav_msgs::Odometry createOdometry(tf::vector3 positionXYZ, tf::vector3 orientationRPY)
{
    nav_msgs::Odometry odometry;

    geometry_msgs::Point position;
    position.x = positionXYZ.x;
    position.y = positionXYZ.y;
    position.z = positionXYZ.z;
    odometry.pose.pose.position = position;
    
    geometry_msgs::Quaternion quaternion;
    quaternion.setRPY(orientationRPY.x, orientationRPY.y, orientationRPY.z);
    odometry.pose.pose.orientation = quaternion;
    
    return odometry;
}