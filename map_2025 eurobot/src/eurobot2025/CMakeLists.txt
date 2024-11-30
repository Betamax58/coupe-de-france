cmake_minimum_required(VERSION 3.0.2)
project(eurobot2025_gazebo)
find_package(catkin REQUIRED)
catkin_add_env_hooks(env_variables SHELLS bash zsh DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/env-hooks)
