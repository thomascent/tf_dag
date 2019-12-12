// Bring in my package's API, which is what I'm testing
#include "foo/foo.h"

#include <gtest/gtest.h>

// Declare another test
TEST(TestSuite, testCase2)
{
    // <test things here, calling EXPECT_* and/or ASSERT_* macros as needed>
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    ros::init(argc, argv, "tester");
    ros::NodeHandle nh;
    return RUN_ALL_TESTS();
}