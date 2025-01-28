#!/bin/bash

source /opt/ros/noetic/setup.bash
echo "source /opt/ros/noetic/setup.bash" >> ~/.bashrc
sudo apt-get install nlohmann-json3-dev
sudo apt-get install ros-noetic-tf
sudo apt-get install ros-noetic-move-base
sudo apt-get install ros-noetic-move-base-msgs
# catkin_make