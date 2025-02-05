#include "robot_motion/motion_tools.hpp"






void motionClient(tf::Vector3 motionRequest, tf::Vector3 motionResponse, std::vector<std_msgs::Bool>& stuckResponse, ros::NodeHandle& n)
{
    ;
    ros::ServiceClient client = n.serviceClient<MotionService::MotionService>("driving");
    MotionService::MotionService srv;
    srv.request.axisXdistance = motionRequest.x();
    srv.request.axisYdistance = motionRequest.y();
    srv.request.axisZrotation = motionRequest.z();

    if (client.call(srv))
    {
        
        ROS_INFO("Response: \n axisXdistance=%ld,\n axisYdistance=%ld,\n axisZrotation=%ld,\n stuckForward=%s,\n stuckBackward=%s,\n stuckRight=%s,\n stuckLeft=%s", (long int)srv.response.axisXdistanceDone, (long int)srv.response.axisYdistanceDone, (long int)srv.response.axisZrotationDone, srv.response.stuckForward ? "true" : "false", srv.response.stuckBackward ? "true" : "false", srv.response.stuckRight ? "true" : "false", srv.response.stuckLeft ? "true" : "false");
        
    }
    else
    {
        
        ROS_ERROR("Failed to call service check_distance");
        
    }
    motionResponse = tf::Vector3(srv.response.axisXdistanceDone, srv.response.axisYdistanceDone, srv.response.axisZrotationDone);
    motionResponse.setX( srv.response.axisXdistanceDone);
    motionResponse.setY( srv.response.axisYdistanceDone);
    motionResponse.setZ( srv.response.axisZrotationDone);
    n.setParam("/axisXdistanceDone", motionResponse.x());
    n.setParam("/axisYdistanceDone", motionResponse.y());
    n.setParam("/axisZdistanceDone", motionResponse.z());
    for (size_t i = 0; i < stuckResponse.size(); i++)
    {
        if(i==0)
            stuckResponse[i].data = srv.response.stuckForward;
        if(i==1)
            stuckResponse[i].data = srv.response.stuckBackward;
        if(i==2)
            stuckResponse[i].data = srv.response.stuckRight;
        if(i==3)
            stuckResponse[i].data = srv.response.stuckLeft;

    }
    // nh.setParam("/stuckForward", stuckResponse[0].data);
    // nh.setParam("/stuckBackward", stuckResponse[1].data);
    // nh.setParam("/stuckRight", stuckResponse[2].data);
    // nh.setParam("/stuckLeft", stuckResponse[3].data);
    
}


void motionServer(ros::NodeHandle& n)
{
    // ros::init();
    ;
    ros::ServiceServer service = n.advertiseService("driving", motionServerServiceCallback);
    
    // // Initialiser le subscriber
    // ros::Subscriber sub = n.subscribe("cmd_vel", 10, motionServerSubscriberCallback);
    
    
    ROS_INFO("Ready to move.");
    
    ros::spin();
}


bool motionServerServiceCallback(MotionService::MotionService::Request &req,
                   MotionService::MotionService::Response &res)
{
    std::vector<geometry_msgs::Pose2D> pose_list;
    
    
    if(motionMode == false)
    {
        motionServerService_bool = true;

        last_req.axisXdistance = req.axisXdistance; 
        last_req.axisYdistance = req.axisYdistance; 
        last_req.axisZrotation = req.axisZrotation;

        pose_list.push_back(createPose2D(req.axisXdistance, req.axisYdistance, req.axisZrotation));
        std::string poseJSON = pose2DListToJson( pose_list);
        
        // envoi de donnée.
        nlohmann::json jsonObject;
        jsonObject["D"] = poseJSON;
        sendUART( jsonObject.dump(), "/dev/ttyAMA0", 9600);
    }
    
    // ROS_INFO("Request: distance_X=%ld, distance_Y=%ld, orientation_Z=%ld", 
    //                     (long int)res.axisXdistance, (long int)res.axisYdistance, (long int)res.axisZrotation);
    // ROS_INFO("Sending back response: distance_X =%ld, \t distance_Y =%ld, \t orientation_Z =%ld,\n
    //         stuckForward=%s, \t stuckBackward=%s, \t stuckRight=%s, \t stuckLeft=%s", 
    //         (long int)res.axisXdistanceDone, (long int)res.axisYdistanceDone, (long int)res.axisZrotationDone, 
    //         res.stuckForward ? "true" : "false", res.stuckBackward ? "true" : "false" , res.stuckRight ? "true" : "false" , res.stuckLeft ? "true" : "false");
    
    
    return true;
}


void motionServerSubscriberCallback(const geometry_msgs::Twist::ConstPtr& msg)
{
    std::vector<geometry_msgs::Pose2D> pose_list;

    geometry_msgs::Twist cmdVelocity;

    if((msg->linear.x > SPEED_FILTER_LIMIT_VALUE)&&(motionMode == true))
    {
        cmdVelocity.linear.x = msg->linear.x;
    }
    if((msg->linear.y > SPEED_FILTER_LIMIT_VALUE)&&(motionMode == true))
    {
        cmdVelocity.linear.y = msg->linear.y;
    }
    if((msg->angular.z > SPEED_FILTER_LIMIT_VALUE)&&(motionMode == true))
    {
        cmdVelocity.angular.z = msg->angular.z;
    }
    if((msg->linear.x > SPEED_FILTER_LIMIT_VALUE)&&(msg->linear.y > SPEED_FILTER_LIMIT_VALUE)&&(msg->angular.z > SPEED_FILTER_LIMIT_VALUE)&&(motionMode == true))
    {
        pose_list.push_back(createPose2D(cmdVelocity.linear.x, cmdVelocity.linear.y, cmdVelocity.angular.z));
        std::string poseJSON = pose2DListToJson( pose_list);
        // envoi de donnée.
        nlohmann::json jsonObject;
        jsonObject["V"] = poseJSON;
        sendUART( jsonObject.dump(), "/dev/ttyAMA0", 9600);    
    }
    
}

geometry_msgs::Twist motionCommand(double cmd_x, double cmd_y, double cmd_z, double time)
{
    geometry_msgs::Twist cmd_vel_msg;
    cmd_vel_msg.linear.x = cmd_x / time; // Calcul de la vitesse linéaire en x
    cmd_vel_msg.linear.y = cmd_y / time; // Calcul de la vitesse linéaire en y
    cmd_vel_msg.angular.z = cmd_z / time; // Calcul de la rotation angulaire sur l'axe z
    return cmd_vel_msg;
}

void movebaseSubscriberCallback(const geometry_msgs::Twist::ConstPtr& msg)
{
    
    geometry_msgs::Twist moveride_twist;
    if((msg->linear.x > SPEED_FILTER_LIMIT_VALUE)&&(motionMode == true))
    {
        moveride_twist.linear.x = msg->linear.x;
    }else {
        moveride_twist.linear.x = 0;
    }
    if((msg->linear.y > SPEED_FILTER_LIMIT_VALUE)&&(motionMode == true))
    {
        moveride_twist.linear.y = msg->linear.y;
    }else {
        moveride_twist.linear.y = 0;
    }
    if((msg->angular.z > SPEED_FILTER_LIMIT_VALUE)&&(motionMode == true))
    {
        moveride_twist.angular.z = msg->angular.z;
    }else {
        moveride_twist.angular.z = 0;
    }
    if((msg->linear.x > SPEED_FILTER_LIMIT_VALUE)&&(msg->linear.y > SPEED_FILTER_LIMIT_VALUE)&&(msg->angular.z > SPEED_FILTER_LIMIT_VALUE)&&(motionMode == true))
    {
        // if(!sub_movebase_bool)
        // {
        //     sub_movebase_bool = true; 
        //     sub_moveride_bool = !sub_movebase_bool;
        // }
    }
    
}


void moverideSubscriberCallback(const geometry_msgs::Twist::ConstPtr& msg)
{
    
    geometry_msgs::Twist movebase_twist;
    if((msg->linear.x > SPEED_FILTER_LIMIT_VALUE)&&(motionMode == true))
    {
        movebase_twist.linear.x = msg->linear.x;
    }else {
        movebase_twist.linear.x = 0;
    }
    if((msg->linear.y > SPEED_FILTER_LIMIT_VALUE)&&(motionMode == true))
    {
        movebase_twist.linear.y = msg->linear.y;
    }else {
        movebase_twist.linear.y = 0;
    }
    if((msg->angular.z > SPEED_FILTER_LIMIT_VALUE)&&(motionMode == true))
    {
        movebase_twist.angular.z = msg->angular.z;
    }else {
        movebase_twist.angular.z = 0;
    }
    if((msg->linear.x > SPEED_FILTER_LIMIT_VALUE)&&(msg->linear.y > SPEED_FILTER_LIMIT_VALUE)&&(msg->angular.z > SPEED_FILTER_LIMIT_VALUE)&&(motionMode == true))
    {
        // if(!sub_moveride_bool)
        // {
        //     sub_moveride_bool = true; 
        //     sub_movebase_bool = !sub_moveride_bool;
        // }
    }
    
}

 