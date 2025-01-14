#include "../include/node.hpp"
#include "../include/process.hpp"
#include "../include/operator.hpp"

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
  TimerProcess timerProcess(&n, "odometry"); // Appelé toutes les 0.1 seconde

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
    ros::Publisher pub = n.advertise<std_msgs::String>("chatter", 1000);
    ros::Rate loop_rate(10);

    Odometrynav_msgs::Odometry frameOdometry

    TransformOperator transformOperator;
    FrameOperator frameOperatorOdom, frameOperatorFootprint, frameOperatorBase_link,
                  frameOperatorCameraFrameA, frameOperatorCameraFrameB, frameOperatorCameraFrameC,
                  frameOperatorTOF_frameA, frameOperatorTOF_frameB, frameOperatorTOF_frameC,
                  frameOperatorTOF_frameD, frameOperatorTOF_frameE, frameOperatorTOF_frameF,
                  frameOperatorTOF_frameG,frameOperatorTOF_frameH; 
    
    
    frameOperatorOdom.setPositionPoint(tf::vector3(0,0,0));
    frameOperatorOdom.setFrameName("odom");
    frameOperatorOdom.setParentFrameName("map");
    frameOperatorFootprint.setPositionPoint(tf::vector3(0,0,0));
    frameOperatorFootprint.setFrameName("footprint");
    frameOperatorFootprint.setParentFrameName("odom");
    frameOperatorBase_link.setPositionPoint(tf::vector3(0,0,0));
    frameOperatorBase_link.setFrameName("base_link");
    frameOperatorBase_link.setParentFrameName("footprint");
    frameOperatorBase_laser.setPositionPoint(tf::vector3(0,0,0));
    frameOperatorBase_laser.setFrameName("base_laser");
    frameOperatorBase_laser.setParentFrameName("base_link");
    frameOperatorCameraFrameA.setPositionPoint(tf::vector3(0,0,0));
    frameOperatorCameraFrameA.setFrameName("cameraFrameA");
    frameOperatorCameraFrameA.setParentFrameName("base_link");
    frameOperatorCameraFrameB.setPositionPoint(tf::vector3(0,0,0));
    frameOperatorCameraFrameB.setFrameName("cameraFrameB");
    frameOperatorCameraFrameB.setParentFrameName("base_link");
    frameOperatorCameraFrameC.setPositionPoint(tf::vector3(0,0,0));
    frameOperatorCameraFrameC.setFrameName("cameraFrameC");
    frameOperatorCameraFrameC.setParentFrameName("base_link");
    frameOperatorTOF_frameA.setPositionPoint(tf::vector3(0,0,0));
    frameOperatorTOF_frameA.setFrameName("tof_frameA");
    frameOperatorTOF_frameA.setParentFrameName("base_link");
    frameOperatorTOF_frameB.setPositionPoint(tf::vector3(0,0,0));
    frameOperatorTOF_frameB.setFrameName("tof_frameB");
    frameOperatorTOF_frameB.setParentFrameName("base_link");
    frameOperatorTOF_frameC.setPositionPoint(tf::vector3(0,0,0));
    frameOperatorTOF_frameC.setFrameName("tof_frameC");
    frameOperatorTOF_frameC.setParentFrameName("base_link");
    frameOperatorTOF_frameD.setPositionPoint(tf::vector3(0,0,0));
    frameOperatorTOF_frameD.setFrameName("tof_frameD");
    frameOperatorTOF_frameD.setParentFrameName("base_link");
    frameOperatorTOF_frameE.setPositionPoint(tf::vector3(0,0,0));
    frameOperatorTOF_frameE.setFrameName("tof_frameE");
    frameOperatorTOF_frameE.setParentFrameName("base_link");
    frameOperatorTOF_frameF.setPositionPoint(tf::vector3(0,0,0));
    frameOperatorTOF_frameF.setFrameName("tof_frameF");
    frameOperatorTOF_frameF.setParentFrameName("base_link");
    frameOperatorTOF_frameG.setPositionPoint(tf::vector3(0,0,0));
    frameOperatorTOF_frameG.setFrameName("tof_frameG");
    frameOperatorTOF_frameG.setParentFrameName("base_link");
    frameOperatorTOF_frameH.setPositionPoint(tf::vector3(0,0,0));
    frameOperatorTOF_frameH.setFrameName("tof_frameH");
    frameOperatorTOF_frameH.setParentFrameName("base_link");

    while (ros::ok())
  {
    /**
     * This is a message object. You stuff it with data, and then publish it.
     */
    // std_msgs::String msg;
    // std::stringstream ss;
    // ss << "hello world "
    // msg.data = ss.str();
    // ROS_INFO("%s", msg.data.c_str());
    
    transformOperator.setChildFrame(frameOperatorFootprint);
    transformOperator.setParentFrame(frameOperatorOdom);
    
    transformOperator.setOdometryTransform()
    
    transformOperator.setChildFrame(frameOperatorBase_link);
    transformOperator.setParentFrame(frameOperatorFootprint);
    

    transformOperator.setChildFrame(frameOperatorCameraFrameA);
    transformOperator.setParentFrame(frameOperatorBase_link);

    transformOperator.setChildFrame(frameOperatorBase_link);
    transformOperator.setParentFrame(frameOperatorCameraFrameA);
    
    transformOperator.setChildFrame(frameOperatorBase_link);
    transformOperator.setParentFrame(frameOperatorCameraFrameB);


    transformOperator.setChildFrame(frameOperatorBase_link);
    transformOperator.setParentFrame(frameOperatorCameraFrameC);

    transformOperator.setChildFrame(frameOperatorBase_link);
    transformOperator.setParentFrame(frameOperatorTOF_frameA);


    transformOperator.setChildFrame(frameOperatorBase_link);
    transformOperator.setParentFrame(frameOperatorTOF_frameB);


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
    ros::Publisher chatter_pub = n.advertise<std_msgs::String>("chatter", 1000);
    ros::Rate loop_rate(10);

    while (ros::ok())
  {
    /**
     * This is a message object. You stuff it with data, and then publish it.
     */
    std_msgs::String msg;

    std::stringstream ss;
    ss << "hello world "
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
    ros::Publisher chatter_pub = n.advertise<std_msgs::String>("chatter", 1000);
    ros::Rate loop_rate(10);

    while (ros::ok())
  {
    /**
     * This is a message object. You stuff it with data, and then publish it.
     */
    std_msgs::String msg;

    std::stringstream ss;
    ss << "hello world "
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
    ros::Publisher chatter_pub = n.advertise<std_msgs::String>("chatter", 1000);
    ros::Rate loop_rate(10);

    while (ros::ok())
  {
    /**
     * This is a message object. You stuff it with data, and then publish it.
     */
    std_msgs::String msg;

    std::stringstream ss;
    ss << "hello world "
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
    ros::Publisher chatter_pub = n.advertise<std_msgs::String>("chatter", 1000);
    ros::Rate loop_rate(10);

    while (ros::ok())
  {
    /**
     * This is a message object. You stuff it with data, and then publish it.
     */
    std_msgs::String msg;

    std::stringstream ss;
    ss << "hello world "
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
    ros::Publisher chatter_pub = n.advertise<std_msgs::String>("chatter", 1000);
    ros::Rate loop_rate(10);

    while (ros::ok())
  {
    /**
     * This is a message object. You stuff it with data, and then publish it.
     */
    std_msgs::String msg;

    std::stringstream ss;
    ss << "hello world "
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
    ss << "hello world "
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
    ros::Subscriber sub = n.subscribe("chatter", 1000);
    ros::spin();
}

void subscriberTF(int argc, char** argv)
{
    ros::init(argc, argv, "subcriberOdometry");
    ros::NodeHandle n;
    ros::Subscriber sub = n.subscribe("chatter", 1000);
    ros::spin();
}

void subscriberMotionControl(int argc, char** argv)
{
    ros::init(argc, argv, "subcriberOdometry");
    ros::NodeHandle n;
    ros::Subscriber sub = n.subscribe("chatter", 1000);
    ros::spin();
}

void subscriberSensor(int argc, char** argv)
{
    ros::init(argc, argv, "subcriberOdometry");
    ros::NodeHandle n;
    ros::Subscriber sub = n.subscribe("chatter", 1000);
    ros::spin();
}
