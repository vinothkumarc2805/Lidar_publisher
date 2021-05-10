/*
ROS node to publish dummy lidar data.

Author: Vinay (me@vnay.in)
*/

#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <signal.h>

// Laser Scanner Parameters
size_t num_readings=100;
double lidar_frequency = 40;
double angle_min = -1.57; // -90 degrees
double angle_max = 1.57;  // 90 degrees
double angle_increment = 3.14/num_readings;
double time_increment = (1 / lidar_frequency) / (num_readings);
double range_min = 0.0;
double range_max = 100.0;


void shutdown_node(int sig){
	// ROS Shutdown.
	ROS_INFO("Shutting down lidar_publisher");
	ros::shutdown();
}

int main(int argc, char* argv[]){
	// Ros defaults for node initialization
	ros::init(argc,argv,"lidar_publisher");
	// Initialize a node_handle
	ros::NodeHandle lidar_node;
	// Initialize a publisher for node (50Hz frequency)
	ros::Publisher lidar_pub = lidar_node.advertise<sensor_msgs::LaserScan>("scan",50);


	signal(SIGINT, shutdown_node);

	ROS_INFO("lidar_publisher node started.");

	srand(0);

	ros::Rate freq(1.0); //Ros rate controller.

	//Create ranges and intensities pointers and allocate memories.
	double *ranges = new double[num_readings];
	double *intensities = new double[num_readings];

	while(ros::ok()){
	    for(size_t i = 0; i < num_readings; ++i){
	    	// ranges to have 1+random value; random value is in [0.00 - 0.01]
			ranges[i] = 1 + static_cast<double>(rand())/(100*static_cast<double>(RAND_MAX));
			// intensity to have 100 + random value [0-10]
			intensities[i] = 100  + 10*static_cast<double>(rand())/(static_cast<double>(RAND_MAX));;
	    }
	    ros::Time scan_time = ros::Time::now();

	    // Create a LaserScan Message
	    sensor_msgs::LaserScan scan;
	    scan.header.stamp = scan_time;
	    scan.header.frame_id = "lidar_frame";
	    scan.angle_min = angle_min;
	    scan.angle_max = angle_max;
	    scan.angle_increment = angle_increment;
	    scan.time_increment = time_increment;
	    scan.range_min = range_min;
	    scan.range_max = range_max;

	    scan.ranges.resize(num_readings);
	    scan.intensities.resize(num_readings);
	    for(uint8_t i = 0; i < num_readings; ++i){
			scan.ranges[i] = ranges[i];
			scan.intensities[i] = intensities[i];
	    }

	    lidar_pub.publish(scan);
	    freq.sleep();
	}

	// Destructors for range and intensity values.
	// (Not really necessary as compiler handles it)
	delete ranges;
	delete intensities;

	return 0;
	
}
