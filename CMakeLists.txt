cmake_minimum_required(VERSION 3.1.0)
project(tf_dag)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  geometry_msgs
  tf2_ros
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

catkin_package()

add_executable(tf_dag src/tf_dag.cpp)
target_link_libraries(tf_dag ${catkin_LIBRARIES})

if(CATKIN_ENABLE_TESTING)
  find_package(rostest REQUIRED)
  add_rostest_gtest(test_tf_dag test/tf_dag.test src/test/tf_test.cpp)
  target_link_libraries(test_tf_dag ${catkin_LIBRARIES})
endif()
