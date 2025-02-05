#include "robot_motion/motion_tools.hpp"

bool sub_movebase_bool, sub_moveride_bool, motionServerService_bool;
geometry_msgs::Twist movebase_twist, moveride_twist;

int main(int argc, char** argv)
{
    ros::init(argc, argv, "control_motion");
    ros::NodeHandle n;
    ros::Rate loopRate(0.01);
    
    // Initialiser le subscriber sur movebase(déplacement autonome)
    ros::Subscriber sub_movebase = n.subscribe("movebase_cmd_vel", 10, movebaseSubscriberCallback);
    // Initialiser le subscriber sur moveride(déplacement non autonome)
    ros::Subscriber sub_moveride = n.subscribe("moveride_cmd_vel", 10, moverideSubscriberCallback);
    
    ros::Publisher pub = n.advertise<geometry_msgs::Twist>("cmd_vel", 10);

    /* statusMotion permet de valider l'envoi de position cible, 
        motionMode permet de changer le mode de déplacement soit autonome soit non autonome
    */ 
    /* si statusMotion est true les données sont envoyées sinon les données ne sont pas envoyée
        si motionMode est true les données sont envoyées à movebase (déplacement autonome) sinon les données ne sont pas envoyée moveride(déplacement non autonome)
    */ 
    bool statusMotion, motionMode;

    while (ros::ok())
    {
        
        try
        {
            // Récupérer un paramètre booléen de mode de déplacement true si movebase actif, false si movebase désactif
            n.getParam("/statusMotion", statusMotion);
            n.getParam("/motionMode", motionMode);

            /*
            changement du mode de déplacement du robot(autonome ou non-autonome)
            */
            if((motionMode)&&(!sub_movebase_bool))
            {
                sub_movebase_bool = true;
                // sub_moveride_bool = !sub_movebase_bool;
            }
            else if((!motionMode)&&(!sub_moveride_bool))
            {
                sub_moveride_bool = true;
                // sub_movebase_bool = !sub_moveride_bool;
            }

            // publication des données de contrôle de vitesse
            if (sub_movebase_bool) 
            {
                pub.publish(movebase_twist);
                sub_movebase_bool = false;
            }
            else if(sub_moveride_bool)
            {
                pub.publish(moveride_twist);
                sub_moveride_bool = false;
            }



        }
        catch (const std::runtime_error& e)
        {
            std::cerr << "Runtime error: " << e.what() << std::endl;
            
            ROS_INFO("motion controller Runtime error: %s", e.what());
            
        }
        catch(const std::exception& e)
        {
            std::cerr << "Exception: " << e.what() << std::endl;
            
            ROS_INFO("motion controller Exception error: %s", e.what());
            
        }
        loopRate.sleep();
    }
}

