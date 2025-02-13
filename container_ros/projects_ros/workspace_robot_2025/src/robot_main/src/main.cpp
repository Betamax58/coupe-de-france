#include "robot_main/main.hpp"

/*
Toujours mettre taskFinished = false avant d'utiliser timer1
timer pour permettre au programme de détection de la caméra de repère les tags aruco  des cannettes.
*/
ros::Timer timer1;

/*
Toujours mettre warningAlarm = false avant d'utiliser timer1
timer pour demander au robot de rentrer dans une zone d'arrivé avant la fin du match.
*/
ros::Timer timer2;

/*
Toujours mettre stopMotion = false avant d'utiliser timer1
timer pour arrêter le robot au moment de la fin du temps de jeu.
*/
ros::Timer timer3;

bool taskFinished = false;// booléen du timer1, true si la tâche est terminé, false si la tâche n'est pas terminé.
bool warningAlarm = false;// booléen du timer2, true si c'est le moment de rentrer dans une zone d'arrivée, false sinon .
bool stopMotion = false;// booléen du timer3, true si le robot doit s'arrête, false sinon.


int main(int argc, char** argv)
{
    ros::init(argc, argv, "control_motion");
    ros::NodeHandle n;
    ros::Rate loopRate(0.01);

    init_timer(n);// initialisation des timers

    n.setParam("/statusCAM", false);
    
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
    
    n.setParam("/targetPosition_x", 0);// coordonnée X cible
    n.setParam("/targetPosition_y", 0);// coordonnée Y cible
    n.setParam("/targetOrientation", 0);// orientation cible

    n.setParam("/currentPosition_x", 0);// coordonnée X courante
    n.setParam("/currentPosition_y", 0);// coordonnée Y courante
    n.setParam("/currentOrientation", 0);// orientation courante

    n.setParam("/movebase_online", false);

    /*
    statusGUI - true si main valide l'envoi des coordonnées cibles aux programmes de navigation autonome et non-autonom, false sinon
    statusCAM - true si main valide l'asservissement en position avec la caméra, false sinon.
    motionMode - true si main selectionne le déplacement autonome, false sinon.
    statusMotion - true si main valide la lecture des coordonnées cibles par les programmes de navigation autonome et non-autonome.
    controlMotionEnd - true si moveride a terminé la navigation non-autonome, false sinon.
    statusMoveBaseEnd - true si movebase a terminé la navigation autonome, false sinon.
    */
    bool statusGUI, statusCAM, motionMode, statusMotion, controlMotionEnd, statusMoveBaseEnd;
    

    while (ros::ok()) 
    {
        n.getParam("/statusGUI", statusGUI);
        // n.getParam("/statusCAM", statusCAM);
        n.getParam("/motionMode", motionMode);
        n.getParam("/statusMotion", statusMotion);
        n.getParam("/controlMotionEnd", controlMotionEnd);
        n.getParam("/statusMoveBaseEnd", statusMoveBaseEnd);
        if((statusGUI)&&(!warningAlarm))
        {
            n.setParam("/statusMotion", true);// autorisation de la  lecture des coordonnées cibles pour le déplacement autonome et non-autonome
            
            // détection du mode de déplacement et du temps d'action du robot, dans la condition suivante le robot est entrain rouler de façon autonome
            if ((motionMode)&&(!warningAlarm)) 
            {
                // dans la boucle suivante nous vérifions que le robot est terminé sont déplacement autonome et que le temps d'action n'est pas terminé
                while ((!warningAlarm)&&(!statusMoveBaseEnd)) 
                {
                    ROS_INFO("robot is moving on movebase software");
                    
                    // verification de la fin du logiciel movebase
                    n.getParam("/statusMoveBaseEnd", statusMoveBaseEnd);
                }
                
                taskFinished = false;// mise en condition normale de la variable pour détecter si l'attente d'une tâche est terminé
                
                timer1.start();// démarrage du timer
                /*
                la boucle suivante permet d'attendre que le programme de détection des tags aruco de canette ait détecté les canettes, 
                si les canettes sont détecté il poursuit avec de l'asservissement en position,
                sinon il poursuit une nouvelle coordonnées.
                */
                while((!warningAlarm)&&(!taskFinished))
                {
                    // vérification de l'autorisation de l'asservissement en position entre les canettes et la pince
                    n.getParam("/statusCAM", statusCAM);
                    if(statusCAM)
                    {
                        n.setParam("/motionMode", false);
                        n.setParam("/statusCAM", false);// remise en condition normale de la validation de l'asservissement en position
                        timer1.stop();
                        taskFinished = true;
                    }
                    
                }
            }

            
            if ((!motionMode)&&(!warningAlarm)) 
            {
                // dans la boucle suivante nous vérifions que le robot est terminé sont déplacement non-autonome et que le temps d'action n'est pas terminé
                while ((!warningAlarm)&&(!controlMotionEnd)) 
                {
                    // fonction d'asservissement en position
                    n.setParam("/controlMotionEnd", controlMotionEnd);// vérification de la fin d'asservissement
                    n.setParam("/motionMode", false);
                }
            }
            
            ;
        }

        if(warningAlarm)
        {
            ;
        }
        if(stopMotion)
        {
            ;
            break;
        }

        loopRate.sleep();
    }

    ROS_INFO("time is over \t BYE BYE !!!!! \n robot turning off");

    return 0;
}

/*
fonction pour détecter le lancement manuel
*/
void detect_launch()
{

}

/*
fonction pour initialiser les timers
*/
void init_timer(ros::NodeHandle& nh)
{
    // Création de deux timers avec des périodes différentes
    timer1 = nh.createTimer(ros::Duration(2.0), timerCallback_Waiting_Camera_Capture, false, false); // 1 seconde
    timer2 = nh.createTimer(ros::Duration(80), timerCallback_Warning_Time_Alarm, false, false); // 80 secondes
    timer3 = nh.createTimer(ros::Duration(90), timerCallback_Stop_Time_Alarm, false, false); // 90 secondes
}

/*
callback du timer1
Toujours mettre taskFinished = false avant d'utiliser le timer associé
*/
void timerCallback_Waiting_Camera_Capture(const ros::TimerEvent&)
{
    ROS_INFO("Timer 1 triggered");
    taskFinished = true;
}

/*
callback du timer2
Toujours mettre warningAlarm = false avant d'utiliser le timer associé
*/
void timerCallback_Warning_Time_Alarm(const ros::TimerEvent&)
{
    ROS_INFO("Timer 2 triggered");
    warningAlarm = true;
}

/*
callback du timer3
Toujours mettre stopMotion = false avant d'utiliser le timer associé
*/
void timerCallback_Stop_Time_Alarm(const ros::TimerEvent&)
{
    ROS_INFO("Timer 3 triggered");
    stopMotion = true;
}
