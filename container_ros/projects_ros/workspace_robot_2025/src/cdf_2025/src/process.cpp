#include "../include/process.hpp"


void odometryMessage(std_msgs::String childFrameName, std_msgs::String parentFrameName, geometry_msgs::Pose poseMsg, geometry_msgs::Twist twistMsg, nav_msgs::Odometry *odom_msg)
{
    if (odom_msg == nullptr) {
        ROS_ERROR("odom_msg pointer is null!");
        return;
    }
    // Création du message Odometry
        // nav_msgs::Odometry odom_msg;

        // Remplissage de l'en-tête
        odom_msg->header.stamp = ros::Time::now();
        odom_msg->header.frame_id = parentFrameName;  // Cadre de référence
        odom_msg->child_frame_id = childFrameName;  // Cadre enfant

        // Remplissage de la pose (position et orientation)
        odom_msg->pose.pose.position.x = poseMsg.position.x;
        odom_msg->pose.pose.position.y = poseMsg.position.y;
        odom_msg->pose.pose.position.z = poseMsg.position.z;
        odom_msg->pose.pose.orientation.x =poseMsg.orientation.x;
        odom_msg->pose.pose.orientation.y = poseMsg.orientation.y;
        odom_msg->pose.pose.orientation.z = poseMsg.orientation.z;
        odom_msg->pose.pose.orientation.w = poseMsg.orientation.w;

        // Covariance de la pose (facultatif)
        for (int i = 0; i < 36; i++) {
            odom_msg->pose.covariance[i] = 0.0;
        }

        // Remplissage de la vitesse (linéaire et angulaire)
        odom_msg->twist.twist.linear.x = twistMsg.linear.x;
        odom_msg->twist.twist.linear.y = twistMsg.linear.y;
        odom_msg->twist.twist.linear.z = twistMsg.linear.z;
        odom_msg->twist.twist.angular.x = twistMsg.angular.x;
        odom_msg->twist.twist.angular.y = twistMsg.angular.y;
        odom_msg->twist.twist.angular.z = twistMsg.angular.z;

        // Covariance de la vitesse (facultatif)
        for (int i = 0; i < 36; i++) {
            odom_msg->twist.covariance[i] = 0.0;
        }
}



    
// Constructeur de la classe TimerProcess.
TimerProcess::TimerProcess(ros::NodeHandle *nh)
{
    // Initialisation du node handle
    this->nodeHandlePtr = nh;           
}

// Constructeur de la classe TimerOdometry.
TimerOdometry::TimerOdometry(ros::NodeHandle *nh)
{
    TimerProcess::TimerProcess(nh);
}

// fonction de lancement de callback avec timer de la classe TimerOdometry.        
void TimerOdometry::Run()
{
   timer = nodeHandlePtr->createTimer(ros::Duration(0.1), &TimerOdometry::timerCallbackOdometry, this); // Appelé toutes les 100 millisecondes
}

// callback pour les opérations de la classe TimerOdometry.
void TimerOdometry::timerCallbackOdometry(const ros::TimerEvent &event)
{
     // Fonction appelée périodiquement par le timer
    std_msgs::String msg;
     msg.data = "Message périodique envoyé par le timer";
    ROS_INFO("Timer callback odometry triggered!");
    // ROS_INFO_STREAM("Timer callback executed. Message published: " << msg.data);
}

// Constructeur de la classe TimerTF.
TimerTF::TimerTF(ros::NodeHandle *nh)
{
    TimerProcess::TimerProcess(nh);
}
 
// fonction de lancement de callback avec timer de la classe TimerTF.     
void TimerTF::Run()
{
    timer = nodeHandlePtr->createTimer(ros::Duration(0.1), &TimerTF::timerCallbackTF, this); // Appelé toutes les 100 millisecondes
}

// callback pour les opérations de la classe TimerTF.
void TimerTF::timerCallbackTF(const ros::TimerEvent &event)
{
    // Fonction appelée périodiquement par le timer
    std_msgs::String msg;
    msg.data = "Message périodique envoyé par le timer";

    ROS_INFO("Timer callback odometry triggered!");
    // ROS_INFO_STREAM("Timer callback executed. Message published: " << msg.data);
}

// Constructeur de la classe TimerCamera.
TimerCamera::TimerCamera(ros::NodeHandle *nh)
{
    TimerProcess::TimerProcess(nh)
}

// fonction de lancement de callback avec timer de la classe TimerCamera.  
void TimerCamera::Run()
{
    timer = nodeHandlePtr->createTimer(ros::Duration(0.1), &TimerCamera::timerCallbackCamera, this); // Appelé toutes les 100 millisecondes
}

// callback pour les opérations de la classe TimerCamera.
void TimerCamera::timerCallbackCamera(const ros::TimerEvent &event)
{
    // Fonction appelée périodiquement par le timer
    std_msgs::String msg;
    msg.data = "Message périodique envoyé par le timer";

    ROS_INFO("Timer callback odometry triggered!");
    // ROS_INFO_STREAM("Timer callback executed. Message published: " << msg.data);
}
   
// Constructeur de la classe TimerTOF.
TimerTOF::TimerTOF(ros::NodeHandle *nh)
{
    TimerProcess::TimerProcess(nh)
}
        
// fonction de lancement de callback avec timer de la classe TimerTOF.  
void TimerTOF::Run()
{
    timer = nodeHandlePtr->createTimer(ros::Duration(0.1), &TimerTOF::timerCallbackTOF, this); // Appelé toutes les 100 millisecondes
}
        
// callback pour les opérations de la classe TimerTOF.
void TimerTOF::timerCallbackTOF(const ros::TimerEvent &event)
{
    // Fonction appelée périodiquement par le timer
    std_msgs::String msg;
    msg.data = "Message périodique envoyé par le timer";

    ROS_INFO("Timer callback odometry triggered!");
    // ROS_INFO_STREAM("Timer callback executed. Message published: " << msg.data);
}

// Constructeur de la classe TimerLidar.
TimerLidar::TimerLidar(ros::NodeHandle *nh)
{
    TimerProcess::TimerProcess(nh)
}
        
// fonction de lancement de callback avec timer de la classe TimerLidar.  
void TimerLidar::Run()
{
    timer = nodeHandlePtr->createTimer(ros::Duration(0.1), &TimerLidar::timerCallbackLidar, this); // Appelé toutes les 100 millisecondes
}
        
// callback pour les opérations de la classe TimerLidar.
void TimerLidar::timerCallbackLidar(const ros::TimerEvent &event)
{
    // Fonction appelée périodiquement par le timer
    std_msgs::String msg;
    msg.data = "Message périodique envoyé par le timer";

    ROS_INFO("Timer callback odometry triggered!");
    // ROS_INFO_STREAM("Timer callback executed. Message published: " << msg.data);
}

// Constructeur de la classe TimerMotion.
TimerMotion::TimerMotion(ros::NodeHandle *nh)
{
    TimerProcess::TimerProcess(nh)
}
        
// fonction de lancement de callback avec timer de la classe TimerMotion.  
void TimerMotion::Run()
{
    timer = nodeHandlePtr->createTimer(ros::Duration(0.1), &TimerMotion::timerCallbackMotion, this); // Appelé toutes les 100 millisecondes
}
        
// callback pour les opérations de la classe TimerMotion.
void TimerMotion::timerCallbackMotion(const ros::TimerEvent &event)
{
    // Fonction appelée périodiquement par le timer
    std_msgs::String msg;
    msg.data = "Message périodique envoyé par le timer";

    ROS_INFO("Timer callback odometry triggered!");
    // ROS_INFO_STREAM("Timer callback executed. Message published: " << msg.data);
}


        






