#include <iostream>
#define _USE_MATH_DEFINES
#include <cmath>
#include <geometry_msgs/PoseStamped.h>
#include <eigen3/Eigen/Dense>

geometry_msgs::PoseStamped rot_PX4(geometry_msgs::PoseStamped data){
	geometry_msgs::PoseStamped ans;
	ans.header = data.header;

	ans.pose.position.x = - data.pose.position.y;
	ans.pose.position.y = data.pose.position.x;
	ans.pose.position.z = data.pose.position.z;

	Eigen::Quaterniond data_q(data.pose.orientation.w, data.pose.orientation.x, data.pose.orientation.y, data.pose.orientation.z);
	Eigen::Quaterniond rot_q(Eigen::AngleAxisd(0.0, Eigen::Vector3d::UnitX())	// roll
		* Eigen::AngleAxisd(0.0, Eigen::Vector3d::UnitY())			// pitch
		* Eigen::AngleAxisd((2.0+1.0/2.0)*M_PI, Eigen::Vector3d::UnitZ()));		// yaw
	Eigen::Quaterniond ans_q = rot_q * data_q;

	ans.pose.orientation.w = ans_q.w();
	ans.pose.orientation.x = ans_q.x();
	ans.pose.orientation.y = ans_q.y();
	ans.pose.orientation.z = ans_q.z();



	return ans;
}
