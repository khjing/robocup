#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include "tf/transform_datatypes.h"
 
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;
 
int main(int argc, char **argv){
	double yaw = -3.1415926 / 2;
	double pitch = 0.0;
	double roll = 0.0;
	ros::init(argc, argv, "simple_navigation_goals");
 
	//tell the action client that we want to spin a thread by default
	MoveBaseClient ac("move_base", true);
 
	//wait for the action server to come up
	while(!ac.waitForServer(ros::Duration(5.0))){
		ROS_INFO("Waiting for the move_base action server to come up");
	}
 
	move_base_msgs::MoveBaseGoal goal;
 
	//we'll send a goal to the robot
	goal.target_pose.header.frame_id = "base_link";
	goal.target_pose.header.stamp = ros::Time::now();
 
	goal.target_pose.pose.position.x = 2.0;
	goal.target_pose.pose.position.y = -1.0;
	//goal.target_pose.pose.orientation
	goal.target_pose.pose.orientation = tf::createQuaternionMsgFromRollPitchYaw(roll, pitch, yaw);
 
	ROS_INFO("Sending goal");
	ac.sendGoal(goal);
 
	ac.waitForResult();
 
	if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
		ROS_INFO("Moving succeeded");
	else
		ROS_INFO("The base failed to move to the goal");
 
	return 0;
}
