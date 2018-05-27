cmake_minimum_required(VERSION 2.8.3)
project(dynamic_introspection)

find_package(catkin REQUIRED COMPONENTS roscpp message_generation rosbag)

#find_package(Eigen REQUIRED)

find_package(Eigen3 REQUIRED)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")



add_message_files(DIRECTORY msg FILES BoolParameter.msg
                                      IntrospectionMsg.msg
                                      VectorParameter.msg
                                      DoubleParameter.msg
                                      MatrixParameter.msg
                                      IntParameter.msg
                                      StringParameter.msg)


generate_messages(
	DEPENDENCIES
	std_msgs
#	geometry_msgs
)

catkin_package(
  INCLUDE_DIRS include
  LIBRARIES ${PROJECT_NAME}
  CATKIN_DEPENDS roscpp rosbag
  DEPENDS eigen3
)



include_directories(
  include
  ${catkin_INCLUDE_DIRS}
#  ${Eigen_INCLUDE_DIRS}
  ${EIGEN_INCLUDE_DIRS}
)

#include_directories(EIGEN3_INCLUDE_DIR)


add_library(${PROJECT_NAME} src/DynamicIntrospection.cpp)
target_link_libraries(${PROJECT_NAME} ${catkin_LIBRARIES})
add_dependencies(${PROJECT_NAME} ${PROJECT_NAME}_generate_messages_cpp)

add_executable(DynamicIntrospectionExample test/DynamicIntrospectionExample.cpp)
target_link_libraries(DynamicIntrospectionExample ${PROJECT_NAME} ${catkin_LIBRARIES})

add_executable(DynamicIntrospectionBagExample test/DynamicIntrospectionBagExample.cpp)
target_link_libraries(DynamicIntrospectionBagExample ${PROJECT_NAME} ${catkin_LIBRARIES})
