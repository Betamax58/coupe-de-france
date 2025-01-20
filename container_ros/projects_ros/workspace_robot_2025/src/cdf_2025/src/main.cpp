#include <ros/ros.h>

#include <move_base_msgs/MoveBaseAction.h>

#include <actionlib/client/simple_action_client.h>

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv) {
    ros::init(argc, argv, "send_goal");

    // Créer un client pour l'action move_base
    MoveBaseClient ac("move_base", true);

    // Attendre que le serveur d'actions soit disponible
    ROS_INFO("Waiting for the move_base action server to come up");
    ac.waitForServer();

    // Définir l'objectif de navigation
    move_base_msgs::MoveBaseGoal goal;
    goal.target_pose.header.frame_id = "map";
    goal.target_pose.header.stamp = ros::Time::now();

    // Définir la position et l'orientation de l'objectif
    goal.target_pose.pose.position.x = 1.0;
    goal.target_pose.pose.position.y = 1.0;
    goal.target_pose.pose.orientation.w = 1.0;

    // Envoyer l'objectif au serveur d'actions
    ROS_INFO("Sending goal");
    ac.sendGoal(goal);

    // Attendre que le robot atteigne l'objectif
    ac.waitForResult();

    if (ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
        ROS_INFO("The robot reached the goal!");
    else
        ROS_INFO("The robot failed to reach the goal.");

    return 0;
}

