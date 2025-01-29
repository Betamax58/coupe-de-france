#include "addons.hpp"



typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;
std::mutex motion_mutex;

std::queue<std::string> message_queue_objet_capture;
std::queue<std::string> message_queue_mode;
std::queue<std::string> message_queue_move_base;
std::queue<std::string> message_queue;

std::mutex queue_mutex;
std::condition_variable queue_cond_var;

std::condition_variable queue_cond_var_subpub_ItemPose;
std::queue<std::string> message_queue_subpub_ItemPose;
std::queue<std::string> message_queue_subpub_TOF;
std::condition_variable queue_cond_var_subpub_TOF;

std::mutex print_mutex;
std::mutex data_mutex;
std::mutex uart_mutex_motor;
std::mutex uart_mutex_gripper;
std::mutex uart_mutex_sensor;

tf_process tfProcess;

bool motionMode;
bool statusMotion, statusMoveBaseEnd, statusGuiReady;


geometry_msgs::Twist cmdVelocity;
tf::Vector3 targetPosition;



// Fonction de rappel pour les feedbacks
void feedbackCb(const move_base_msgs::MoveBaseFeedback::ConstPtr& feedback) {
    std::lock_guard<std::mutex> lock(queue_mutex);
    // message_queue.push(feedback->base_position.pose.position.x); // Exemple de mise en queue de la donnée
    queue_cond_var.notify_one();
    // ROS_INFO("Current position: x = %f", feedback->base_position.pose.position.x);
}

// Fonction pour gérer move_base
void moveBaseThread() {
    bool boolStatusMotion;
    MoveBaseClient ac("move_base", true);

    std::unique_lock<std::mutex> dataMutex(data_mutex, std::defer_lock);
    boolStatusMotion = statusMotion;
    dataMutex.unlock();
    while(boolStatusMotion==true)
    {
        std::unique_lock<std::mutex> guard(print_mutex, std::defer_lock);
        ROS_INFO("Waiting for the move_base action server to come up");
        guard.unlock();
        ac.waitForServer();

        tf::Vector3 position;
        do 
        {
            dataMutex.lock();
            position.setX(targetPosition.x());
            position.setY(targetPosition.y());
            position.setZ(targetPosition.z());
            dataMutex.unlock();
        }while ((position.x() < 0)&&(position.y() < 0));
        

        move_base_msgs::MoveBaseGoal goal;
        goal.target_pose.header.frame_id = "map";
        goal.target_pose.header.stamp = ros::Time::now();
        
        
        goal.target_pose.pose.position.x = position.x();
        goal.target_pose.pose.position.y = position.y();
        goal.target_pose.pose.orientation.w = position.z();
        

        guard.lock();
        ROS_INFO("Sending goal");
        guard.unlock();
        
        ac.sendGoal(goal, MoveBaseClient::SimpleDoneCallback(), MoveBaseClient::SimpleActiveCallback(), &feedbackCb);

        ac.waitForResult();

        if (ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
        {
            std::unique_lock<std::mutex> guard(print_mutex, std::defer_lock);
            ROS_INFO("The robot reached the goal!");
            guard.unlock();
            data_mutex.lock();
            statusMoveBaseEnd = true;
            statusMotion = false;
            data_mutex.unlock();
        }
        else
        {
            guard.lock();
            ROS_INFO("The robot failed to reach the goal.");
            guard.unlock();
            data_mutex.lock();
            statusMoveBaseEnd = true;
            statusMotion = false;
            data_mutex.unlock();
        }
    }
    std::this_thread::sleep_for(std::chrono::seconds(1));

    dataMutex.lock();
    targetPosition.setX(-1);
    targetPosition.setY(-1);
    targetPosition.setZ(0);
    dataMutex.unlock();

}

// Fonction pour changer le mode de déplacement
void monitoringModeProgramThread() {
    
    while (ros::ok()) {
        std::unique_lock<std::mutex> lock(queue_mutex);
        queue_cond_var.wait(lock, []{ return !message_queue.empty(); });

        std::string data = message_queue.front();
        message_queue.pop();
        lock.unlock();

        std::unique_lock<std::mutex> guard(print_mutex, std::defer_lock);
        ROS_INFO("Received data from queue: %s", data.c_str());
        guard.unlock();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

// Fonction pour faire correspondre les objets avec la pince
void objectCaptureProgramThread() {
    while (ros::ok()) {
        std::unique_lock<std::mutex> lock(queue_mutex);
        queue_cond_var.wait(lock, []{ return !message_queue.empty(); });

        std::string data = message_queue.front();
        message_queue.pop();
        lock.unlock();

        std::unique_lock<std::mutex> guard(print_mutex, std::defer_lock);
        ROS_INFO("Received data from queue: %s", data.c_str());
        guard.unlock();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

// Fonction pour le programme principale
void mainProgramThread() {
    
    tfProcess.init();
    tfProcess.initializeFrame(tf::Vector3(0.05, 0.05, 0),tf::Vector3(0, 0, 0));

    while (ros::ok()) {
        // std::unique_lock<std::mutex> lock(queue_mutex);
        // queue_cond_var.wait(lock, []{ return !message_queue.empty(); });

        // std::string data = message_queue.front();
        // message_queue.pop();
        // lock.unlock();
        bool status, statusGUI;
        std::unique_lock<std::mutex> dataMutex(data_mutex, std::defer_lock);
        status = statusMoveBaseEnd;
        statusGUI = statusGuiReady;
        dataMutex.unlock();

        if ((status)&&(statusGUI)) 
        {
            dataMutex.lock();
            statusMotion = true;
            statusMoveBaseEnd = false;
            statusGUI=false;
            dataMutex.unlock();
            std::unique_lock<std::mutex> guard(print_mutex, std::defer_lock);
            ROS_INFO("Ready to launch move_base target");
            guard.unlock();
        }
            
        
        

        
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

// Fonction pour communiquer avec l'écran du robot
void guiProgramThread() {
    while (ros::ok()) {
        // std::unique_lock<std::mutex> lock(queue_mutex);
        // queue_cond_var.wait(lock, []{ return !message_queue.empty(); });

        // std::string data = message_queue.front();
        // message_queue.pop();
        // lock.unlock();

        // std::unique_lock<std::mutex> guard(print_mutex, std::defer_lock);
        // ROS_INFO("Received data from queue: %s", data.c_str());
        // guard.unlock();
        std::string cmdPosition;
        bool statusGUI;
        std::unique_lock<std::mutex> dataMutex(data_mutex, std::defer_lock);
        statusGUI = statusGuiReady;
        dataMutex.unlock();
        if(!statusGUI)
        {
            float value;
            cmdPosition = getUserInputAndConvertToJson();
            dataMutex.lock();
            value = stringToFloat(getDataFromJson(cmdPosition, "x"));
            targetPosition.setX((int)value);
            value = stringToFloat(getDataFromJson(cmdPosition, "y"));
            targetPosition.setY((int)value);
            value = stringToFloat(getDataFromJson(cmdPosition, "z"));
            targetPosition.setZ((int)value);
            statusGuiReady = true;
            dataMutex.unlock();
        }

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

std::string convertStringIntoJson(const std::vector<std::string>& keys, const std::vector<std::string>& values) 
{
    try
    {
        if (keys.size() != values.size()) {
            throw std::invalid_argument("Keys and values must have the same length");
        }

        nlohmann::json jsonObject;

        for (size_t i = 0; i < keys.size(); ++i) {
            jsonObject[keys[i]] = values[i];
        }

        return jsonObject.dump();

    }catch(const nlohmann::json::out_of_range& e)
    {
        std::cerr << "JSON out of range error: " << e.what() << std::endl;
        std::unique_lock<std::mutex> guard(print_mutex, std::defer_lock);
        ROS_INFO("JSON out of range error: %s", e.what());
        guard.unlock();
    }

    
}    

std::string getDataFromJson(const std::string& jsonString, const std::string& key) 
{
    try {
        // Parse the JSON string
        nlohmann::json jsonObject = nlohmann::json::parse(jsonString);

        // Check if the key exists in the JSON object
        if (jsonObject.contains(key)) {
            // Return the value associated with the key
            return jsonObject[key].get<std::string>();
        } else {
            throw std::invalid_argument("Key not found in JSON");
        }
    } catch (const nlohmann::json::parse_error& e) {
        throw std::invalid_argument("Invalid JSON string");
    }
}

std::string floatToString(float value) 
{
    std::ostringstream oss;
    oss << value;
    return oss.str();
}

float stringToFloat(const std::string& str) 
{
    std::istringstream iss(str);
    float value;
    iss >> value;
    return value;
}

void subscriberTOF(int argc, char** argv)
{
    ros::init(argc, argv, "subcriberTOFData");
    ros::NodeHandle n;
    ros::Subscriber sub = n.subscribe("/TOF/cloudPoint", 1000, callbackTOF);
    ros::spin();
}

void subscriberItemPose(int argc, char** argv)
{
    ros::init(argc, argv, "subcriberItemPose");
    ros::NodeHandle n;
    ros::Subscriber sub = n.subscribe("/ItemPose", 1000, callbackItemPose);
    ros::spin();
}

void callbackTOF(const sensor_msgs::PointCloud::ConstPtr& msg) {
    std::vector<float> x_values;
    json j;
    
    // Extraction des valeurs x des points
    for (const geometry_msgs::Point32 point : msg->points)
    {
        x_values.push_back(point.x);
    }
    
    // Conversion en JSON
    j["tof"] = x_values;

    std::string json_str = j.dump();

    std::unique_lock<std::mutex> guard(print_mutex, std::defer_lock);
    ROS_INFO("I heard tof data JSON: %s", json_str.c_str());
    guard.unlock();

    std::unique_lock<std::mutex> lock(queue_mutex);
    message_queue_subpub_TOF.push(json_str.c_str()); // Exemple de mise en queue de la donnée
    queue_cond_var_subpub_TOF.notify_one();
    lock.unlock();
}


void callbackItemPose(const geometry_msgs::Pose::ConstPtr& msg) {
    json j;
    
    // Conversion des données Pose en JSON
    j["position"]["x"] = msg->position.x;
    j["position"]["y"] = msg->position.y;
    j["position"]["z"] = msg->position.z;
    j["orientation"]["x"] = msg->orientation.x;
    j["orientation"]["y"] = msg->orientation.y;
    j["orientation"]["z"] = msg->orientation.z;
    j["orientation"]["w"] = msg->orientation.w;

    std::string json_str = j.dump();

    std::unique_lock<std::mutex> guard(print_mutex, std::defer_lock);
    ROS_INFO("I heard: [%s]", json_str.c_str());
    guard.unlock();

    std::unique_lock<std::mutex> lock(queue_mutex, std::defer_lock);
    message_queue_subpub_ItemPose.push(json_str.c_str()); // Exemple de mise en queue de la donnée
    queue_cond_var_subpub_ItemPose.notify_one();
    lock.unlock();
}

geometry_msgs::Pose2D createPose2D(double x, double y, double theta)
{
    geometry_msgs::Pose2D pose;
    pose.x = x;
    pose.y = y;
    pose.theta = theta;
    return pose;
}

std::vector<geometry_msgs::Pose2D> createPose2DList()
{
    std::vector<geometry_msgs::Pose2D> pose_list;
    pose_list.push_back(createPose2D(1.0, 2.0, 0.5));
    pose_list.push_back(createPose2D(3.0, 4.0, 1.0));
    pose_list.push_back(createPose2D(5.0, 6.0, 1.5));
    return pose_list;
}

std::string pose2DListToJson(const std::vector<geometry_msgs::Pose2D>& pose_list)
{
    json j;
    for (size_t i = 0; i < pose_list.size(); ++i)
    {
        j[i]["x"] = pose_list[i].x;
        j[i]["y"] = pose_list[i].y;
        j[i]["theta"] = pose_list[i].theta;
    }
    return j.dump();
}

void sendJsonToQueue(const std::string& json_str, std::queue<std::string>& queue)
{
    queue.push(json_str);
}

geometry_msgs::Pose2D getPose2DFromJson(const std::string& json_str, size_t index)
{
    json j = json::parse(json_str);
    geometry_msgs::Pose2D pose;
    pose.x = j[index]["x"];
    pose.y = j[index]["y"];
    pose.theta = j[index]["theta"];
    return pose;
}

std::string getUserInputAndConvertToJson()
{
    double x, y, theta;

    try
    {
        std::unique_lock<std::mutex> guard(print_mutex);

        // Demander à l'utilisateur d'entrer les données de position 2D
        std::cout << "Entrez la position x : ";
        if (!(std::cin >> x)) throw std::invalid_argument("Entrée invalide pour x");

        std::cout << "Entrez la position y : ";
        if (!(std::cin >> y)) throw std::invalid_argument("Entrée invalide pour y");

        std::cout << "Entrez l'angle theta : ";
        if (!(std::cin >> theta)) throw std::invalid_argument("Entrée invalide pour theta");

        guard.unlock();
        
        // Créer un objet JSON et y ajouter les données
        json j;
        j["x"] = x;
        j["y"] = y;
        j["z"] = theta;

        // Convertir l'objet JSON en chaîne de caractères
        std::string json_str = j.dump();

        return json_str;
    }
    catch (const std::invalid_argument& e)
    {
        std::unique_lock<std::mutex> guard(print_mutex);
        std::cerr << "Erreur : " << e.what() << std::endl;
        guard.unlock();
        return "";
    }
}


void motionClient(tf::Vector3 motionRequest, tf::Vector3& motionResponse, std::vector<std_msgs::Bool>& stuckResponse)
{
    ros::NodeHandle n;
    ros::ServiceClient client = n.serviceClient<cdf_2025::MotionService>("driving");
    cdf_2025::MotionService srv;
    srv.request.axisXdistance = motionRequest.x();
    srv.request.axisYdistance = motionRequest.y();
    srv.request.axisZrotation = motionRequest.z();

    if (client.call(srv))
    {
        std::unique_lock<std::mutex> guard(print_mutex);
        ROS_INFO("Response: \n axisXdistance=%ld,\n axisYdistance=%ld,\n axisZrotation=%ld,\n stuckForward=%s,\n stuckBackward=%s,\n stuckRight=%s,\n stuckLeft=%s", (long int)srv.response.axisXdistanceDone, (long int)srv.response.axisYdistanceDone, (long int)srv.response.axisZrotationDone, srv.response.stuckForward ? "true" : "false", srv.response.stuckBackward ? "true" : "false", srv.response.stuckRight ? "true" : "false", srv.response.stuckLeft ? "true" : "false");
        guard.unlock();
    }
    else
    {
        std::unique_lock<std::mutex> guard(print_mutex);
        ROS_ERROR("Failed to call service check_distance");
        guard.unlock();
    }
    motionResponse = tf::Vector3(srv.response.axisXdistanceDone, srv.response.axisYdistanceDone, srv.response.axisZrotationDone);
    // motionResponse.x.data = srv.response.axisXdistanceDone;
    // motionResponse.y.data = srv.response.axisYdistanceDone;
    // motionResponse.z.data = srv.response.axisZrotationDone;
    for (size_t i = 0; i < stuckResponse.size(); i++)
    {
        if(i==0)
            stuckResponse[i].data = srv.response.stuckForward;
        if(i==1)
            stuckResponse[i].data = srv.response.stuckBackward;
        if(i==2)
            stuckResponse[i].data = srv.response.stuckRight;
        if(i==3)
            stuckResponse[i].data = srv.response.stuckLeft;

    }
}


void motionServer()
{
    ros::NodeHandle n;
    ros::ServiceServer service = n.advertiseService("driving", motionServerServiceCallback);
    
    // Initialiser le subscriber
    ros::Subscriber sub = n.subscribe("cmd_vel", 1000, motionServerSubscriberCallback);
    
    std::unique_lock<std::mutex> guard(print_mutex);
    ROS_INFO("Ready to move.");
    guard.unlock();
    ros::spin();
}


bool motionServerServiceCallback(cdf_2025::MotionService::Request &req,
                   cdf_2025::MotionService::Response &res)
{
    std::vector<geometry_msgs::Pose2D> pose_list;
    
    std::unique_lock<std::mutex> guard(motion_mutex);
    if(motionMode == false)
    {
        pose_list.push_back(createPose2D(req.axisXdistance, req.axisYdistance, req.axisZrotation));
        std::string poseJSON = pose2DListToJson( pose_list);
        
    }
    if(motionMode == false)
    {
        // espace réservé à la l'envoi de donnée.
    }
    
    guard.unlock();
    // res.distance = req.distance;
    // res.stuck = (req.distance < 10);  // Exemple de condition pour stuck
    // ROS_INFO("Request: distance=%ld", (long int)req.distance);
    // ROS_INFO("Sending back response: distance=%ld, stuck=%s", (long int)res.distance, res.stuck ? "true" : "false");
    return true;
}


void motionServerSubscriberCallback(const geometry_msgs::Twist::ConstPtr& msg)
{
    std::vector<geometry_msgs::Pose2D> pose_list;

    std::unique_lock<std::mutex> guard(motion_mutex);
    if((msg->linear.x > SPEED_FILTER_LIMIT_VALUE)&&(motionMode == true))
    {
        cmdVelocity.linear.x = msg->linear.x;
    }
    if((msg->linear.y > SPEED_FILTER_LIMIT_VALUE)&&(motionMode == true))
    {
        cmdVelocity.linear.y = msg->linear.y;
    }
    if((msg->angular.z > SPEED_FILTER_LIMIT_VALUE)&&(motionMode == true))
    {
        cmdVelocity.angular.z = msg->angular.z;
    }
    if((msg->linear.x > SPEED_FILTER_LIMIT_VALUE)&&(msg->linear.y > SPEED_FILTER_LIMIT_VALUE)&&(msg->angular.z > SPEED_FILTER_LIMIT_VALUE)&&(motionMode == true))
    {
        pose_list.push_back(createPose2D(cmdVelocity.linear.x, cmdVelocity.linear.y, cmdVelocity.angular.z));
        std::string poseJSON = pose2DListToJson( pose_list);
        // espace réservé à la l'envoi de donnée.
    }
    guard.unlock();
}


bool sendUART(const std::string& data, const std::string& device, int baudrate) {
    int uart_filestream = open(device.c_str(), O_RDWR | O_NOCTTY | O_NDELAY);
    if (uart_filestream == -1) {
        std::cerr << "Error - Unable to open UART. Ensure it is not in use by another application\n";
        return false;
    }

    struct termios options;
    tcgetattr(uart_filestream, &options);
    options.c_cflag = baudrate | CS8 | CLOCAL | CREAD;
    options.c_iflag = IGNPAR;
    options.c_oflag = 0;
    options.c_lflag = 0;
    tcflush(uart_filestream, TCIFLUSH);
    tcsetattr(uart_filestream, TCSANOW, &options);

    int count = write(uart_filestream, data.c_str(), data.length());
    if (count < 0) {
        std::cerr << "UART TX error\n";
        close(uart_filestream);
        return false;
    }

    close(uart_filestream);
    return true;
}


bool receiveUART(std::string& data, const std::string& device, int baudrate) {
    int uart_filestream = open(device.c_str(), O_RDWR | O_NOCTTY | O_NDELAY);
    if (uart_filestream == -1) {
        std::cerr << "Error - Unable to open UART. Ensure it is not in use by another application\n";
        return false;
    }

    struct termios options;
    tcgetattr(uart_filestream, &options);
    options.c_cflag = baudrate | CS8 | CLOCAL | CREAD;
    options.c_iflag = IGNPAR;
    options.c_oflag = 0;
    options.c_lflag = 0;
    tcflush(uart_filestream, TCIFLUSH);
    tcsetattr(uart_filestream, TCSANOW, &options);

    char buffer[256];
    int length = read(uart_filestream, (void*)buffer, sizeof(buffer) - 1);
    if (length < 0) {
        std::cerr << "UART RX error\n";
        close(uart_filestream);
        return false;
    } else if (length == 0) {
        std::cerr << "No data received\n";
        close(uart_filestream);
        return false;
    } else {
        buffer[length] = '\0';
        data = std::string(buffer);
    }

    close(uart_filestream);
    return true;
}

void tfUpdate(const nav_msgs::Odometry::ConstPtr& msg)
{
    static tf::TransformBroadcaster br;
    tf::Transform transform;
    tf::Quaternion q;

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
    br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "odom", "base_link"));

    // Définir et diffuser d'autres transformations
    geometry_msgs::TransformStamped transformStamped;

    // Transformation de base_link à footprint
    transformStamped.header.stamp = ros::Time::now();
    transformStamped.header.frame_id = "base_link";
    transformStamped.child_frame_id = "footprint";
    transformStamped.transform.translation.x = 0.0;
    transformStamped.transform.translation.y = 0.0;
    transformStamped.transform.translation.z = 0.0;
    transformStamped.transform.rotation = tf::createQuaternionMsgFromYaw(0.0);
    br.sendTransform(transformStamped);

    // Transformation de base_link à lidar_frame
    transformStamped.child_frame_id = "lidar_frame";
    transformStamped.transform.translation.x = 0.2; // Exemple de décalage
    transformStamped.transform.translation.y = 0.0;
    transformStamped.transform.translation.z = 0.1;
    br.sendTransform(transformStamped);

    // Transformation de base_link à sensor_frame
    transformStamped.child_frame_id = "sensor_frame";
    transformStamped.transform.translation.x = 0.1;
    transformStamped.transform.translation.y = 0.1;
    transformStamped.transform.translation.z = 0.2;
    br.sendTransform(transformStamped);

    // Transformation de base_link à camera_frame
    transformStamped.child_frame_id = "camera_frame";
    transformStamped.transform.translation.x = 0.3;
    transformStamped.transform.translation.y = 0.0;
    transformStamped.transform.translation.z = 0.5;
    br.sendTransform(transformStamped);
}


void stabilizer()
{
    std::unique_lock<std::mutex> lock(queue_mutex);
    queue_cond_var_subpub_TOF.wait(lock, []{ return !message_queue_subpub_TOF.empty(); });
    std::string data = message_queue_subpub_TOF.front();
    message_queue_subpub_TOF.pop();
    lock.unlock();
}


