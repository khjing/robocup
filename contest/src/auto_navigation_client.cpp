#include "ros/ros.h"
#include "contest/AutoNavigation.h"
#include <cstdlib>
#include <actionlib/client/simple_action_client.h>
#include <move_base_msgs/MoveBaseAction.h>

int main(int argc, char **argv)
{
	ros::init(argc, argv, "auto_navigation_client");
	
	if (argc != 8)
	{
		ROS_INFO("usage: auto_navigation position.x position.y position.z orientation.x orientation.y orientation.z orientation.w");
	}

	ros::NodeHandle n;
	ros::ServiceClient client = n.serviceClient<contest::AutoNavigation>("auto_navigation");
	
	contest::AutoNavigation srv;
	srv.request.pose.position.x = atoll(argv[1]);
	srv.request.pose.position.y = atoll(argv[2]);
	srv.request.pose.position.z = atoll(argv[3]);
	srv.request.pose.orientation.x = atoll(argv[4]);
	srv.request.pose.orientation.y = atoll(argv[5]);
	srv.request.pose.orientation.z = atoll(argv[6]);
	srv.request.pose.orientation.w = atoll(argv[7]);

	if (client.call(srv))
	{
		ROS_INFO("state of navigation: %d", (int)srv.response.state);
	}
	else
	{
		ROS_ERROR("Failed to call service auto_navigation");
		return 1;
	}	

	return 0;
}
