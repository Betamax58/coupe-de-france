#include "robot_motion/motion_tools.hpp"


MotionService::MotionService::Request last_req; 
MotionService::MotionService::Response last_res;

bool motionMode, motionServerService_bool, sub_movebase_bool, sub_moveride_bool;

int main(int argc, char** argv)
{
    ros::init(argc, argv, "control_motion");
    ros::NodeHandle n;
    ros::Rate loopRate(0.01);
    ros::Rate loopRateWait(1);

    ros::Publisher pub = n.advertise<geometry_msgs::Twist>("moveride_cmd_vel", 10);

    while (ros::ok())
    {
        
        try
        {
            bool motionMode, statusMotion;
            n.getParam("/motionMode", motionMode);
            n.getParam("/statusMotion", statusMotion);
            if((!motionMode)&&(statusMotion))
            {
                motionServerService_bool = true;
            }
            
            if(motionServerService_bool)
            {
                
                bool controlMotionEnd, stuckBackward, stuckForward, stuckRight, stuckLeft;
                   
                for(size_t i = 0; i <= 5; i++)
                {
                    n.getParam("/stuckForward", stuckForward);
                    n.getParam("/stuckBackward", stuckBackward);
                    n.getParam("/stuckRight", stuckRight);
                    n.getParam("/stuckLeft", stuckLeft);
                    if((!stuckForward)||(!stuckBackward)||(!stuckRight)||(!stuckLeft))
                    {
                        geometry_msgs::Twist cmd_twist;
                        cmd_twist = motionCommand();
                        pub.publish(cmd_twist);
                        n.setParam("/controlMotionEnd", false);
                    }
                    else 
                    {
                        
                        geometry_msgs::Twist cmd_twist;
                        cmd_twist = motionCommand(last_req.axisXdistance, last_req.axisYdistance, last_req.axisZrotation, 5);// 5 est la durée de la commande de vitesse inscrite dans la boucle for
                        pub.publish(cmd_twist);
                        
                    }
                    loopRateWait.sleep();// attendre 1 seconde entre l'envoi des différentes consignes de vitesse.
                }
                
                // ROS_INFO("Request: distance_X=%ld, distance_Y=%ld, orientation_Z=%ld", 
                //         (long int)res.axisXdistance, (long int)res.axisYdistance, (long int)res.axisZrotation);
                // ROS_INFO("Sending back response: distance_X =%ld, \t distance_Y =%ld, \t orientation_Z =%ld,\n
                //         stuckForward=%s, \t stuckBackward=%s, \t stuckRight=%s, \t stuckLeft=%s", 
                //         (long int)res.axisXdistanceDone, (long int)res.axisYdistanceDone, (long int)res.axisZrotationDone, 
                //         res.stuckForward ? "true" : "false", res.stuckBackward ? "true" : "false" , res.stuckRight ? "true" : "false" , res.stuckLeft ? "true" : "false");
                
                motionServerService_bool = false;

                n.setParam("/statusMotion", false);
            }
        }
        catch (const std::runtime_error& e)
        {
            std::cerr << "Runtime error: " << e.what() << std::endl;
            
            ROS_INFO("control motion Runtime error: %s", e.what());
            
        }
        catch(const std::exception& e)
        {
            std::cerr << "Exception: " << e.what() << std::endl;
            
            ROS_INFO("control motion Exception error: %s", e.what());
            
        }
        loopRate.sleep();
    }
}




