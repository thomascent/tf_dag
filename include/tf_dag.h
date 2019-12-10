#pragma once

#include <ros/ros.h>
#include <tf2_ros/transform_broadcaster.h>
#include <tf2_ros/transform_listener.h>

class TFDAG
{
    tf2_ros::Buffer tf_buffer;
    tf2_ros::TransformListener tf_listener;
    tf2_ros::TransformBroadcaster tf_broadcaster;
    ros::Subscriber frame_sub;

public:
    explicit TFDAG(ros::NodeHandle &nh);
    void frame_cb(const tf2_msgs::TFMessage::ConstPtr &msg);
};
