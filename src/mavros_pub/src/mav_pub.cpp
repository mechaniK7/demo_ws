#include <ros/ros.h>
#include <iostream>
#include <geometry_msgs/PoseStamped.h>

const double RUNNING_TIME = 3.0;

ros::Publisher mav_zero; // Pub zero to /mavros/local_position/pose
geometry_msgs::PoseStamped pattern_of_zero; // Pattern for publisher

int main(int argc, char **argv) {
    ros::init(argc, argv, "pub_zero_run");
    ros::NodeHandle n;
    mav_zero = n.advertise<geometry_msgs::PoseStamped>("/mavros/local_position/pose", 1);
    ros::Rate loop_rate(5);

    bool time_is_up = false;

    ros::Time start_time = ros::Time::now();

    while (ros::ok() && !time_is_up) {
        auto current_time = ros::Time::now();
        double time_since_start = (current_time - start_time).toSec();
        if (time_since_start >= RUNNING_TIME)
            time_is_up = true;

        pattern_of_zero.header.frame_id = 'map';
        pattern_of_zero.header.stamp = ros::Time::now();

        // orientation
        pattern_of_zero.pose.orientation.x = 0.0;
        pattern_of_zero.pose.orientation.y = 0.0;
        pattern_of_zero.pose.orientation.z = 0.0;
        pattern_of_zero.pose.orientation.w = 0.0;

        // position
        pattern_of_zero.pose.position.x = 0.0;
        pattern_of_zero.pose.position.y = 0.0;
        pattern_of_zero.pose.position.z = 0.0;

        mav_zero.publish(pattern_of_zero);
        ros::spinOnce();
        loop_rate.sleep();
    }
    return 0;
}