// #include "../include/node.hpp"
// #include "../include/process.hpp"
// #include "../include/operator.hpp"
#include "node.hpp"
#include "process.hpp"
#include "operator.hpp"

void publisherOdometry(int argc, char** argv)
{
    ros::init(argc, argv, "publisherOdometry");
    ros::NodeHandle n;
    ros::Publisher pub = n.advertise<nav_msgs::Odometry>("/odom", 100);
    ros::Rate loop_rate(10);

  /**
   * A count of how many messages we have sent. This is used to create
   * a unique string for each message.
   */
    int count = 0;

  // Création du timer
  TimerProcess timerProcess(&n); // Appelé toutes les 0.1 seconde

  while (ros::ok())
  {
    /**
     * This is a message object. You stuff it with data, and then publish it.
     */
    std_msgs::String msg;

    std::stringstream ss;
    ss << "p_n_Odometry_ID_" << count;
    msg.data = ss.str();

    ROS_INFO("%s", msg.data.c_str());

    /**
     * The publish() function is how you send messages. The parameter
     * is the message object. The type of this object must agree with the type
     * given as a template parameter to the advertise<>() call, as was done
     * in the constructor above.
     */
    pub.publish(msg);

    ros::spinOnce();

    loop_rate.sleep();
    ++count;
  }
}

void publisherTF(int argc, char** argv)
{
    ros::init(argc, argv, "publisherTF");
    ros::NodeHandle n;
    ros::Publisher pub = n.advertise<std_msgs::String>("/chatterTF", 1000);
    ros::Rate loop_rate(10);

    nav_msgs::Odometry frameOdometry;

    

    while (ros::ok())
  {
    /**
     * This is a message object. You stuff it with data, and then publish it.
     */
    std_msgs::String msg;
    std::stringstream ss;
    ss << "hello world ";
    msg.data = ss.str();
    ROS_INFO("%s", msg.data.c_str());
    
    


    /**
     * The publish() function is how you send messages. The parameter
     * is the message object. The type of this object must agree with the type
     * given as a template parameter to the advertise<>() call, as was done
     * in the constructor above.
     */
    pub.publish(msg);

    // ros::spinOnce();

    loop_rate.sleep();
    
  }
}

void publisherCameraData(int argc, char** argv)
{
    ros::init(argc, argv, "publisherOdometry");
    ros::NodeHandle n;
    ros::Publisher chatter_pub = n.advertise<std_msgs::String>("/chatterCam", 1000);
    ros::Rate loop_rate(10);

    while (ros::ok())
  {
    /**
     * This is a message object. You stuff it with data, and then publish it.
     */
    std_msgs::String msg;

    std::stringstream ss;
    ss << "hello world ";
    msg.data = ss.str();

    ROS_INFO("%s", msg.data.c_str());

    /**
     * The publish() function is how you send messages. The parameter
     * is the message object. The type of this object must agree with the type
     * given as a template parameter to the advertise<>() call, as was done
     * in the constructor above.
     */
    chatter_pub.publish(msg);

    // ros::spinOnce();

    loop_rate.sleep();
    
  }
}

void publisherTOFData(int argc, char** argv)
{
    ros::init(argc, argv, "publisherOdometry");
    ros::NodeHandle n;
    ros::Publisher chatter_pub = n.advertise<std_msgs::String>("chatterTOF", 1000);
    ros::Rate loop_rate(10);

    while (ros::ok())
  {
    /**
     * This is a message object. You stuff it with data, and then publish it.
     */
    std_msgs::String msg;

    std::stringstream ss;
    ss << "hello world ";
    msg.data = ss.str();

    ROS_INFO("%s", msg.data.c_str());

    /**
     * The publish() function is how you send messages. The parameter
     * is the message object. The type of this object must agree with the type
     * given as a template parameter to the advertise<>() call, as was done
     * in the constructor above.
     */
    chatter_pub.publish(msg);

    // ros::spinOnce();

    loop_rate.sleep();
    
  }
}

void publisherLidarData(int argc, char** argv)
{
    ros::init(argc, argv, "publisherOdometry");
    ros::NodeHandle n;
    ros::Publisher chatter_pub = n.advertise<std_msgs::String>("chatterLidar", 1000);
    ros::Rate loop_rate(10);

    while (ros::ok())
  {
    /**
     * This is a message object. You stuff it with data, and then publish it.
     */
    std_msgs::String msg;

    std::stringstream ss;
    ss << "hello world ";
    msg.data = ss.str();

    ROS_INFO("%s", msg.data.c_str());

    /**
     * The publish() function is how you send messages. The parameter
     * is the message object. The type of this object must agree with the type
     * given as a template parameter to the advertise<>() call, as was done
     * in the constructor above.
     */
    chatter_pub.publish(msg);

    // ros::spinOnce();

    loop_rate.sleep();
    
  }
}

void publisherVelocity(int argc, char** argv)
{
    ros::init(argc, argv, "publisherOdometry");
    ros::NodeHandle n;
    ros::Publisher chatter_pub = n.advertise<std_msgs::String>("/chatterVel", 1000);
    ros::Rate loop_rate(10);

    while (ros::ok())
  {
    /**
     * This is a message object. You stuff it with data, and then publish it.
     */
    std_msgs::String msg;

    std::stringstream ss;
    ss << "hello world ";
    msg.data = ss.str();

    ROS_INFO("%s", msg.data.c_str());

    /**
     * The publish() function is how you send messages. The parameter
     * is the message object. The type of this object must agree with the type
     * given as a template parameter to the advertise<>() call, as was done
     * in the constructor above.
     */
    chatter_pub.publish(msg);

    // ros::spinOnce();

    loop_rate.sleep();
    
  }
}

void publisherMotion(int argc, char** argv)
{
    ros::init(argc, argv, "publisherOdometry");
    ros::NodeHandle n;
    ros::Publisher chatter_pub = n.advertise<std_msgs::String>("/chatterMotion", 1000);
    ros::Rate loop_rate(10);

    while (ros::ok())
  {
    /**
     * This is a message object. You stuff it with data, and then publish it.
     */
    std_msgs::String msg;

    std::stringstream ss;
    ss << "hello world ";
    msg.data = ss.str();

    ROS_INFO("%s", msg.data.c_str());

    /**
     * The publish() function is how you send messages. The parameter
     * is the message object. The type of this object must agree with the type
     * given as a template parameter to the advertise<>() call, as was done
     * in the constructor above.
     */
    chatter_pub.publish(msg);

    // ros::spinOnce();

    loop_rate.sleep();
    
  }
}

void publisherMonitoring(int argc, char** argv)
{
    ros::init(argc, argv, "publisherOdometry");
    ros::NodeHandle n;
    ros::Publisher chatter_pub = n.advertise<std_msgs::String>("chatter", 1000);
    ros::Rate loop_rate(10);

    while (ros::ok())
  {
    /**
     * This is a message object. You stuff it with data, and then publish it.
     */
    std_msgs::String msg;

    std::stringstream ss;
    ss << "hello world ";
    msg.data = ss.str();

    ROS_INFO("%s", msg.data.c_str());

    /**
     * The publish() function is how you send messages. The parameter
     * is the message object. The type of this object must agree with the type
     * given as a template parameter to the advertise<>() call, as was done
     * in the constructor above.
     */
    chatter_pub.publish(msg);

    // ros::spinOnce();

    loop_rate.sleep();
    
  }
}

void subscriberOdometry(int argc, char** argv)
{
    ros::init(argc, argv, "subcriberOdometry");
    ros::NodeHandle n;
    ros::Subscriber sub = n.subscribe("/odom", 1000, chatterCallback);
    ros::spin();
}

void subscriberTF(int argc, char** argv)
{
    ros::init(argc, argv, "subcriberOdometry");
    ros::NodeHandle n;
    ros::Subscriber sub = n.subscribe("chatterTF", 1000, chatterCallback);
    ros::spin();
}

void subscriberMotionControl(int argc, char** argv)
{
    ros::init(argc, argv, "subcriberOdometry");
    ros::NodeHandle n;
    ros::Subscriber sub = n.subscribe("chatterMotion", 1000, chatterCallback);
    ros::spin();
}

void subscriberSensor(int argc, char** argv)
{
    ros::init(argc, argv, "subcriberOdometry");
    ros::NodeHandle n;
    ros::Subscriber sub = n.subscribe("chatterSensor", 1000, chatterCallback);
    ros::spin();
}

void chatterCallback(const std_msgs::String::ConstPtr& msg) {
    ROS_INFO("I heard: [%s]", msg->data.c_str());
}

