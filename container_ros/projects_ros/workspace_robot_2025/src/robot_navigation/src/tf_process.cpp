// #include "../include/tf_process.hpp"
#include "robot_navigation/tf_process.hpp"

void initializeFrame(tf::Vector3 positionXYZ, tf::Vector3 orientationRPY)
{
    // ros::init(argc, argv, "initialize_TF");
    
    nav_msgs::Odometry odometryTransform = createOdometry(tf::Vector3(0,0,0), tf::Vector3(0,0,0));
    tf::Transform frameTransform;
    tf::TransformBroadcaster broadcaster;
    
    // Translation entre les 2 repères et les axes (x, y, z).
    //< mise en place des offsets sur les axes x,y,z.
    frameTransform.setOrigin(tf::Vector3(
                        odometryTransform.pose.pose.position.x,
                        odometryTransform.pose.pose.position.y,
                        odometryTransform.pose.pose.position.z ));

    // rotation autour de X, Y, Z avec le quaternion entre les 2 repères.
    tf::Quaternion tf_quat;
    tf::quaternionMsgToTF(odometryTransform.pose.pose.orientation, tf_quat);
    frameTransform.setRotation(tf_quat);

    broadcaster.sendTransform(tf::StampedTransform(frameTransform, 
                                                    ros::Time::now(), 
                                                    "map", 
                                                    "aruco_A_base"));
    
    
    odometryTransform = createOdometry(tf::Vector3(0,0,0), tf::Vector3(0,0,0));
    
    
    // Translation entre les 2 repères et les axes (x, y, z).
    //< mise en place des offsets sur les axes x,y,z.
    frameTransform.setOrigin(tf::Vector3(
                        odometryTransform.pose.pose.position.x,
                        odometryTransform.pose.pose.position.y,
                        odometryTransform.pose.pose.position.z ));

    // rotation autour de X, Y, Z avec le quaternion entre les 2 repères.
    
    tf::quaternionMsgToTF(odometryTransform.pose.pose.orientation, tf_quat);
    frameTransform.setRotation(tf_quat);

    broadcaster.sendTransform(tf::StampedTransform(frameTransform, 
                                                    ros::Time::now(), 
                                                    "map", 
                                                    "aruco_B_base"));

    
    odometryTransform = createOdometry(tf::Vector3(0,0,0), tf::Vector3(0,0,0));
    
    
    // Translation entre les 2 repères et les axes (x, y, z).
    //< mise en place des offsets sur les axes x,y,z.
    frameTransform.setOrigin(tf::Vector3(
                        odometryTransform.pose.pose.position.x,
                        odometryTransform.pose.pose.position.y,
                        odometryTransform.pose.pose.position.z ));

    // rotation autour de X, Y, Z avec le quaternion entre les 2 repères.
    
    tf::quaternionMsgToTF(odometryTransform.pose.pose.orientation, tf_quat);
    frameTransform.setRotation(tf_quat);

    broadcaster.sendTransform(tf::StampedTransform(frameTransform, 
                                                    ros::Time::now(), 
                                                    "map", 
                                                    "aruco_C_base"));


    odometryTransform = createOdometry(tf::Vector3(0,0,0), tf::Vector3(0,0,0));
    
    
    // Translation entre les 2 repères et les axes (x, y, z).
    //< mise en place des offsets sur les axes x,y,z.
    frameTransform.setOrigin(tf::Vector3(
                        odometryTransform.pose.pose.position.x,
                        odometryTransform.pose.pose.position.y,
                        odometryTransform.pose.pose.position.z ));

    // rotation autour de X, Y, Z avec le quaternion entre les 2 repères.
    
    tf::quaternionMsgToTF(odometryTransform.pose.pose.orientation, tf_quat);
    frameTransform.setRotation(tf_quat);

    broadcaster.sendTransform(tf::StampedTransform(frameTransform, 
                                                    ros::Time::now(), 
                                                    "map", 
                                                    "aruco_D_base"));


    odometryTransform = createOdometry(tf::Vector3(0,0,0), tf::Vector3(0,0,0));
    
    
    // Translation entre les 2 repères et les axes (x, y, z).
    //< mise en place des offsets sur les axes x,y,z.
    frameTransform.setOrigin(tf::Vector3(
                        odometryTransform.pose.pose.position.x,
                        odometryTransform.pose.pose.position.y,
                        odometryTransform.pose.pose.position.z ));

    // rotation autour de X, Y, Z avec le quaternion entre les 2 repères.
    
    tf::quaternionMsgToTF(odometryTransform.pose.pose.orientation, tf_quat);
    frameTransform.setRotation(tf_quat);

    broadcaster.sendTransform(tf::StampedTransform(frameTransform, 
                                                    ros::Time::now(), 
                                                    "map", 
                                                    "odom"));


    odometryTransform = createOdometry(tf::Vector3(0,0,0), tf::Vector3(0,0,0));
    
    
    // Translation entre les 2 repères et les axes (x, y, z).
    //< mise en place des offsets sur les axes x,y,z.
    frameTransform.setOrigin(tf::Vector3(
                        odometryTransform.pose.pose.position.x,
                        odometryTransform.pose.pose.position.y,
                        odometryTransform.pose.pose.position.z ));

    // rotation autour de X, Y, Z avec le quaternion entre les 2 repères.
    
    tf::quaternionMsgToTF(odometryTransform.pose.pose.orientation, tf_quat);
    frameTransform.setRotation(tf_quat);

    broadcaster.sendTransform(tf::StampedTransform(frameTransform, 
                                                    ros::Time::now(), 
                                                    "odom", 
                                                    "footprint"));


    odometryTransform = createOdometry(tf::Vector3(0,0,0), tf::Vector3(0,0,0));
    
    
    // Translation entre les 2 repères et les axes (x, y, z).
    //< mise en place des offsets sur les axes x,y,z.
    frameTransform.setOrigin(tf::Vector3(
                        odometryTransform.pose.pose.position.x,
                        odometryTransform.pose.pose.position.y,
                        odometryTransform.pose.pose.position.z ));

    // rotation autour de X, Y, Z avec le quaternion entre les 2 repères.
    
    tf::quaternionMsgToTF(odometryTransform.pose.pose.orientation, tf_quat);
    frameTransform.setRotation(tf_quat);

    broadcaster.sendTransform(tf::StampedTransform(frameTransform, 
                                                    ros::Time::now(), 
                                                    "footprint", 
                                                    "base_link"));


    odometryTransform = createOdometry(tf::Vector3(0,0,0), tf::Vector3(0,0,0));
    
    
    // Translation entre les 2 repères et les axes (x, y, z).
    //< mise en place des offsets sur les axes x,y,z.
    frameTransform.setOrigin(tf::Vector3(
                        odometryTransform.pose.pose.position.x,
                        odometryTransform.pose.pose.position.y,
                        odometryTransform.pose.pose.position.z ));

    // rotation autour de X, Y, Z avec le quaternion entre les 2 repères.
    
    tf::quaternionMsgToTF(odometryTransform.pose.pose.orientation, tf_quat);
    frameTransform.setRotation(tf_quat);

    broadcaster.sendTransform(tf::StampedTransform(frameTransform, 
                                                    ros::Time::now(), 
                                                    "base_link", 
                                                    "base_laser"));


    odometryTransform = createOdometry(tf::Vector3(0,0,0), tf::Vector3(0,0,0));
    
    
    // Translation entre les 2 repères et les axes (x, y, z).
    //< mise en place des offsets sur les axes x,y,z.
    frameTransform.setOrigin(tf::Vector3(
                        odometryTransform.pose.pose.position.x,
                        odometryTransform.pose.pose.position.y,
                        odometryTransform.pose.pose.position.z ));

    // rotation autour de X, Y, Z avec le quaternion entre les 2 repères.
    
    tf::quaternionMsgToTF(odometryTransform.pose.pose.orientation, tf_quat);
    frameTransform.setRotation(tf_quat);

    broadcaster.sendTransform(tf::StampedTransform(frameTransform, 
                                                    ros::Time::now(), 
                                                    "base_link", 
                                                    "tof_frameA"));


    odometryTransform = createOdometry(tf::Vector3(0,0,0), tf::Vector3(0,0,0));
    
    
    // Translation entre les 2 repères et les axes (x, y, z).
    //< mise en place des offsets sur les axes x,y,z.
    frameTransform.setOrigin(tf::Vector3(
                        odometryTransform.pose.pose.position.x,
                        odometryTransform.pose.pose.position.y,
                        odometryTransform.pose.pose.position.z ));

    // rotation autour de X, Y, Z avec le quaternion entre les 2 repères.
    
    tf::quaternionMsgToTF(odometryTransform.pose.pose.orientation, tf_quat);
    frameTransform.setRotation(tf_quat);

    broadcaster.sendTransform(tf::StampedTransform(frameTransform, 
                                                    ros::Time::now(), 
                                                    "base_link", 
                                                    "tof_frameB"));


    odometryTransform = createOdometry(tf::Vector3(0,0,0), tf::Vector3(0,0,0));
    
    
    // Translation entre les 2 repères et les axes (x, y, z).
    //< mise en place des offsets sur les axes x,y,z.
    frameTransform.setOrigin(tf::Vector3(
                        odometryTransform.pose.pose.position.x,
                        odometryTransform.pose.pose.position.y,
                        odometryTransform.pose.pose.position.z ));

    // rotation autour de X, Y, Z avec le quaternion entre les 2 repères.
    
    tf::quaternionMsgToTF(odometryTransform.pose.pose.orientation, tf_quat);
    frameTransform.setRotation(tf_quat);

    broadcaster.sendTransform(tf::StampedTransform(frameTransform, 
                                                    ros::Time::now(), 
                                                    "base_link", 
                                                    "tof_frameC"));


    odometryTransform = createOdometry(tf::Vector3(0,0,0), tf::Vector3(0,0,0));
    
    
    // Translation entre les 2 repères et les axes (x, y, z).
    //< mise en place des offsets sur les axes x,y,z.
    frameTransform.setOrigin(tf::Vector3(
                        odometryTransform.pose.pose.position.x,
                        odometryTransform.pose.pose.position.y,
                        odometryTransform.pose.pose.position.z ));

    // rotation autour de X, Y, Z avec le quaternion entre les 2 repères.
    
    tf::quaternionMsgToTF(odometryTransform.pose.pose.orientation, tf_quat);
    frameTransform.setRotation(tf_quat);

    broadcaster.sendTransform(tf::StampedTransform(frameTransform, 
                                                    ros::Time::now(), 
                                                    "base_link", 
                                                    "tof_frameD"));


    odometryTransform = createOdometry(tf::Vector3(0,0,0), tf::Vector3(0,0,0));
    
    
    // Translation entre les 2 repères et les axes (x, y, z).
    //< mise en place des offsets sur les axes x,y,z.
    frameTransform.setOrigin(tf::Vector3(
                        odometryTransform.pose.pose.position.x,
                        odometryTransform.pose.pose.position.y,
                        odometryTransform.pose.pose.position.z ));

    // rotation autour de X, Y, Z avec le quaternion entre les 2 repères.
    
    tf::quaternionMsgToTF(odometryTransform.pose.pose.orientation, tf_quat);
    frameTransform.setRotation(tf_quat);

    broadcaster.sendTransform(tf::StampedTransform(frameTransform, 
                                                    ros::Time::now(), 
                                                    "base_link", 
                                                    "tof_frameE"));


    odometryTransform = createOdometry(tf::Vector3(0,0,0), tf::Vector3(0,0,0));
    
    
    // Translation entre les 2 repères et les axes (x, y, z).
    //< mise en place des offsets sur les axes x,y,z.
    frameTransform.setOrigin(tf::Vector3(
                        odometryTransform.pose.pose.position.x,
                        odometryTransform.pose.pose.position.y,
                        odometryTransform.pose.pose.position.z ));

    // rotation autour de X, Y, Z avec le quaternion entre les 2 repères.
    
    tf::quaternionMsgToTF(odometryTransform.pose.pose.orientation, tf_quat);
    frameTransform.setRotation(tf_quat);

    broadcaster.sendTransform(tf::StampedTransform(frameTransform, 
                                                    ros::Time::now(), 
                                                    "base_link", 
                                                    "tof_frameF"));


    odometryTransform = createOdometry(tf::Vector3(0,0,0), tf::Vector3(0,0,0));
    
    
    // Translation entre les 2 repères et les axes (x, y, z).
    //< mise en place des offsets sur les axes x,y,z.
    frameTransform.setOrigin(tf::Vector3(
                        odometryTransform.pose.pose.position.x,
                        odometryTransform.pose.pose.position.y,
                        odometryTransform.pose.pose.position.z ));

    // rotation autour de X, Y, Z avec le quaternion entre les 2 repères.
    
    tf::quaternionMsgToTF(odometryTransform.pose.pose.orientation, tf_quat);
    frameTransform.setRotation(tf_quat);

    broadcaster.sendTransform(tf::StampedTransform(frameTransform, 
                                                    ros::Time::now(), 
                                                    "base_link", 
                                                    "cameraFrameA"));


    // ros::spinOnce();


}


void tfUpdate(const nav_msgs::Odometry::ConstPtr& msg)
{
    static tf::TransformBroadcaster br;
    tf::Transform transform;
    tf::Quaternion q;

    const double PI = 3.14159265358979323846;

    // Récupérer les données d'odométrie
    double x = msg->pose.pose.position.x;
    double y = msg->pose.pose.position.y;
    double z = msg->pose.pose.position.z;
    double ox = msg->pose.pose.orientation.x;
    double oy = msg->pose.pose.orientation.y;
    double oz = msg->pose.pose.orientation.z;
    double ow = msg->pose.pose.orientation.w;

    // Définir la transformation pour base_link
    transform.setOrigin(tf::Vector3(x, y, z));
    q.setX(ox);
    q.setY(oy);
    q.setZ(oz);
    q.setW(ow);
    transform.setRotation(q);
    br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "odom", "footprint"));

    // Définir et diffuser d'autres transformations
    geometry_msgs::TransformStamped transformStamped;

    // Transformation de base_link à footprint
    transformStamped.header.stamp = ros::Time::now();
    transformStamped.header.frame_id = "footprint";
    transformStamped.child_frame_id = "base_link";
    transformStamped.transform.translation.x = 0.0;
    transformStamped.transform.translation.y = 0.0;
    transformStamped.transform.translation.z = 0.02;
    transformStamped.transform.rotation = tf::createQuaternionMsgFromYaw(0.0);
    br.sendTransform(transformStamped);

    // Transformation de base_link à base_laser
    transformStamped.header.frame_id = "base_link";
    transformStamped.child_frame_id = "base_laser";
    transformStamped.transform.translation.x = 0.2; // Exemple de décalage
    transformStamped.transform.translation.y = 0.0;
    transformStamped.transform.translation.z = 0.1;
    q.setRPY(0, 0, 0);
    transform.setRotation(q);
    br.sendTransform(transformStamped);

    // Transformation de base_link à sensor_frame
    transformStamped.child_frame_id = "tof_frameA";
    transformStamped.transform.translation.x = -0.01;
    transformStamped.transform.translation.y = 0.1;
    transformStamped.transform.translation.z = 0.2;
    q.setRPY(0, 0, 0);
    transform.setRotation(q);
    br.sendTransform(transformStamped);

    // Transformation de base_link à sensor_frame
    transformStamped.child_frame_id = "tof_frameB";
    transformStamped.transform.translation.x = 0.01;
    transformStamped.transform.translation.y = 0.1;
    transformStamped.transform.translation.z = 0.2;
    q.setRPY(0, 0, 0);
    transform.setRotation(q);
    br.sendTransform(transformStamped);

    // Transformation de base_link à sensor_frame
    transformStamped.child_frame_id = "tof_frameC";
    transformStamped.transform.translation.x = 0.01;
    transformStamped.transform.translation.y = 0.1;
    transformStamped.transform.translation.z = 0.2;
    q.setRPY(0, 0, -90*(PI/180));
    transform.setRotation(q);
    br.sendTransform(transformStamped);

    // Transformation de base_link à sensor_frame
    transformStamped.child_frame_id = "tof_frameD";
    transformStamped.transform.translation.x = 0.01;
    transformStamped.transform.translation.y = 0.1;
    transformStamped.transform.translation.z = 0.2;
    q.setRPY(0, 0, -90*(PI/180));
    transform.setRotation(q);
    br.sendTransform(transformStamped);

    // Transformation de base_link à sensor_frame
    transformStamped.child_frame_id = "tof_frameE";
    transformStamped.transform.translation.x = 0.01;
    transformStamped.transform.translation.y = 0.1;
    transformStamped.transform.translation.z = 0.2;
    q.setRPY(0, 0, -90*(PI/180));
    transform.setRotation(q);
    br.sendTransform(transformStamped);

    // Transformation de base_link à sensor_frame
    transformStamped.child_frame_id = "tof_frameF";
    transformStamped.transform.translation.x = 0.01;
    transformStamped.transform.translation.y = 0.1;
    transformStamped.transform.translation.z = 0.2;
    q.setRPY(0, 0, 90*(PI/180));
    transform.setRotation(q);
    br.sendTransform(transformStamped);

    // Transformation de base_link à sensor_frame
    transformStamped.child_frame_id = "cameraFrameA";
    transformStamped.transform.translation.x = 0.01;
    transformStamped.transform.translation.y = 0.1;
    transformStamped.transform.translation.z = 0.2;
    q.setRPY(0, -10*(PI/180), 0);
    transform.setRotation(q);
    br.sendTransform(transformStamped);
}



nav_msgs::Odometry createOdometry(tf::Vector3 positionXYZ, tf::Vector3 orientationRPY)
{
    nav_msgs::Odometry odometry;

    geometry_msgs::Point position;
    position.x = positionXYZ.x();
    position.y = positionXYZ.y();
    position.z = positionXYZ.z();
    odometry.pose.pose.position = position;
    
    tf::Quaternion quaternion;
    quaternion.setRPY(orientationRPY.x(), orientationRPY.y(), orientationRPY.z());
    geometry_msgs::Quaternion odom_quat;
    tf::quaternionTFToMsg(quaternion, odom_quat);
    odometry.pose.pose.orientation = odom_quat;
    
    return odometry;
}