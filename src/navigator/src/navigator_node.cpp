#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include <iostream>

class Navigator 
{
public:
	Navigator(const ros::NodeHandle &nh) : nh_(nh)
	{
		vel_pub_ = nh_.advertise<geometry_msgs::Twist>("/cmd_vel_mux/input/teleop", 1000);
	}

	void driveStraight(double speed, double distance, bool isForward)
	{
		if (isForward)
		{
			vel_msg_.linear.x = speed;
		}
		else
		{
			vel_msg_.linear.x = -speed;
		}
		vel_msg_.linear.y = 0;
		vel_msg_.linear.z = 0;
		vel_msg_.angular.x = 0;
		vel_msg_.angular.y = 0;
		vel_msg_.angular.z = 0;

		double t0 = ros::Time::now().toSec();

		double current_distance = 0.0;
		ros::Rate loop_rate(100);
	
		while (current_distance < distance)
		{
			vel_pub_.publish(vel_msg_);
			double t1 = ros::Time::now().toSec();
			current_distance = speed * (t1-t0);
			ros::spinOnce();
			loop_rate.sleep();
		}
		vel_msg_.linear.x = 0;
		vel_pub_.publish(vel_msg_);
	}

private:
	ros::NodeHandle nh_;
	ros::Publisher vel_pub_;
	ros::Subscriber pose_sub_;
	geometry_msgs::Twist vel_msg_;
};

int main(int argc, char *argv[])
{
	ros::init(argc, argv, "navigator_node");
	ros::NodeHandle nh;
	Navigator navigator(nh);

	ros::Rate loop_rate(10);
	loop_rate.sleep();

	navigator.driveStraight(1.2, 9.5, true);

	return 0;
}
