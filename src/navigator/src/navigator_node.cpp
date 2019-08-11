#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "nav_msgs/Odometry.h"
#include "tf/transform_datatypes.h"
#include "geometry_msgs/Vector3.h"

#include <cmath>

namespace skynet
{
class Navigator 
{
public:
	Navigator(const ros::NodeHandle &nh) : nh_(nh), pi_(3.14159265358979323846)
	{
		vel_pub_ = nh_.advertise<geometry_msgs::Twist>("/cmd_vel_mux/input/teleop", 100);
		odom_sub_ = nh_.subscribe("/odom", 100, &Navigator::odomCallback, this);
	}

	~Navigator()
	{
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
		const double angular_speed_rad = degreesToRadians(angular_speed_deg);
		const double relative_angle_rad = degreesToRadians(relative_angle_deg);

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

	void odomCallback(const nav_msgs::Odometry::ConstPtr &odom_msg)
	{	
		tf::Quaternion orientation_quaternion;
		tf::quaternionMsgToTF(odom_msg->pose.pose.orientation, orientation_quaternion); 
		
		double roll, pitch, yaw;
		tf::Matrix3x3(orientation_quaternion).getRPY(roll, pitch, yaw);

		orientation_rad_.x = roll;
		orientation_rad_.y = pitch;
		orientation_rad_.z = yaw;
	}

	void turnToDesiredOrientation(const double angular_speed_deg, const double desired_angle_deg)
	{
		const double yaw_deg = degreesToRadians(orientation_rad_.z);
		const double relative_angle_deg = desired_angle_deg - yaw_deg;
		const bool clockwise = ((relative_angle_deg < 0) ? true : false);
		turnInPlace(angular_speed_deg, relative_angle_deg, clockwise);
	}

	double degreesToRadians(const double degrees)
	{
		const double radians = degrees*pi_/180;
		return radians;
	}

	void quaternionToEuler(const double quaternion)
	{
	}

private:
	ros::NodeHandle nh_;
	ros::Publisher vel_pub_;
	ros::Subscriber odom_sub_;
	geometry_msgs::Twist vel_msg_;
	geometry_msgs::Vector3 orientation_rad_;
	nav_msgs::Odometry odom_msg_;
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
	
	navigator.turnToDesiredOrientation(90.0, 270.0);
/*
	loop_rate.sleep();
	
	navigator.driveStraight(1.5, 4, true);
	
	loop_rate.sleep();
	
	navigator.turnInPlace(9.5, 45.2, false);

	loop_rate.sleep();

	ros::spin();
*/
	return 0;
}
