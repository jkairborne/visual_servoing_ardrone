cmake_minimum_required(VERSION 2.8.3)
project(visual_servoing_ardrone)

## Find catkin and any catkin packages
find_package(catkin REQUIRED COMPONENTS 
	roscpp
	rospy 
	std_msgs 
	genmsg
	message_generation	
)

## Declare ROS messages and services
add_message_files(FILES 
	test.msg)
#add_service_files(DIRECTORY srv FILES AddTwoInts.srv)

## Generate added messages and services
generate_messages(DEPENDENCIES std_msgs)

## Declare a catkin package
catkin_package(
	CATKIN_DEPENDS message_runtime
	)

include_directories(include ${catkin_INCLUDE_DIRS})

add_executable(talker_original src/talker_original.cpp)
add_executable(talker src/talker.cpp)
add_executable(talker_multiple src/talker_multiple.cpp)
add_executable(listen_to_rpy src/listen_to_rpy.cpp)
target_link_libraries(talker ${catkin_LIBRARIES})
target_link_libraries(talker_multiple ${catkin_LIBRARIES})
target_link_libraries(listen_to_rpy ${catkin_LIBRARIES})
add_dependencies(talker publ_subs_generate_messages_cpp)
add_dependencies(talker_original publ_subs_generate_messages_cpp)

target_link_libraries(talker_original ${catkin_LIBRARIES})
add_executable(listener src/listener.cpp)
target_link_libraries(listener ${catkin_LIBRARIES})
add_dependencies(listener publ_subs_generate_messages_cpp)
