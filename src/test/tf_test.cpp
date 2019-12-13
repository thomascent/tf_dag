#include <tf2_ros/transform_listener.h>
#include <gtest/gtest.h>


TEST(TestSuite, test_tf)
{
    std::string parent_frame, child_frame;
    std::vector<double> translation, rotation;

    ros::param::get("~parent_frame", parent_frame);
    ros::param::get("~child_frame", child_frame);
    ros::param::get("~translation", translation);
    ros::param::get("~rotation", rotation);

    tf2_ros::Buffer buffer;
    tf2_ros::TransformListener listener(buffer);

    auto transform_stamped = buffer.lookupTransform(parent_frame, child_frame, ros::Time(0), ros::Duration(5));

    EXPECT_DOUBLE_EQ(transform_stamped.transform.translation.x, translation[0]);
    EXPECT_DOUBLE_EQ(transform_stamped.transform.translation.y, translation[1]);
    EXPECT_DOUBLE_EQ(transform_stamped.transform.translation.z, translation[2]);
    EXPECT_DOUBLE_EQ(transform_stamped.transform.rotation.x, rotation[0]);
    EXPECT_DOUBLE_EQ(transform_stamped.transform.rotation.y, rotation[1]);
    EXPECT_DOUBLE_EQ(transform_stamped.transform.rotation.z, rotation[2]);
    EXPECT_DOUBLE_EQ(transform_stamped.transform.rotation.w, rotation[3]);
}


int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    ros::init(argc, argv, "tester");
    ros::NodeHandle nh;
    return RUN_ALL_TESTS();
}
