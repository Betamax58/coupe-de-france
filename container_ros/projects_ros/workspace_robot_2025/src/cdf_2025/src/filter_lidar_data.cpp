#include "node.hpp"



ros::Publisher filtered_scan_pub;

void laserScanCallback(const sensor_msgs::LaserScan::ConstPtr& scan) {
    sensor_msgs::LaserScan filtered_scan = *scan;

    const double PI = 3.14159265358979323846;
    double degree = PI/180;

    // Filtrer les faisceaux laser selon vos critères
    for (size_t i = 0; i < scan->ranges.size(); ++i) {
        
        // détermination des angles de mesure des faisceaux laser du lidar
        float angle_i = scan->angle_min + i * scan->angle_increment;
        float limit_angle = 5*degree, angle_A = 90*degree,angle_B = 270*degree;
        if (((angle_A < angle_i + limit_angle)||(angle_A > angle_i - limit_angle))&&((angle_B < angle_i + limit_angle)||(angle_B > angle_i - limit_angle))) {
            filtered_scan.ranges[i] = std::numeric_limits<float>::infinity();
        }
    }

    filtered_scan_pub.publish(filtered_scan);
}

int main(int argc, char** argv) {
    ros::init(argc, argv, "laser_filter_node");
    ros::NodeHandle nh;

    ros::Subscriber scan_sub = nh.subscribe<sensor_msgs::LaserScan>("/lidar", 10, laserScanCallback); // /scan
    filtered_scan_pub = nh.advertise<sensor_msgs::LaserScan>("/filtered_scan", 10);

    ros::spin();
    return 0;
}
