#include "addons.hpp"


// typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;
// bool motionMode;

int main(int argc, char** argv) 
{
    ros::init(argc, argv, "multi_thread_example");
    ros::NodeHandle nh;

    motionMode = false;

    // Créer les threads
    std::thread move_base_thread(moveBaseThread);
    std::thread gui_program_thread(guiProgramThread);
    std::thread main_program_thread(mainProgramThread);
    std::thread object_capture_program_thread(objectCaptureProgramThread);
    std::thread monitoring_mode_program_thread(monitoringModeProgramThread);
    std::thread subscriber_tof_thread(subscriberTOF, argc, argv);
    std::thread subscriber_item_pose_thread(subscriberItemPose, argc, argv);


    // Attendre que les threads se terminent
    move_base_thread.join();
    gui_program_thread.join();
    main_program_thread.join();
    object_capture_program_thread.join();
    monitoring_mode_program_thread.join();
    subscriber_tof_thread.join();
    subscriber_item_pose_thread.join();

    return 0;
}

