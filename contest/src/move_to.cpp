#include <ros/ros.h>
#include "contest/MoveTo.h"
#include <signal.h>
#include <geometry_msgs/Twist.h>

ros::Publisher cmdVelPub;
std::string topic = "/cmd_vel_mux/input/teleop";
//void shutdown(int sig)
//{
//	cmdVelPub.publish(geometry_msgs::Twist());
//	ROS_INFO("motion ended!");
//	ros::shutdown();
//}

bool moveTo(contest::MoveTo::Request &req,
		contest::MoveTo::Response &res)
{
	geometry_msgs::Twist move_cmd;
	double rate = 50;
	ros::Rate loopRate(50); //The desired rate to run at in Hz
	double distance = 0, goal_distance, linear_speed;
	double angular = 0, goal_angle, angular_speed;
	if (req.move > 0)
	{
		linear_speed = 0.2;
		goal_distance = req.move;
	}
	else 
	{
		linear_speed = -0.2;
		goal_distance = -req.move;
	}
	move_cmd.linear.x = linear_speed;
	while (distance < goal_distance && ros::ok())
	{
		//publish the Twist message and sleep 1 cycle	
		cmdVelPub.publish(move_cmd);
	        distance += linear_speed * 1 / rate;	
		ros::spinOnce();
		loopRate.sleep();
	}
	move_cmd.linear.x = 0;

	if (req.rotate > 0)
	{
		angular_speed = 1.0;
		goal_angle = req.rotate;
	}
	else
	{
		angular_speed = -1.0;
		goal_angle = -req.rotate;
	}
	move_cmd.angular.z = angular_speed;
	while (angular < goal_angle && ros::ok())
	{
		//publish the Twist message and sleep 1 cycle	
		cmdVelPub.publish(move_cmd);
		angular += angular_speed * 1 / rate;
		ros::spinOnce();
		loopRate.sleep();
	}

}		

int main(int argc, char** argv)
{
	ros::init(argc, argv, "move_to_server");
	ros::NodeHandle n;
	cmdVelPub = n.advertise<geometry_msgs::Twist>(topic, 10);
	ros::ServiceServer service = n.advertiseService("move_to", moveTo);
	ros::spin();
	return 0;
}

