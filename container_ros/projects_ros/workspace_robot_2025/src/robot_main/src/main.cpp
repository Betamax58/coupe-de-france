#include "robot_main/main.hpp"


int main(int argc, char** argv)
{
    ros::init(argc, argv, "control_motion");
    ros::NodeHandle n;
    ros::Rate loopRate(0.01);

    n.setParam("/axisXdistanceDone", 0);
    n.setParam("/axisYdistanceDone", 0);
    n.setParam("/axisZdistanceDone", 0);

    /* true si le module main autorise l'envoi des coordonnées cibles aux modules de déplacement autonome ou non-autonome, 
    false si le module main refuse l'envoi des coordonnées cibles aux modules de déplacement autonome ou non-autonome
    */
    n.setParam("/statusMotion", false);
    
    /* true si le robot est en navigation autonome, 
    false si le robot est en navigation non autonome
    */
    n.setParam("/motionMode", true);
    
    /* true si le module GUI autorise la lecture des coordonnées de la nouvelle cible, 
    false si le module GUI n'autorise pas la lecture des coordonnées de la nouvelle cible
    */
    n.setParam("/statusGUI", false);
    n.setParam("/stuckForward", false);
    n.setParam("/stuckBackward", false);
    n.setParam("/stuckRight", false);
    n.setParam("/stuckLeft", false);

    n.setParam("/controlMotionEnd", false);
    n.setParam("/statusMoveBaseEnd", false);
    
    n.setParam("/targetPosition_x", 0);// coordonnée X
    n.setParam("/targetPosition_y", 0);// coordonnée Y

    n.setParam("/movebase_online", false);

    bool statusGUI, statusCAM, motionMode, statusMotion, controlMotionEnd, statusMoveBaseEnd;
    n.getParam("/statusGUI", statusGUI);
    n.getParam("/statusCAM", statusCAM);
    n.getParam("/motionMode", motionMode);
    n.getParam("/statusMotion", statusMotion);
    n.getParam("/controlMotionEnd", controlMotionEnd);
    n.getParam("/statusMoveBaseEnd", statusMoveBaseEnd);
    if(statusGUI)
    {
        n.setParam("/statusMotion", true);
        ;
    }

    while (ros::ok()) 
    {
        n.getParam("/statusGUI", statusGUI);
        n.getParam("/statusCAM", statusCAM);
        n.getParam("/motionMode", motionMode);
        n.getParam("/statusMotion", statusMotion);
        n.getParam("/controlMotionEnd", controlMotionEnd);
        n.getParam("/statusMoveBaseEnd", statusMoveBaseEnd);
        if(statusGUI)
        {

        }

        loopRate.sleep();
    }

}
