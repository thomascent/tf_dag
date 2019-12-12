#include "tf_dag.h"

using namespace tf2_msgs;


TFDAG::TFDAG(ros::NodeHandle &nh) : tf_listener(tf_buffer), tf_buffer(ros::Duration(1))
{
    frame_sub = nh.subscribe<tf2_msgs::TFMessage>("tf_dag", 1, &TFDAG::frame_cb, this);
}

void TFDAG::frame_cb(const TFMessage::ConstPtr &msg)
{
    std::string parent, child;

    for(auto transform : msg->transforms)
    {
        if(tf_buffer._frameExists(transform.child_frame_id) &&
            tf_buffer._getParent(transform.child_frame_id, ros::Time(0), parent) &&
            parent != transform.header.frame_id)
        {
            child = transform.child_frame_id;

            // Scan up the tree until we reach a frame without a parent
            while(tf_buffer._getParent(child, ros::Time(0), parent) && parent != transform.header.frame_id)
                child = parent;

            auto transform_to_ancestor = tf_buffer.lookupTransform(transform.child_frame_id, child, ros::Time(0), ros::Duration(0));

            transform.child_frame_id = child;
            transform.transform = tf2::toMsg(from_msg(transform_to_ancestor) * from_msg(transform));
        }

        tf_buffer.setTransform(transform, "tf_dag");
        tf_broadcaster.sendTransform(transform);
    }
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "tf_dag");
    ros::NodeHandle nh;

    TFDAG tf_dag(nh);

    ros::spin();
    return 0;
}
