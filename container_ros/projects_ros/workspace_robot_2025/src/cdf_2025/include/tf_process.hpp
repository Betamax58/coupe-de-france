#ifndef TF_PROCESS_H
#define TF_PROCESS_H

#include "../include/operator.hpp"

class tf_process
{
    private:
        nav_msgs::Odometry frameOdometry;

        TransformOperator transformOperator;
        FrameOperator frameOperatorOdom, frameOperatorFootprint, frameOperatorBase_link,
                  frameOperatorCameraFrameA, frameOperatorCameraFrameB, frameOperatorCameraFrameC,
                  frameOperatorTOF_frameA, frameOperatorTOF_frameB, frameOperatorTOF_frameC,
                  frameOperatorTOF_frameD, frameOperatorTOF_frameE, frameOperatorTOF_frameF,
                  frameOperatorTOF_frameG,frameOperatorTOF_frameH, frameOperatorBase_laser,
                  frameOperatorMap; 
    
    public:
        void init(void);
        void initializeFrame(void);
        nav_msgs::Odometry createOdometry(tf::vector3 position, tf::vector3 orientationRPY);
        
        

};

#endif // TF_PROCESS_H