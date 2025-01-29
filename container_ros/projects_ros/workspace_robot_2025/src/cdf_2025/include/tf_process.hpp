#ifndef TF_PROCESS_H
#define TF_PROCESS_H

// #include "../include/operator.hpp"
#include "operator.hpp"

#include <tf/transform_broadcaster.h>
#include <tf/tf.h>
#include <geometry_msgs/Quaternion.h>
#include <geometry_msgs/Point.h>
// #include <geometry_msgs/Vector3.h>

#include <nav_msgs/Odometry.h>




class tf_process
{
    private:
        const double PI = 3.14159265358979323846;
        
        nav_msgs::Odometry frameOdometry;

        TransformOperator transformOperator;
        FrameOperator frameOperatorOdom, frameOperatorFootprint, frameOperatorBase_link,
                  frameOperatorCameraFrameA, frameOperatorCameraFrameB, frameOperatorCameraFrameC,
                  frameOperatorTOF_frameG,frameOperatorTOF_frameH, frameOperatorBase_laser,
                  frameOperatorAruco_base_A, frameOperatorAruco_base_B, frameOperatorAruco_base_C,
                  frameOperatorAruco_base_D, frameOperatorMap; 
    
    public:
        FrameOperator frameOperatorTOF_frameA, frameOperatorTOF_frameB, frameOperatorTOF_frameC,
        frameOperatorTOF_frameD, frameOperatorTOF_frameE, frameOperatorTOF_frameF;
        
        void init(void);
        void initializeFrame(tf::Vector3 positionXYZ, tf::Vector3 orientationRPY);
        void transformFrame(nav_msgs::Odometry frameOdometry);
        nav_msgs::Odometry createOdometry(tf::Vector3 positionXYZ, tf::Vector3 orientationRPY);
        

};

#endif // TF_PROCESS_H