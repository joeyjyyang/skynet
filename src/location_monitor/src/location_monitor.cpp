#include <math.h>
#include <vector>
#include <string>
#include "ros/ros.h"
#include "nav_msgs/Odometry.h" //import Odometry msg
#include "location_monitor/LandmarkDistance.h" //import LandmarkDistance msg

using std::vector;
using std::string;
using location_monitor::LandmarkDistance;

class Landmark {
public:
	Landmark(string name, double x, double y) : m_name(name), m_x(x), m_y(y) 
	{}
	
	string m_name;
	double m_x;
	double m_y;
};

class LandmarkMonitor {
public:
	LandmarkMonitor(const ros::Publisher& landmark_pub) : m_landmarks(), m_landmark_pub(landmark_pub)
	{
		InitLandmarks();
	}



	void OdomCallback(const nav_msgs::Odometry::ConstPtr& msg) {
		double x = msg->pose.pose.position.x;
		double y = msg->pose.pose.position.y;
		LandmarkDistance ld = FindClosest(x, y);
		if (ld.distance <= 5) {
			ROS_INFO("I'm near the %s", ld.name.c_str()); //print to ros log and console
		}	
		m_landmark_pub.publish(ld); //publish to /closest_landmark topic
	}
private:
	vector<Landmark> m_landmarks;
	ros::Publisher m_landmark_pub;
	void InitLandmarks() {
		m_landmarks.push_back(Landmark("Cube", 0.31, -0.99));
		m_landmarks.push_back(Landmark("Dumpster", 0.11, -2.42));
		m_landmarks.push_back(Landmark("Cylinder", -1.14, -2.88));
		m_landmarks.push_back(Landmark("Barrier", -2.59, -0.83));
		m_landmarks.push_back(Landmark("Bookshelf", -0.09, 0.53));
	}

	LandmarkDistance FindClosest(double x, double y) {
		LandmarkDistance result; //of LandmarkDistance msg type
		result.distance = -1; //initialize distance member of LandmarkDistance msg

		for (size_t i = 0; i < m_landmarks.size(); i++) {
			const Landmark& landmark = m_landmarks[i];
			double xd = landmark.m_x - x;
			double yd = landmark.m_y - y;
			double distance = sqrt(xd*xd + yd*yd);

			if (result.distance < 0 || distance < result.distance) {
				result.name = landmark.m_name;
				result.distance = distance;
			}
		}
		return result;
 	}
};

int main(int argc, char** argv) {
	ros::init(argc, argv, "location_monitor");
	ros::NodeHandle nh;
	ros::Publisher landmark_pub = nh.advertise<LandmarkDistance>("closest_landmark", 10);
	LandmarkMonitor monitor(landmark_pub);
	ros::Subscriber sub = nh.subscribe("odom", 10, &LandmarkMonitor::OdomCallback, &monitor);
	ros::spin();
	return 0;
}

