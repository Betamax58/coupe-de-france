// #include "../include/node.hpp"
// #include "../include/process.hpp"
// #include "../include/operator.hpp"

#include "node.hpp"

// #include "tf_process.hpp"

void publisherOdometry(int argc, char** argv)
{
    ros::init(argc, argv, "publisherOdometry");
    ros::NodeHandle n;
    ros::Publisher pub = n.advertise<nav_msgs::Odometry>("/odom", 100);
    ros::Rate loop_rate(0.1);

    nav_msgs::Odometry odom;

    const double PI = 3.14159265358979323846;

  /**
   * A count of how many messages we have sent. This is used to create
   * a unique string for each message.
   */
    int count = 0;

  // Création du timer
  // TimerProcess timerProcess(&n); // Appelé toutes les 0.1 seconde

  while (ros::ok())
  {
    /**
     * This is a message object. You stuff it with data, and then publish it.
     */
    std_msgs::String msg;
    std::string data, stringValue;

    // std::stringstream ss;
    // ss << "p_n_Odometry_ID_" << count;
    // msg.data = ss.str();

    // ROS_INFO("%s", msg.data.c_str());

    // /**
    //  * The publish() function is how you send messages. The parameter
    //  * is the message object. The type of this object must agree with the type
    //  * given as a template parameter to the advertise<>() call, as was done
    //  * in the constructor above.
    //  */
    // pub.publish(msg);

    // ros::spinOnce();

    // loop_rate.sleep();
    // ++count;

    try
    {
      if(receiveUART(data, "/dev/ttyAMA0", 9600))
      {
        stringValue = getDataFromJson(data, "poseX");
        odom.pose.pose.position.x = stringToFloat(stringValue);
        stringValue = getDataFromJson(data, "poseY");
        odom.pose.pose.position.y = stringToFloat(stringValue);
        stringValue = getDataFromJson(data, "poseZ");
        odom.pose.pose.position.z = stringToFloat(stringValue);
        stringValue = getDataFromJson(data, "orientation");
        
        double degrees = (double)stringToFloat(stringValue);
        // Convertir les degrés en radians
        double radians = degrees * PI / 180.0;
        // Créer un quaternion à partir de l'angle en radians
        tf::Quaternion quaternion = tf::createQuaternionFromYaw(radians);
        // Convertir le quaternion en message ROS
        geometry_msgs::Quaternion qMsg;
        tf::quaternionTFToMsg(quaternion, qMsg);
        odom.pose.pose.orientation.x = qMsg.x;
        odom.pose.pose.orientation.y = qMsg.y;
        odom.pose.pose.orientation.z = qMsg.z;
        odom.pose.pose.orientation.w = qMsg.w;
        pub.publish(odom);
        loop_rate.sleep();
      }
      else
      {
        ROS_INFO("Unable to get data from encoder, please check encoder is connected !!!");
        loop_rate.sleep();
      }
    }catch (const std::runtime_error& e)
    {
      std::cerr << "Runtime error: " << e.what() << std::endl;
      std::unique_lock<std::mutex> guard(print_mutex, std::defer_lock);
      ROS_INFO("Receiver UART Runtime error: %s", e.what());
      guard.unlock();
    }
    catch(const std::exception& e)
    {
      std::cerr << "Exception: " << e.what() << std::endl;
      std::unique_lock<std::mutex> guard(print_mutex, std::defer_lock);
      ROS_INFO("Receiver UART Exception error: %s", e.what());
      guard.unlock();
    }
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
    ros::init(argc, argv, "publisherTOF");
    ros::NodeHandle n;
    ros::Publisher pub = n.advertise<sensor_msgs::PointCloud2>("/tof_points", 1);
    ros::Rate loop_rate(0.1);

    // tfProcess;
    // std_msgs::String msg;
    std::string data, stringValue;
    float distance;

  while (ros::ok())
  {
    /**
     * This is a message object. You stuff it with data, and then publish it.
     */
    // std_msgs::String msg;

    // std::stringstream ss;
    // ss << "hello world ";
    // msg.data = ss.str();

    // ROS_INFO("%s", msg.data.c_str());

    // /**
    //  * The publish() function is how you send messages. The parameter
    //  * is the message object. The type of this object must agree with the type
    //  * given as a template parameter to the advertise<>() call, as was done
    //  * in the constructor above.
    //  */
    // chatter_pub.publish(msg);

    // ros::spinOnce();

    geometry_msgs::PointStamped pointInParentFrame;

    sensor_msgs::PointCloud2 cloud_msg;
    cloud_msg.header.stamp = ros::Time::now();
    cloud_msg.header.frame_id = "base_link";
    cloud_msg.height = 1;
    cloud_msg.width = 6; // 6 points
    // Définir les champs de données
    sensor_msgs::PointCloud2Modifier modifier(cloud_msg);

    modifier.setPointCloud2FieldsByString(2, "xyz", "rgb");

    // Remplir les données du point
    sensor_msgs::PointCloud2Iterator<float> iter_x(cloud_msg, "x");
    sensor_msgs::PointCloud2Iterator<float> iter_y(cloud_msg, "y");
    sensor_msgs::PointCloud2Iterator<float> iter_z(cloud_msg, "z");
    sensor_msgs::PointCloud2Iterator<uint8_t> iter_r(cloud_msg, "r");
    sensor_msgs::PointCloud2Iterator<uint8_t> iter_g(cloud_msg, "g");
    sensor_msgs::PointCloud2Iterator<uint8_t> iter_b(cloud_msg, "b");

    
    try
    {
      if(receiveUART(data, "/dev/ttyAMA1", 9600))
      {
        stringValue = getDataFromJson(data, "tof1");
        tfProcess.frameOperatorTOF_frameA.setPositionPoint(tf::Vector3( stringToFloat(stringValue), 0, 0));
        pointInParentFrame = tfProcess.frameOperatorTOF_frameA.getPositionPointFromParentFrame();
        *iter_x = pointInParentFrame.point.x; // Coordonnée x
        *iter_y = pointInParentFrame.point.y; // Coordonnée y
        *iter_z = pointInParentFrame.point.z; // Coordonnée z
        *iter_r = 255; // Rouge
        *iter_g = 0;   // Vert
        *iter_b = 0;   // Bleu
        ++iter_x, ++iter_y, ++iter_z, ++iter_r, ++iter_g, ++iter_b;
        stringValue = getDataFromJson(data, "tof2");
        tfProcess.frameOperatorTOF_frameB.setPositionPoint(tf::Vector3( stringToFloat(stringValue), 0, 0)); 
        pointInParentFrame = tfProcess.frameOperatorTOF_frameB.getPositionPointFromParentFrame();
        *iter_x = pointInParentFrame.point.x; // Coordonnée x
        *iter_y = pointInParentFrame.point.y; // Coordonnée y
        *iter_z = pointInParentFrame.point.z; // Coordonnée z
        *iter_r = 255; // Rouge
        *iter_g = 0;   // Vert
        *iter_b = 0;   // Bleu
        ++iter_x, ++iter_y, ++iter_z, ++iter_r, ++iter_g, ++iter_b;
        stringValue = getDataFromJson(data, "tof3");
        tfProcess.frameOperatorTOF_frameC.setPositionPoint(tf::Vector3( stringToFloat(stringValue), 0, 0));
        pointInParentFrame = tfProcess.frameOperatorTOF_frameC.getPositionPointFromParentFrame();
        *iter_x = pointInParentFrame.point.x; // Coordonnée x
        *iter_y = pointInParentFrame.point.y; // Coordonnée y
        *iter_z = pointInParentFrame.point.z; // Coordonnée z
        *iter_r = 255; // Rouge
        *iter_g = 0;   // Vert
        *iter_b = 0;   // Bleu
        ++iter_x, ++iter_y, ++iter_z, ++iter_r, ++iter_g, ++iter_b;
        stringValue = getDataFromJson(data, "tof4");
        tfProcess.frameOperatorTOF_frameD.setPositionPoint(tf::Vector3( stringToFloat(stringValue), 0, 0)); 
        pointInParentFrame = tfProcess.frameOperatorTOF_frameD.getPositionPointFromParentFrame();
        *iter_x = pointInParentFrame.point.x; // Coordonnée x
        *iter_y = pointInParentFrame.point.y; // Coordonnée y
        *iter_z = pointInParentFrame.point.z; // Coordonnée z
        *iter_r = 255; // Rouge
        *iter_g = 0;   // Vert
        *iter_b = 0;   // Bleu
        ++iter_x, ++iter_y, ++iter_z, ++iter_r, ++iter_g, ++iter_b;
        stringValue = getDataFromJson(data, "tof5");
        tfProcess.frameOperatorTOF_frameE.setPositionPoint(tf::Vector3( stringToFloat(stringValue), 0, 0)); 
        pointInParentFrame = tfProcess.frameOperatorTOF_frameE.getPositionPointFromParentFrame();
        *iter_x = pointInParentFrame.point.x; // Coordonnée x
        *iter_y = pointInParentFrame.point.y; // Coordonnée y
        *iter_z = pointInParentFrame.point.z; // Coordonnée z
        *iter_r = 255; // Rouge
        *iter_g = 0;   // Vert
        *iter_b = 0;   // Bleu
        ++iter_x, ++iter_y, ++iter_z, ++iter_r, ++iter_g, ++iter_b;
        stringValue = getDataFromJson(data, "tof6");
        tfProcess.frameOperatorTOF_frameF.setPositionPoint(tf::Vector3( stringToFloat(stringValue), 0, 0));
        pointInParentFrame = tfProcess.frameOperatorTOF_frameF.getPositionPointFromParentFrame();
        *iter_x = pointInParentFrame.point.x; // Coordonnée x
        *iter_y = pointInParentFrame.point.y; // Coordonnée y
        *iter_z = pointInParentFrame.point.z; // Coordonnée z
        *iter_r = 255; // Rouge
        *iter_g = 0;   // Vert
        *iter_b = 0;   // Bleu
        
        pub.publish(cloud_msg);
        ros::spin();
        loop_rate.sleep();

      }
      else
      {
        ROS_INFO("Unable to get data from i2c multiplexer, please check multiplexer is connected !!!");
        loop_rate.sleep();
      }
    }catch (const std::runtime_error& e)
    {
      std::cerr << "Runtime error: " << e.what() << std::endl;
      std::unique_lock<std::mutex> guard(print_mutex, std::defer_lock);
      ROS_INFO("Receiver UART Runtime error: %s", e.what());
      guard.unlock();
    }
    catch(const std::exception& e)
    {
      std::cerr << "Exception: " << e.what() << std::endl;
      std::unique_lock<std::mutex> guard(print_mutex, std::defer_lock);
      ROS_INFO("Receiver UART Exception error: %s", e.what());
      guard.unlock();
    }
    
    
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

