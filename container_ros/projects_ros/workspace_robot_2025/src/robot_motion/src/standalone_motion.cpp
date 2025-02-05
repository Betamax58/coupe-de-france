#include "robot_motion/standalone_motion.hpp"


int main(int argc, char** argv)
{
    ros::init(argc, argv, "standalone_motion");
    ros::NodeHandle n;
    ros::Rate loopRate(0.01);

    while (ros::ok())
    {
        
        try
        {
            bool motionMode;
            n.getParam("/motionMode", motionMode);
            if(motionMode)
            {
                moveBaseClient(n);
            }
        }
        catch (const std::runtime_error& e)
        {
            std::cerr << "Runtime error: " << e.what() << std::endl;
            
            ROS_INFO("moveBse Runtime error: %s", e.what());
            
        }
        catch(const std::exception& e)
        {
            std::cerr << "Exception: " << e.what() << std::endl;
            
            ROS_INFO("moveBse Exception error: %s", e.what());
            
        }
        loopRate.sleep();
    }
}

// fonction d'envoi des cibles à moveBase
void moveBaseClient(ros::NodeHandle& nh) {
    
    float value;
    // std::vector<float> valueList;
    tf::Vector3 position;

    // Définir l'alias pour MoveBaseClient
    typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

    MoveBaseClient ac("move_base", true);

    

    bool statusMotion;
    // Récupérer un paramètre booléen
    nh.getParam("/statusMotion", statusMotion);
    
    if(statusMotion==true)
    {
        
        ROS_INFO("Waiting for the move_base action server to come up");
        
        ac.waitForServer();

        
        
            
        nh.getParam("/targetPosition_x", value);
        position.setX(value);// coordonnée X
        nh.getParam("/targetPosition_y", value);
        position.setY(value);// coordonnée Y
        nh.getParam("/targetPosition_z", value);
        position.setZ(value);// coordonnée d'orientation sur l'axe Z
            
            
            
            
        
        
        if((position.x() <= 0)&&(position.y() <= 0)&&(statusMotion==true))
        {
            ROS_INFO("The robot get invalid goal coordinate, so the robot don't move.");
            
            // Définir un paramètre booléen
            nh.setParam("/statusMoveBaseEnd", true);
            nh.setParam("/statusMotion", false);
        }
        else
        {    
            move_base_msgs::MoveBaseGoal goal;
            goal.target_pose.header.frame_id = "map";
            goal.target_pose.header.stamp = ros::Time::now();
            
            
            goal.target_pose.pose.position.x = position.x();
            goal.target_pose.pose.position.y = position.y();
            goal.target_pose.pose.orientation.w = position.z();
            

            
            ROS_INFO("Sending goal");
            
            
            ac.sendGoal(goal, MoveBaseClient::SimpleDoneCallback(), MoveBaseClient::SimpleActiveCallback(), &feedbackCb);

            ac.waitForResult();

            if (ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
            {
                
                ROS_INFO("The robot reached the goal!");
                
                
                // Définir un paramètre booléen
                nh.setParam("/statusMoveBaseEnd", true);
                nh.setParam("/statusMotion", false);
                
            }
            else
            {
                
                ROS_INFO("The robot failed to reach the goal.");
                
                // Définir un paramètre booléen
                nh.setParam("/statusMoveBaseEnd", true);
                nh.setParam("/statusMotion", false);
                
                
            }
                
            ros::spinOnce();
        }
        
    }
    
    nh.setParam("/targetPosition_x", 0);
    position.setX(value);// coordonnée X
    nh.setParam("/targetPosition_y", 0);
    position.setY(value);// coordonnée Y    


}


// Fonction de rappel pour les feedbacks
void feedbackCb(const move_base_msgs::MoveBaseFeedback::ConstPtr& feedback) 
{
    tf::Quaternion tf_quat;
    tf::quaternionMsgToTF(feedback->base_position.pose.orientation, tf_quat);

    double roll, pitch, yaw;
    tf::Matrix3x3(tf_quat).getRPY(roll, pitch, yaw);

    // Convertir l'angle de yaw de radians en degrés
    double yaw_degrees = yaw * 180.0 / M_PI;
    

    ROS_INFO("Current position \n X: %f \t Y: = %f \t Z: %f", feedback->base_position.pose.position.x, 
                                                            feedback->base_position.pose.position.y, 
                                                            yaw_degrees);
}

