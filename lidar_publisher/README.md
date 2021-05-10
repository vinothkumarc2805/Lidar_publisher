## ROS node to publish dummy LIDAR data.

### Node Description:
This node describes a laser scanner fit on a robot. Data published by this node is just made up and does represent approximate reading of a lidar. below diagram represents the robot setup:

![robot setup][robot]

Range values are 1m + some noise ([0.00-0.01]) and intensity values are 100 + some noise. 
### TF details.
Laser Scanner publishes the readings with frame_id as lidar_frame. This represents a lidar sensor which is placed on top of the robot, 1m high and no offset with the center of the robot. Below figure illustrates the setup:

![tf][tf]


### Commands

Two launch files are found inside the package:
- Just launch the lidar publisher: `roslaunch lidar_publisher lidar_demo.launch`
- Launch along with rviz visualization: `roslaunch lidar_publisher lidar_rviz_demo.launch`

### Dependencies
- roscpp
- sensor_msgs
- tf

### References:
1. [ROS Lidar Example](http://wiki.ros.org/navigation/Tutorials/RobotSetup/Sensors)
2. [ROS Tf documentation](http://wiki.ros.org/tf)

[robot]: data/robot.png
[tf]: data/tf.png




