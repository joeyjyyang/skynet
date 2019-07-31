#include "ros/ros.h"
#include "geometry_msgs/Twist.h"

class Navigator 
{
public:
	Navigator(const ros::NodeHandle &nh) : nh_(nh)
	{
		vel_pub_ = nh_.advertise<geometry_msgs::Twist>("/mobile_base/commands/velocity", 10);
	}

	void publishData()
	{
		vel_msg_.linear.x = 2;
		vel_msg_.linear.y = 0;
		vel_msg_.linear.z = 0;
		vel_msg_.angular.x = 2;
		vel_msg_.angular.y = 0;
		vel_msg_.angular.z = 0;

		vel_pub_.publish(vel_msg_);
	}


private:
	ros::NodeHandle nh_;
	ros::Publisher vel_pub_;
	geometry_msgs::Twist vel_msg_;

};

int main(int argc, char *argv[])
{
	ros::init(argc, argv, "navigator_node");
	ros::NodeHandle nh;
	Navigator navigator(nh);
	
	ros::Rate l_rate(50);

	while (ros::ok())
	{
		navigator.publishData();
		ros::spinOnce();
		l_rate.sleep();
	}		
	
	return 0;
}
