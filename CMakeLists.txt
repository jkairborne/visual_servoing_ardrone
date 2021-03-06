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

    add_executable(combine_floats src/combine_floats.cpp)
    add_executable(zerotwist src/zerotwist.cpp)
    add_executable(tag_detect src/tag_detect.cpp)
    add_executable(tag_detect2 src/tag_detect2.cpp)
    add_executable(setpoints_tag src/setpoints_tag.cpp)
    target_link_libraries(combine_floats ${catkin_LIBRARIES})
    target_link_libraries(zerotwist ${catkin_LIBRARIES})
    target_link_libraries(tag_detect ${catkin_LIBRARIES})
    target_link_libraries(tag_detect2 ${catkin_LIBRARIES})
    target_link_libraries(setpoints_tag ${catkin_LIBRARIES})

    add_executable(roomba_vel src/roomba_vel.cpp)
    target_link_libraries(roomba_vel ${catkin_LIBRARIES})
    add_executable(roomba_acc src/roomba_acc.cpp)
    target_link_libraries(roomba_acc ${catkin_LIBRARIES})

    add_executable(vicon src/vicon.cpp)
    target_link_libraries(vicon ${catkin_LIBRARIES})
    add_executable(testtalker src/testtalker.cpp)
    target_link_libraries(testtalker ${catkin_LIBRARIES})
    add_executable(quat_to_rpy src/quat_to_rpy.cpp)
    target_link_libraries(quat_to_rpy ${catkin_LIBRARIES})
    add_executable(PoseStamped_split src/PoseStamped_split.cpp)
    target_link_libraries(PoseStamped_split ${catkin_LIBRARIES})
    add_executable(testing src/testing.cpp)
    target_link_libraries(testing ${catkin_LIBRARIES})
    add_executable(simpletest src/simpletest.cpp)
    target_link_libraries(simpletest ${catkin_LIBRARIES})

    #add_executable(listen_to_rpy src/listen_to_rpy.cpp)
    #add_executable(setpoints src/setpoints.cpp)
    #add_executable(pos_rpy_display src/pos_rpy_display.cpp)
    #add_executable(transform_listener src/transform_listener.cpp)
    #add_executable(testing src/testing.cpp)
    #add_executable(newtest src/newtest.cpp)
    #add_executable(tag_detect_orig src/tag_detect_orig.cpp)
    #add_executable(parser src/parser.cpp)
    #add_executable(listener src/listener.cpp)
    #target_link_libraries(listen_to_rpy ${catkin_LIBRARIES})
    #target_link_libraries(setpoints ${catkin_LIBRARIES})
    #target_link_libraries(pos_rpy_display ${catkin_LIBRARIES})
    #target_link_libraries(transform_listener ${catkin_LIBRARIES})
    #target_link_libraries(newtest ${catkin_LIBRARIES})
    #target_link_libraries(tag_detect_orig ${catkin_LIBRARIES})
    #target_link_libraries(parser ${catkin_LIBRARIES})
    #target_link_libraries(listener ${catkin_LIBRARIES})
