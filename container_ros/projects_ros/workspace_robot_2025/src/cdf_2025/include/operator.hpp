#ifndef OPERATOR_H
#define OPERATOR_H

#include <nav_msgs/Odometry.h>

#include <tf/transform_broadcaster.h>
#include <tf/transform_listener.h>
#include <tf/transform_datatypes.h>
#include <tf/exceptions.h>

#include <geometry_msgs/Quaternion.h>
#include <geometry_msgs/PointStamped.h>
#include <geometry_msgs/Vector3.h>

#include <std_msgs/String.h>

#include <ros/time.h>

/**
 * @class FrameOperator
 * @brief classe qui gère la manipulation des informations appartenant à un repère.
 * 
 * - les attributs sont les suivants:
 * - "x_position_point" : coordonnée sur l'axe x.
 * - "y_position_point" : coordonnée sur l'axe y.
 * - "z_position_point" : coordonnée sur l'axe z.
 * - "frameName" : nom du repère à manipuler.
 * - "parentFrameName" : nom du repère de référence.
 * - "frameTransform" : vecteur de transformation du repère child par rapport au repère parent.
 */
class FrameOperator
{
    private:
        float x_position_point;
        float y_position_point;
        float z_position_point;
        std_msgs::String frameName;
        std_msgs::String parentFrameName;
        tf::Transform frameTransform;
        tf::TransformListener listener;

    public:
        void setPositionPoint(tf::vector3 vector);
        void setFrameName(std_msgs::String name);
        void setParentFrameName(std_msgs::String name);
        void setPositionPoint(tf::vector3 vector);
        tf::vector3 getPositionPointFromParentFrame(void);
        std_msgs::String getParentFrameName(void);
        std_msgs::String getFrameName(void);
        void setFrameTransform(tf::Transform transform);
        void getFrameTransform(void);

};

/**
 * @class MotionOperator
 * @brief classe qui gère la manipulation des informations appartenant à un repère.
 * 
 * - les attributs sont les suivants:
 * - "rightForwardWheelVelocity" : vitesse de la roue droite avant.
 * - "leftForwardWheelVelocity" : vitesse de la roue gauche avant.
 * - "rightBackwardWheelVelocity" : vitesse de la roue droite arriere.
 * - "leftBackwardWheelVelocity" : vitesse de la roue gauche arriere.
 * - "timestamp" : moment de la mesure des valeurs des vitesses de roues.
 * - "motionMode" : mode de déplacement axial ou radial.
 */
class MotionOperator
{
    private:
        float rightForwardWheelVelocity[2];
        float leftForwardWheelVelocity[2];
        float rightBackwardWheelVelocity[2];
        float leftBackwardWheelVelocity[2];
        float timestamp[2];
        std_msgs::Bool motionMode; /** @brief si true deplacement axial, si false déplacement radial */ 
        

    public:
        nav_msgs::Odometry getWheelsOdometry(void);
        void setMotionMode(std_msgs::Bool motionMode);
        void updateWheelsOdometry(void);
        

};

/**
 * @class TransformOperator
 * @brief classe pour le traitement de changement de position entre à un repère et un autre repère.
 * 
 * - les attributs sont les suivants:
 * - "childFrame" : FrameOperator pour le repère relatif.
 * - "parentFrame" : FrameOperator pour le repère de reférence.
 * - "odometryTransform" : odométrie correspond à différence de position actuel et la position prècedemment calculé.
 * - "broadcaster" : outil pour partager une objet de type tf::Transform étant la différence de position entre un child repère et parent repère avec tout les noeuds en fonctionnement.
 * - "listener" : outil utiliser pour mesurer un objet de type tf::Transform étant la différence de position entre un child repère et parent repère.
 */
class TransformOperator
{
    private:
        FrameOperator childFrame;
        FrameOperator parentFrame;
        nav_msgs::Odometry odometryTransform;
        tf::TransformBroadcaster broadcaster;
        tf::TransformListener listener;
        

    public:
        tf::Transform getFrameTransformation(void);
        void setChildFrame(FrameOperator childFrame);
        void setParentFrame(FrameOperator parentFrame);
        void setOdometryTransform(nav_msgs::Odometry odometryTransform);
        void broadcastTransform(void);
        void updateChildFrame(void);

};

#endif