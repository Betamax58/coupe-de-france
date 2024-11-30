This repository is for the first version of map 2025.

For the simulation,follow these instructions  :

# Running the simulation

![Table 2025](images/cdf2025.png)

Clone the repository:
```bash
git clone [https://github.com/Betamax58/coupe-de-france.git]
cd map_2025
```
run commands for the gazebo simulation
```bash
catkin_make
source install/setup.bash
roslaunch eurobot2025_gazebo eurobot.launch
```



> **Note &#9432; :** for systems with low RAM (<16Gb), it is recommended to compile using `colcon build --symlink-install --executor sequential` to avoid running out of memory.
