#ifndef PROCESS_H
#define PROCESS_H

#include <nav_msgs/Odometry.h>

#include <tf/transform_broadcaster.h>

#include <std_msgs/String.h>

#include <geometry_msgs/Pose.h>
#include <geometry_msgs/Twist.h>

#include <ros/time.h>
#include <ros/ros.h>

void odometryMessage(std_msgs::String childFrameName, std_msgs::String parentFrameName, geometry_msgs::Pose pose, geometry_msgs::Twist twist, nav_msgs::Odometry &odom_msg);


/**
 * @class TimerProcess
 * @brief Cette classe gère le processus de minuterie de callback.
 * 
 * La classe TimerProcess est utilisée pour initialiser et gérer les opérations
 * liées à la minuterie  de callback.
 */
class TimerProcess
{
public:
    /**
     * @brief Constructeur de la classe TimerProcess.
     * @param nh pointeur du noeud à manipuler de type nodeHandle
     *
     */
    TimerProcess(ros::NodeHandle *nh);
    

protected:
    ros::NodeHandle* nodeHandlePtr; ///< pointeur du noeud à manipuler
    
    ros::Timer timer; ///< timer stocke la valeur de temps
    
};

class TimerOdometry : public TimerProcess
{
    private:
        nav_msgs::Odometry odometryMsg; ///< message concernant l'odométrie manipuler par timerOdometry
        
        /**
         * @brief Callback pour l'execution de tâche associé à l'odométrie.
         * @param event pointeur d'evenement ros
         *
         */
        void timerCallbackOdometry(const ros::TimerEvent &event);
        

    public:
        /**
         * @brief Constructeur de la classe de base TimerProcess.
         * @param nh pointeur du noeud à manipuler
         *
         */
        TimerOdometry(ros::NodeHandle *nh);
        
        
        void Run();
        

};

class TimerTF: public TimerProcess
{
    private:
        nav_msgs::Odometry odometryMsg; ///< message concernant l'odométrie manipuler par timerOdometry
        
        /**
         * @brief Callback pour l'execution de tâche associé à la manipulation de repère.
         * @param event pointeur d'evenement ros
         *
         */
        void timerCallbackTF(const ros::TimerEvent &event);
        

    public:
        /**
         * @brief Constructeur de la classe de base TimerProcess.
         * @param nh pointeur du noeud à manipuler
         *
         */
        TimerTF(ros::NodeHandle *nh);
        
        
        void Run();
        

};

class TimerCamera : public TimerProcess
{
    private:
        nav_msgs::Odometry odometryMsg; ///< message concernant l'odométrie manipuler par timerOdometry
        
        /**
         * @brief Callback pour l'execution de tâche associé au traitement des données obtenu à partir de la caméra.
         * @param event pointeur d'evenement ros
         *
         */
        void timerCallbackCamera(const ros::TimerEvent &event);
        

    public:
        /**
         * @brief Constructeur de la classe de base TimerProcess.
         * @param nh pointeur du noeud à manipuler
         *
         */
        TimerCamera(ros::NodeHandle *nh);
        
        
        void Run();
        

};

class TimerTOF : public TimerProcess
{
    private:
        nav_msgs::Odometry odometryMsg; ///< message concernant l'odométrie manipuler par timerOdometry
        
        /**
         * @brief Callback pour l'execution de tâche associé au traitement des données des capteurs TOF.
         * @param event pointeur d'evenement ros
         *
         */
        void timerCallbackTOF(const ros::TimerEvent &event);
        

    public:
        /**
         * @brief Constructeur de la classe de base TimerProcess.
         * @param nh pointeur du noeud à manipuler
         *
         */
        TimerTOF(ros::NodeHandle *nh);
        
        
        void Run();
        

};

class TimerLidar : public TimerProcess
{
    private:
        nav_msgs::Odometry odometryMsg; ///< message concernant l'odométrie manipuler par timerOdometry
        
        /**
         * @brief Callback pour l'execution de tâche associé au traitement des données du lidar.
         * @param event pointeur d'evenement ros
         *
         */
        void timerCallbackLidar(const ros::TimerEvent &event);
        

    public:
        /**
         * @brief Constructeur de la classe de base TimerProcess.
         * @param nh pointeur du noeud à manipuler
         *
         */
        TimerLidar(ros::NodeHandle *nh);
        
        
        void Run();
        

};

class TimerMotion : public TimerProcess
{
    private:
        nav_msgs::Odometry odometryMsg; ///< message concernant l'odométrie manipuler par timerOdometry
        
        /**
         * @brief Callback pour l'execution de tâche associé au mouvement du robot.
         * @param event pointeur d'evenement ros
         *
         */
        void timerCallbackMotion(const ros::TimerEvent &event);
        

    public:
        /**
         * @brief Constructeur de la classe de base TimerProcess.
         * @param nh pointeur du noeud à manipuler
         *
         */
        TimerMotion(ros::NodeHandle *nh);
        
        
        void Run();
        

};


#endif // NOM_FICHIER_H