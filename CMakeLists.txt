cmake_minimum_required(VERSION 2.8.3)
project(visual_servoing_ardrone)

## Find catkin and any catkin packages
find_package(catkin REQUIRED COMPONENTS 
	roscpp
	rospy 
	std_msgs 
	genmsg
	message_generation
	tf	
	message_filters
	cv_bridge
	image_transport
	sensor_msgs
)
#find_package(OpenCV 3.1.0 REQUIRED COMPONENTS core highgui imgproc imgcodecs)

## Declare ROS messages and services
add_message_files(FILES 
	SF.msg
	StampedFloat.msg)
#add_service_files(DIRECTORY srv FILES AddTwoInts.srv)

## Generate added messages and services
generate_messages(DEPENDENCIES std_msgs)

## Declare a catkin package
catkin_package(
	CATKIN_DEPENDS message_runtime std_msgs
	)

include_directories(include ${catkin_INCLUDE_DIRS})


add_executable(filter_empty_msgs src/filter_empty_msgs.cpp)
add_executable(combine_floats src/combine_floats.cpp)
add_executable(zerotwist src/zerotwist.cpp)
add_executable(tag_detect src/tag_detect.cpp)
add_executable(tag_detect2 src/tag_detect2.cpp)
add_executable(setpoints_tag src/setpoints_tag.cpp)
target_link_libraries(filter_empty_msgs ${catkin_LIBRARIES})
target_link_libraries(combine_floats ${catkin_LIBRARIES})
target_link_libraries(zerotwist ${catkin_LIBRARIES})
target_link_libraries(tag_detect ${catkin_LIBRARIES})
target_link_libraries(tag_detect2 ${catkin_LIBRARIES})
target_link_libraries(setpoints_tag ${catkin_LIBRARIES})

add_executable(simplepub src/simplepub.cpp)
target_link_libraries(simplepub ${catkin_LIBRARIES})
add_executable(tag_detect_jmod src/tag_detect_jmod.cpp)
target_link_libraries(tag_detect_jmod ${catkin_LIBRARIES})
add_executable(roomba_vel src/roomba_vel.cpp)
target_link_libraries(roomba_vel ${catkin_LIBRARIES})
add_executable(roomba_acc src/roomba_acc.cpp)
target_link_libraries(roomba_acc ${catkin_LIBRARIES})

#add_executable(image_converter src/image_converter.cpp)
#target_link_libraries(image_converter ${catkin_LIBRARIES})




# THESE ARE REALLY OLD	
#target_link_libraries(image_converter ${catkin_LIBRARIES} g2o_core g2o_stuff csparse cxsparse g2o_solver_csparse g2o_csparse_extension g2o_types_sim3 g2o_types_sba X11 opencv_core opencv_imgproc opencv_highgui opencv_imgcodecs)
#add_executable(listen_to_rpy src/listen_to_rpy.cpp)
#add_executable(quat_to_rpy src/quat_to_rpy.cpp)
#add_executable(setpoints src/setpoints.cpp)
#add_executable(pos_rpy_display src/pos_rpy_display.cpp)
#add_executable(transform_listener src/transform_listener.cpp)
#add_executable(testing src/testing.cpp)
#add_executable(newtest src/newtest.cpp)
#add_executable(tag_detect_orig src/tag_detect_orig.cpp)
#add_executable(parser src/parser.cpp)
#add_executable(listener src/listener.cpp)
#target_link_libraries(listen_to_rpy ${catkin_LIBRARIES})
#target_link_libraries(quat_to_rpy ${catkin_LIBRARIES})
#target_link_libraries(setpoints ${catkin_LIBRARIES})
#target_link_libraries(pos_rpy_display ${catkin_LIBRARIES})
#target_link_libraries(transform_listener ${catkin_LIBRARIES})
#target_link_libraries(testing ${catkin_LIBRARIES})
#target_link_libraries(newtest ${catkin_LIBRARIES})
#target_link_libraries(tag_detect_orig ${catkin_LIBRARIES})
#target_link_libraries(parser ${catkin_LIBRARIES})
#target_link_libraries(listener ${catkin_LIBRARIES})
