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

	void driveStraight(double linear_speed, double desired_distance, bool forward)
	{
		if (forward)
		{
			vel_msg_.linear.x = linear_speed;
		}
		else
		{
			vel_msg_.linear.x = -linear_speed;
		}
		vel_msg_.linear.y = 0;
		vel_msg_.linear.z = 0;
		vel_msg_.angular.x = 0;
		vel_msg_.angular.y = 0;
		vel_msg_.angular.z = 0;

		double timestamp_0 = ros::Time::now().toSec();
		double current_distance = 0.0;
		ros::Rate loop_rate(100);
	
		while (current_distance < desired_distance)
		{
			vel_pub_.publish(vel_msg_);
			double timestamp_1 = ros::Time::now().toSec();
			current_distance = linear_speed * (timestamp_1 - timestamp_0);
			ros::spinOnce();
			loop_rate.sleep();
		}
		vel_msg_.linear.x = 0;
		vel_pub_.publish(vel_msg_);
	}

	void turnInPlace(double angular_speed, double relative_angle, double clockwise)
	{
		vel_msg_.linear.x =0;
		vel_msg_.linear.y =0;
		vel_msg_.linear.z =0;
		vel_msg_.angular.x = 0;
		vel_msg_.angular.y = 0;

		if (clockwise)
		{	
			vel_msg_.angular.z = -angular_speed;
		}
		else
			vel_msg_.angular.z = angular_speed;

		double timestamp_0 = ros::Time::now().toSec();
		double current_angle = 0.0;
		ros::Rate loop_rate(100);
			
		while (current_angle < relative_angle)
		{
			vel_pub_.publish(vel_msg_);
			double timestamp_1 = ros::Time::now().toSec();
			current_angle = angular_speed * (timestamp_1 - timestamp_0);
			ros::spinOnce();
			loop_rate.sleep();
		}
		vel_msg_.angular.z = 0;
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
	navigator.turnInPlace(2.1, 12.2, false);

	return 0;
}
