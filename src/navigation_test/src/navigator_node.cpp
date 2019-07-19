#include "ros/ros.h"
#include "geometry_msgs/Twist.h"

int main(int argc, char *argv[])
{
	ros::init(argc, argv, "navigator_node");
	ros::NodeHandle nh;
	ros::Publisher vel_pub = nh.advertise<geometry_msgs::Twist>("/mobile_base/commands/velocity", 10);

	geometry_msgs::Twist vel_msg;

	ros::Rate l_rate(50);

	while (ros::ok())
	{
		vel_msg.linear.x = 1;
		vel_msg.linear.y = 1;
		vel_msg.linear.z = 0;
		vel_msg.angular.x = 0;
		vel_msg.angular.y = 0;
		vel_msg.angular.z = 0;

		vel_pub.publish(vel_msg);
		ros::spinOnce();
		l_rate.sleep();
	}		
	
	return 0;
}
