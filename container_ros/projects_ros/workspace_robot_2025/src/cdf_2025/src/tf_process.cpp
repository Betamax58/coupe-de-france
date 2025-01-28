// #include "../include/tf_process.hpp"
#include "tf_process.hpp"

void tf_process::init(void)
        {
            std_msgs::String nameStd_msgs;
            
            this->frameOperatorMap.setPositionPoint(tf::Vector3(0,0,0));
            nameStd_msgs.data = "map";
            this->frameOperatorMap.setFrameName(nameStd_msgs);
            nameStd_msgs.data = "world";
            this->frameOperatorMap.setParentFrameName(nameStd_msgs);
            this->frameOperatorAruco_base_A.setPositionPoint(tf::Vector3(0,0,0));
            nameStd_msgs.data = "aruco_A_base";
            this->frameOperatorAruco_base_A.setFrameName(nameStd_msgs);
            nameStd_msgs.data = "map";
            this->frameOperatorAruco_base_A.setParentFrameName(nameStd_msgs);
            this->frameOperatorAruco_base_B.setPositionPoint(tf::Vector3(0,0,0));
            nameStd_msgs.data = "aruco_B_base";
            this->frameOperatorAruco_base_B.setFrameName(nameStd_msgs);
            nameStd_msgs.data = "map";
            this->frameOperatorAruco_base_B.setParentFrameName(nameStd_msgs);
            this->frameOperatorAruco_base_C.setPositionPoint(tf::Vector3(0,0,0));
            nameStd_msgs.data = "aruco_C_base";
            this->frameOperatorAruco_base_C.setFrameName(nameStd_msgs);
            nameStd_msgs.data = "map";
            this->frameOperatorAruco_base_C.setParentFrameName(nameStd_msgs);
            this->frameOperatorAruco_base_D.setPositionPoint(tf::Vector3(0,0,0));
            nameStd_msgs.data = "aruco_D_base";
            this->frameOperatorAruco_base_D.setFrameName(nameStd_msgs);
            nameStd_msgs.data = "map";
            this->frameOperatorAruco_base_D.setParentFrameName(nameStd_msgs);
            this->frameOperatorOdom.setPositionPoint(tf::Vector3(0,0,0));
            nameStd_msgs.data = "odom";
            this->frameOperatorOdom.setFrameName(nameStd_msgs);
            nameStd_msgs.data = "map";
            this->frameOperatorOdom.setParentFrameName(nameStd_msgs);
            this->frameOperatorFootprint.setPositionPoint(tf::Vector3(0,0,0));
            nameStd_msgs.data = "footprint";
            this->frameOperatorFootprint.setFrameName(nameStd_msgs);
            nameStd_msgs.data = "odom";
            this->frameOperatorFootprint.setParentFrameName(nameStd_msgs);
            this->frameOperatorBase_link.setPositionPoint(tf::Vector3(0,0,0));
            nameStd_msgs.data = "base_link";
            this->frameOperatorBase_link.setFrameName(nameStd_msgs);
            nameStd_msgs.data = "footprint";
            this->frameOperatorBase_link.setParentFrameName(nameStd_msgs);
            this->frameOperatorBase_laser.setPositionPoint(tf::Vector3(0,0,0));
            nameStd_msgs.data = "base_laser";
            this->frameOperatorBase_laser.setFrameName(nameStd_msgs);
            nameStd_msgs.data = "base_link";
            this->frameOperatorBase_laser.setParentFrameName(nameStd_msgs);
            this->frameOperatorCameraFrameA.setPositionPoint(tf::Vector3(0,0,0));
            nameStd_msgs.data = "cameraFrameA";
            this->frameOperatorCameraFrameA.setFrameName(nameStd_msgs);
            nameStd_msgs.data = "base_link";
            this->frameOperatorCameraFrameA.setParentFrameName(nameStd_msgs);
            this->frameOperatorCameraFrameB.setPositionPoint(tf::Vector3(0,0,0));
            nameStd_msgs.data = "cameraFrameB";
            this->frameOperatorCameraFrameB.setFrameName(nameStd_msgs);
            nameStd_msgs.data = "base_link";
            this->frameOperatorCameraFrameB.setParentFrameName(nameStd_msgs);
            this->frameOperatorCameraFrameC.setPositionPoint(tf::Vector3(0,0,0));
            nameStd_msgs.data = "cameraFrameC";
            this->frameOperatorCameraFrameC.setFrameName(nameStd_msgs);
            nameStd_msgs.data = "base_link";
            this->frameOperatorCameraFrameC.setParentFrameName(nameStd_msgs);
            this->frameOperatorTOF_frameA.setPositionPoint(tf::Vector3(0,0,0));
            nameStd_msgs.data = "tof_frameA";
            this->frameOperatorTOF_frameA.setFrameName(nameStd_msgs);
            nameStd_msgs.data = "base_link";
            this->frameOperatorTOF_frameA.setParentFrameName(nameStd_msgs);
            this->frameOperatorTOF_frameB.setPositionPoint(tf::Vector3(0,0,0));
            nameStd_msgs.data = "tof_frameB";
            this->frameOperatorTOF_frameB.setFrameName(nameStd_msgs);
            nameStd_msgs.data = "base_link";
            this->frameOperatorTOF_frameB.setParentFrameName(nameStd_msgs);
            this->frameOperatorTOF_frameC.setPositionPoint(tf::Vector3(0,0,0));
            nameStd_msgs.data = "tof_frameC";
            this->frameOperatorTOF_frameC.setFrameName(nameStd_msgs);
            nameStd_msgs.data = "base_link";
            this->frameOperatorTOF_frameC.setParentFrameName(nameStd_msgs);
            this->frameOperatorTOF_frameD.setPositionPoint(tf::Vector3(0,0,0));
            nameStd_msgs.data = "tof_frameD";
            this->frameOperatorTOF_frameD.setFrameName(nameStd_msgs);
            nameStd_msgs.data = "base_link";
            this->frameOperatorTOF_frameD.setParentFrameName(nameStd_msgs);
            this->frameOperatorTOF_frameE.setPositionPoint(tf::Vector3(0,0,0));
            nameStd_msgs.data = "tof_frameE";
            this->frameOperatorTOF_frameE.setFrameName(nameStd_msgs);
            nameStd_msgs.data = "base_link";
            this->frameOperatorTOF_frameE.setParentFrameName(nameStd_msgs);
            this->frameOperatorTOF_frameF.setPositionPoint(tf::Vector3(0,0,0));
            nameStd_msgs.data = "base_link";
            this->frameOperatorTOF_frameF.setFrameName(nameStd_msgs);
            nameStd_msgs.data = "base_link";
            this->frameOperatorTOF_frameF.setParentFrameName(nameStd_msgs);
            this->frameOperatorTOF_frameG.setPositionPoint(tf::Vector3(0,0,0));
            // frameOperatorTOF_frameG.setFrameName("tof_frameG");
            // frameOperatorTOF_frameG.setParentFrameName("base_link");
            // frameOperatorTOF_frameH.setPositionPoint(tf::Vector3(0,0,0));
            // frameOperatorTOF_frameH.setFrameName("tof_frameH");
            // frameOperatorTOF_frameH.setParentFrameName("base_link");
        }

void tf_process::initializeFrame(tf::Vector3 positionXYZ, tf::Vector3 orientationRPY)
{
    TransformOperator transformOperator;

    transformOperator.setChildFrame(this->frameOperatorAruco_base_A);
    transformOperator.setParentFrame(this->frameOperatorMap);
    this->frameOdometry = createOdometry(tf::Vector3(1, 1, 0), tf::Vector3(0, 0, 0));
    transformOperator.setOdometryTransform(this->frameOdometry);
    // transformOperator.updateChildFrame();
    transformOperator.broadcastTransform();


    transformOperator.setChildFrame(this->frameOperatorAruco_base_B);
    transformOperator.setParentFrame(this->frameOperatorMap);
    this->frameOdometry = createOdometry(tf::Vector3(1, 5, 0), tf::Vector3(0, 0, 0));
    transformOperator.setOdometryTransform(this->frameOdometry);
    transformOperator.broadcastTransform();


    transformOperator.setChildFrame(this->frameOperatorAruco_base_C);
    transformOperator.setParentFrame(this->frameOperatorMap);
    this->frameOdometry = createOdometry(tf::Vector3(5, 1, 0), tf::Vector3(0, 0, 0));
    transformOperator.setOdometryTransform(this->frameOdometry);
    transformOperator.broadcastTransform();


    transformOperator.setChildFrame(this->frameOperatorAruco_base_D);
    transformOperator.setParentFrame(this->frameOperatorMap);
    this->frameOdometry = createOdometry(tf::Vector3(5, 5, 0), tf::Vector3(0, 0, 0));
    transformOperator.setOdometryTransform(this->frameOdometry);
    transformOperator.broadcastTransform();

    transformOperator.setChildFrame(this->frameOperatorFootprint);
    transformOperator.setParentFrame(this->frameOperatorOdom);
    this->frameOdometry = createOdometry(tf::Vector3(0, 0, 0), tf::Vector3(0, 0, 0));
    transformOperator.setOdometryTransform(this->frameOdometry);
    transformOperator.broadcastTransform();
    
    transformOperator.setChildFrame(this->frameOperatorBase_link);
    transformOperator.setParentFrame(this->frameOperatorFootprint);
    this->frameOdometry = createOdometry(tf::Vector3(0.0, 0.0, 0.3), tf::Vector3(0, 0, 0));
    transformOperator.setOdometryTransform(this->frameOdometry);
    transformOperator.broadcastTransform();

    transformOperator.setChildFrame(this->frameOperatorCameraFrameA);
    transformOperator.setParentFrame(this->frameOperatorBase_link);
    this->frameOdometry = createOdometry(tf::Vector3(0, 0.3, 0.2), tf::Vector3(0, (10/180)*(this->PI), 0));
    transformOperator.setOdometryTransform(this->frameOdometry);
    transformOperator.broadcastTransform();

    // transformOperator.setChildFrame(this->frameOperatorBase_link);
    // transformOperator.setParentFrame(this->frameOperatorCameraFrameA);
    // this->frameOdometry = createOdometry(tf::Vector3(0, 0, 0), tf::Vector3(0, 0, 0));
    // transformOperator.setOdometryTransform(this->frameOdometry);
    // transformOperator.updateChildFrame();
    // transformOperator.broadcastTransform();

    transformOperator.setParentFrame(this->frameOperatorBase_link);
    transformOperator.setChildFrame(this->frameOperatorCameraFrameB);
    this->frameOdometry = createOdometry(tf::Vector3(0.3, 0, 0.2), tf::Vector3(0, (10/180)*(this->PI), (-90/180)*(this->PI)));
    transformOperator.setOdometryTransform(this->frameOdometry);
    transformOperator.broadcastTransform();

    transformOperator.setParentFrame(this->frameOperatorBase_link);
    transformOperator.setChildFrame(this->frameOperatorCameraFrameC);
    this->frameOdometry = createOdometry(tf::Vector3(-0.3, 0, 0.2), tf::Vector3(0, (10/180)*(this->PI), (90/180)*(this->PI)));
    transformOperator.setOdometryTransform(this->frameOdometry);
    transformOperator.broadcastTransform();

    transformOperator.setParentFrame(this->frameOperatorBase_link);
    transformOperator.setChildFrame(this->frameOperatorTOF_frameA);
    this->frameOdometry = createOdometry(tf::Vector3(-0.02, 0.2, 0.01), tf::Vector3(0, 0, 0));
    transformOperator.setOdometryTransform(this->frameOdometry);
    transformOperator.broadcastTransform();

    transformOperator.setParentFrame(this->frameOperatorBase_link);
    transformOperator.setChildFrame(this->frameOperatorTOF_frameB);
    this->frameOdometry = createOdometry(tf::Vector3(0.02, 0.2, 0.01), tf::Vector3(0, 0, 0));
    transformOperator.setOdometryTransform(this->frameOdometry);
    transformOperator.broadcastTransform();

    transformOperator.setParentFrame(this->frameOperatorBase_link);
    transformOperator.setChildFrame(this->frameOperatorTOF_frameC);
    this->frameOdometry = createOdometry(tf::Vector3(0.02, 0, 0.01), tf::Vector3(0, 0, (-90/180)*(this->PI)));
    transformOperator.setOdometryTransform(this->frameOdometry);
    transformOperator.broadcastTransform();

    transformOperator.setParentFrame(this->frameOperatorBase_link);
    transformOperator.setChildFrame(this->frameOperatorTOF_frameD);
    this->frameOdometry = createOdometry(tf::Vector3(0.02, -0.2, 0.01), tf::Vector3(0, 0, (-180/180)*(this->PI)));
    transformOperator.setOdometryTransform(this->frameOdometry);
    
    transformOperator.broadcastTransform();

    transformOperator.setParentFrame(this->frameOperatorBase_link);
    transformOperator.setChildFrame(this->frameOperatorTOF_frameE);
    this->frameOdometry = createOdometry(tf::Vector3(-0.02, -0.2, 0.01), tf::Vector3(0, 0, (-180/180)*(this->PI)));
    transformOperator.setOdometryTransform(this->frameOdometry);
    transformOperator.broadcastTransform();

    transformOperator.setParentFrame(this->frameOperatorBase_link);
    transformOperator.setChildFrame(this->frameOperatorTOF_frameF);
    this->frameOdometry = createOdometry(tf::Vector3(-0.02, 0, 0.01), tf::Vector3(0, 0, (90/180)*(this->PI)));
    transformOperator.setOdometryTransform(this->frameOdometry); 
    transformOperator.broadcastTransform();

    transformOperator.setParentFrame(this->frameOperatorBase_link);
    transformOperator.setChildFrame(this->frameOperatorBase_laser);
    this->frameOdometry = createOdometry(tf::Vector3(0, 0, 0.4), tf::Vector3(0, 0, 0));
    transformOperator.setOdometryTransform(this->frameOdometry);
    transformOperator.broadcastTransform();


}


void tf_process::transformFrame(nav_msgs::Odometry frameOdometry)
{
    TransformOperator transformOperator;

    // transformOperator.setChildFrame(this->frameOperatorAruco_base_A);
    // transformOperator.setParentFrame(this->frameOperatorMap);
    // this->frameOdometry = createOdometry(tf::Vector3(1, 1, 0), tf::Vector3(0, 0, 0));
    // transformOperator.setOdometryTransform(this->frameOdometry);
    // transformOperator.updateChildFrame();
    // transformOperator.broadcastTransform();


    // transformOperator.setChildFrame(this->frameOperatorAruco_base_B);
    // transformOperator.setParentFrame(this->frameOperatorMap);
    // this->frameOdometry = createOdometry(tf::Vector3(1, 5, 0), tf::Vector3(0, 0, 0));
    // transformOperator.setOdometryTransform(this->frameOdometry);
    // transformOperator.updateChildFrame();
    // transformOperator.broadcastTransform();


    // transformOperator.setChildFrame(this->frameOperatorAruco_base_C);
    // transformOperator.setParentFrame(this->frameOperatorMap);
    // this->frameOdometry = createOdometry(tf::Vector3(5, 1, 0), tf::Vector3(0, 0, 0));
    // transformOperator.setOdometryTransform(this->frameOdometry);
    // transformOperator.updateChildFrame();
    // transformOperator.broadcastTransform();


    // transformOperator.setChildFrame(this->frameOperatorAruco_base_D);
    // transformOperator.setParentFrame(this->frameOperatorMap);
    // this->frameOdometry = createOdometry(tf::Vector3(5, 5, 0), tf::Vector3(0, 0, 0));
    // transformOperator.setOdometryTransform(this->frameOdometry);
    // transformOperator.updateChildFrame();
    // transformOperator.broadcastTransform();
    
    
    transformOperator.setChildFrame(this->frameOperatorFootprint);
    transformOperator.setParentFrame(this->frameOperatorOdom);
    // this->frameOdometry = createOdometry(tf::Vector3(0, 0, 0), tf::Vector3(0, 0, 0));
    transformOperator.setOdometryTransform(frameOdometry);
    transformOperator.broadcastTransform();
    
    transformOperator.setChildFrame(this->frameOperatorBase_link);
    transformOperator.setParentFrame(this->frameOperatorFootprint);
    this->frameOdometry = createOdometry(tf::Vector3(0.0, 0.0, 0.3), tf::Vector3(0, 0, 0));
    transformOperator.setOdometryTransform(frameOdometry);
    transformOperator.broadcastTransform();

    transformOperator.setChildFrame(this->frameOperatorCameraFrameA);
    transformOperator.setParentFrame(this->frameOperatorBase_link);
    this->frameOdometry = createOdometry(tf::Vector3(0, 0.3, 0.2), tf::Vector3(0, (10/180)*(this->PI), 0));
    transformOperator.setOdometryTransform(frameOdometry);
    transformOperator.broadcastTransform();

    transformOperator.setChildFrame(this->frameOperatorCameraFrameB);
    transformOperator.setParentFrame(this->frameOperatorBase_link);
    this->frameOdometry = createOdometry(tf::Vector3(0.3, 0, 0.2), tf::Vector3(0, (10/180)*(this->PI), (-90/180)*(this->PI)));
    transformOperator.setOdometryTransform(frameOdometry);
    transformOperator.broadcastTransform();

    transformOperator.setChildFrame(this->frameOperatorCameraFrameC);
    transformOperator.setParentFrame(this->frameOperatorBase_link);
    this->frameOdometry = createOdometry(tf::Vector3(-0.3, 0, 0.2), tf::Vector3(0, (10/180)*(this->PI), (90/180)*(this->PI)));
    transformOperator.setOdometryTransform(frameOdometry);
    transformOperator.broadcastTransform();

    // transformOperator.setChildFrame(this->frameOperatorCameraFrameC);
    // transformOperator.setParentFrame(this->frameOperatorBase_link);
    // // this->frameOdometry = createOdometry(tf::Vector3(0, 0, 0), tf::Vector3(0, 0, 0));
    // transformOperator.setOdometryTransform(frameOdometry);
    // transformOperator.broadcastTransform();

    transformOperator.setChildFrame(this->frameOperatorTOF_frameA);
    transformOperator.setParentFrame(this->frameOperatorBase_link);
    this->frameOdometry = createOdometry(tf::Vector3(0.3, 0, 0.2), tf::Vector3(0, (10/180)*(this->PI), (-90/180)*(this->PI)));
    transformOperator.setOdometryTransform(frameOdometry);
    transformOperator.broadcastTransform();

    transformOperator.setChildFrame(this->frameOperatorTOF_frameB);
    transformOperator.setParentFrame(this->frameOperatorBase_link);
    this->frameOdometry = createOdometry(tf::Vector3(0.3, 0, 0.2), tf::Vector3(0, (10/180)*(this->PI), (-90/180)*(this->PI)));
    transformOperator.setOdometryTransform(frameOdometry);
    transformOperator.broadcastTransform();

    transformOperator.setParentFrame(this->frameOperatorBase_link);
    transformOperator.setChildFrame(this->frameOperatorTOF_frameC);
    this->frameOdometry = createOdometry(tf::Vector3(0, 0, 0), tf::Vector3(0, 0, 0));
    transformOperator.setOdometryTransform(this->frameOdometry);
    
    transformOperator.broadcastTransform();

    transformOperator.setParentFrame(this->frameOperatorBase_link);
    transformOperator.setChildFrame(this->frameOperatorTOF_frameD);
    this->frameOdometry = createOdometry(tf::Vector3(0, 0, 0), tf::Vector3(0, 0, 0));
    transformOperator.setOdometryTransform(this->frameOdometry);
    transformOperator.broadcastTransform();

    transformOperator.setParentFrame(this->frameOperatorBase_link);
    transformOperator.setChildFrame(this->frameOperatorTOF_frameE);
    this->frameOdometry = createOdometry(tf::Vector3(0, 0, 0), tf::Vector3(0, 0, 0));
    transformOperator.setOdometryTransform(this->frameOdometry);
    transformOperator.broadcastTransform();

    transformOperator.setParentFrame(this->frameOperatorBase_link);
    transformOperator.setChildFrame(this->frameOperatorTOF_frameF);
    this->frameOdometry = createOdometry(tf::Vector3(0, 0, 0), tf::Vector3(0, 0, 0));
    transformOperator.setOdometryTransform(this->frameOdometry);
    transformOperator.broadcastTransform();

    transformOperator.setParentFrame(this->frameOperatorBase_link);
    transformOperator.setChildFrame(this->frameOperatorBase_laser);
    this->frameOdometry = createOdometry(tf::Vector3(0, 0, 0.4), tf::Vector3(0, 0, 0));
    transformOperator.setOdometryTransform(this->frameOdometry);
    transformOperator.broadcastTransform();

}


nav_msgs::Odometry tf_process::createOdometry(tf::Vector3 positionXYZ, tf::Vector3 orientationRPY)
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