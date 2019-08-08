#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include <cmath>

namespace skynet
{
class Navigator 
{
public:
	Navigator(const ros::NodeHandle &nh) : nh_(nh), pi_(3.14159265358979323846)
	{
		vel_pub_ = nh_.advertise<geometry_msgs::Twist>("/cmd_vel_mux/input/teleop", 1000);
	}

	void driveStraight(const double linear_speed, const double desired_distance, const bool forward)
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
			current_distance = linear_speed*(timestamp_1-timestamp_0);
			ros::spinOnce();
			loop_rate.sleep();
		}
		vel_msg_.linear.x = 0;
		vel_pub_.publish(vel_msg_);
	}

	void turnInPlace(const double angular_speed_deg, const double relative_angle_deg, const double clockwise)
	{
		const double angular_speed_rad = angular_speed_deg*pi_/180;
		const double relative_angle_rad = relative_angle_deg*pi_/180;

		vel_msg_.linear.x =0;
		vel_msg_.linear.y =0;
		vel_msg_.linear.z =0;
		vel_msg_.angular.x = 0;
		vel_msg_.angular.y = 0;

		if (clockwise)
		{	
			vel_msg_.angular.z = -angular_speed_rad;
		}
		else
			vel_msg_.angular.z = angular_speed_rad;

		double timestamp_0 = ros::Time::now().toSec();
		double current_angle_rad = 0.0;
		ros::Rate loop_rate(100);
			
		while (current_angle_rad < relative_angle_rad)
		{
			vel_pub_.publish(vel_msg_);
			double timestamp_1 = ros::Time::now().toSec();
			current_angle_rad = angular_speed_rad*(timestamp_1-timestamp_0);
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
	const double pi_;
};
}

int main(int argc, char *argv[])
{
	ros::init(argc, argv, "navigator_node");
	ros::NodeHandle nh;
	skynet::Navigator navigator(nh);

	ros::Rate loop_rate(10);
	
	loop_rate.sleep();
	
	navigator.driveStraight(1.5, 4, true);
	
	loop_rate.sleep();
	
	navigator.turnInPlace(9.5, 45.2, false);

	return 0;
}
