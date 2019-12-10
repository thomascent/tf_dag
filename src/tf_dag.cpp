#include "tf_dag.h"
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>

using namespace tf2_msgs;

TFDAG::TFDAG(ros::NodeHandle &nh) : tf_listener(tf_buffer)
{
    frame_sub = nh.subscribe<tf2_msgs::TFMessage>("tf_dag", 1, &TFDAG::frame_cb, this);
}

void TFDAG::frame_cb(const TFMessage::ConstPtr &msg)
{
    std::string parent, child;

    for(auto transform : msg->transforms)
    {
        // B wants to publish to C but that's no bueno because world is already publishing to C
        // to get B into the graph

        // so 

        if(tf_buffer._frameExists(transform.child_frame_id) && tf_buffer._getParent(transform.child_frame_id, transform.header.stamp, parent) && parent != transform.header.frame_id)
        {
            child = transform.child_frame_id;

            // Scan up the tree until we reach a frame without a parent
            while(tf_buffer._getParent(child, transform.header.stamp, parent)) 
                child = parent;

            ROS_ERROR_STREAM(transform.header.frame_id << " " << transform.child_frame_id << " " << parent);
        }

        tf_broadcaster.sendTransform(transform);
    }


    // std::string parent;

    // for(auto transform : msg->transforms)
    // {
    //     // If the frame is in the tree, it has a parent and that parent doesn't match the transform's source frame
    //     if(tf_buffer._frameExists(transform.child_frame_id) &&
    //         tf_buffer._getParent(transform.child_frame_id, transform.header.stamp, parent) &&
    //         parent != transform.header.frame_id) 
    //     {
    //         tf2::Stamped<tf2::Transform> transform_to_ancestor, transform_to_child;

    //         // Scan up the tree until we reach a frame without a parent
    //         while(tf_buffer._getParent(transform.child_frame_id, transform.header.stamp, parent)) ;

    //         // publish the inverse of the transform between the target frame and the parent
    //         tf2::convert(tf_buffer.lookupTransform(transform.header.frame_id, parent, transform.header.stamp, ros::Duration(0)), transform_to_ancestor);
    //         tf2::convert(transform, transform_to_child);

    //         transform.transform = tf2::toMsg((transform_to_ancestor * transform_to_child).inverse());
    //         transform.child_frame_id = parent;
    //         transform.header.frame_id = transform.header.frame_id;
    //     }

    //     tf_broadcaster.sendTransform(transform);
    // }
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "tf_dag");
    ros::NodeHandle nh;

    TFDAG tf_dag(nh);

    ros::spin();
    return 0;
}
