cmake_minimum_required(VERSION 2.8.3)
project(ic_project)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS roscpp rviz sicktoolbox std_msgs urdf geometry_msgs)

## System dependencies are found with CMake's conventions
# find_package(Boost REQUIRED COMPONENTS system)


## Uncomment this if the package has a setup.py. This macro ensures
## modules and global scripts declared therein get installed
## See http://ros.org/doc/api/catkin/html/user_guide/setup_dot_py.html
# catkin_python_setup()

#######################################
## Declare ROS messages and services ##
#######################################

## Generate messages in the 'msg' folder
# add_message_files(
#   FILES
#   Message1.msg
#   Message2.msg
# )

## Generate services in the 'srv' folder
# add_service_files(
#   FILES
#   Service1.srv
#   Service2.srv
# )

## Generate added messages and services with any dependencies listed here
# generate_messages(
#   DEPENDENCIES
#   std_msgs
# )

###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if you package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES ic_project
#  CATKIN_DEPENDS roscpp rviz sicktoolbox std_msgs urdf geometry_msgs
#  DEPENDS system_lib 
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
# include_directories(include)
include_directories(
  ${catkin_INCLUDE_DIRS}
)

## Declare a cpp library
# add_library(ic_project
#   src/${PROJECT_NAME}/ic_project.cpp
# )

## Declare a cpp executable
# add_executable(ic_project_node src/ic_project_node.cpp)

## Add cmake target dependencies of the executable/library
## as an example, message headers may need to be generated before nodes
# add_dependencies(ic_project_node ic_project_generate_messages_cpp)

## Specify libraries to link a library or executable target against
# target_link_libraries(ic_project_node
#   ${catkin_LIBRARIES}
# )

#############
## Install ##
#############

# all install targets should use catkin DESTINATION variables
# See http://ros.org/doc/api/catkin/html/adv_user_guide/variables.html

## Mark executable scripts (Python etc.) for installation
## in contrast to setup.py, you can choose the destination
# install(PROGRAMS
#   scripts/my_python_script
#   DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
# )

## Mark executables and/or libraries for installation
# install(TARGETS ic_project ic_project_node
#   ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#   LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#   RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
# )

## Mark cpp header files for installation
# install(DIRECTORY include/${PROJECT_NAME}/
#   DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
#   FILES_MATCHING PATTERN "*.h"
#   PATTERN ".svn" EXCLUDE
# )

## Mark other files for installation (e.g. launch and bag files, etc.)
# install(FILES
#   # myfile1
#   # myfile2
#   DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
# )

#############
## Testing ##
#############

## Add gtest based cpp test target and link libraries
# catkin_add_gtest(${PROJECT_NAME}-test test/test_ic_project.cpp)
# if(TARGET ${PROJECT_NAME}-test)
#   target_link_libraries(${PROJECT_NAME}-test ${PROJECT_NAME})
# endif()

## Add folders to be run by python nosetests
# catkin_add_nosetests(test)


add_executable(state_publisher src/r2d2_test.cpp)
target_link_libraries(state_publisher ${catkin_LIBRARIES})

add_executable(circle_fool src/circle_fool.cpp)
target_link_libraries(circle_fool ${catkin_LIBRARIES})

add_executable(parser src/parser.cpp)
target_link_libraries(parser ${catkin_LIBRARIES})

add_executable(control_box src/control_box.cpp)
target_link_libraries(control_box ${catkin_LIBRARIES})

add_executable(pioneer_state src/pioneer_state.cpp)
target_link_libraries(pioneer_state ${catkin_LIBRARIES})

add_executable(teleop_keyboard src/teleop_keyboard.cpp)
target_link_libraries(teleop_keyboard ${catkin_LIBRARIES})

add_executable(joypad_teleop src/joypad_teleop.cpp)
target_link_libraries(joypad_teleop ${catkin_LIBRARIES})

add_executable(name_publisher src/publisher.cpp)
target_link_libraries(name_publisher ${catkin_LIBRARIES})

add_executable(name_subscriber src/subscriber.cpp)
target_link_libraries(name_subscriber ${catkin_LIBRARIES})

