cmake_minimum_required(VERSION 2.8.3)
project(acconeer_sensor)

list(INSERT CMAKE_MODULE_PATH 0 ${CMAKE_CURRENT_LIST_DIR}/../cmake)
## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  message_generation
  genmsg
  geometry_msgs
  
)

## System dependencies are found with CMake's conventions
# find_package(Boost REQUIRED COMPONENTS system)


## Uncomment this if the package has a setup.py. This macro ensures
## modules and global scripts declared therein get installed
## See http://ros.org/doc/api/catkin/html/user_guide/setup_dot_py.html
# catkin_python_setup()

################################################
## Declare ROS messages, services and actions ##
################################################

## To declare and build messages, services or actions from within this
## package, follow these steps:
## * Let MSG_DEP_SET be the set of packages whose message types you use in
##   your messages/services/actions (e.g. std_msgs, actionlib_msgs, ...).
## * In the file package.xml:
##   * add a build_depend tag for "message_generation"
##   * add a build_depend and a exec_depend tag for each package in MSG_DEP_SET
##   * If MSG_DEP_SET isn't empty the following dependency has been pulled in
##     but can be declared for certainty nonetheless:
##     * add a exec_depend tag for "message_runtime"
## * In this file (CMakeLists.txt):
##   * add "message_generation" and every package in MSG_DEP_SET to
##     find_package(catkin REQUIRED COMPONENTS ...)
##   * add "message_runtime" and every package in MSG_DEP_SET to
##     catkin_package(CATKIN_DEPENDS ...)
##   * uncomment the add_*_files sections below as needed
##     and list every .msg/.srv/.action file to be processed
##   * uncomment the generate_messages entry below
##   * add every package in MSG_DEP_SET to generate_messages(DEPENDENCIES ...)

## Generate messages in the 'msg' folder
 add_message_files(
   FILES
   sensData.msg
 )


## Generate added messages and services with any dependencies listed here
 generate_messages(
   DEPENDENCIES
   std_msgs
   geometry_msgs
 )

################################################
## Declare ROS dynamic reconfigure parameters ##
################################################

## To declare and build dynamic reconfigure parameters within this
## package, follow these steps:
## * In the file package.xml:
##   * add a build_depend and a exec_depend tag for "dynamic_reconfigure"
## * In this file (CMakeLists.txt):
##   * add "dynamic_reconfigure" to
##     find_package(catkin REQUIRED COMPONENTS ...)
##   * uncomment the "generate_dynamic_reconfigure_options" section below
##     and list every .cfg file to be processed

## Generate dynamic reconfigure parameters in the 'cfg' folder
# generate_dynamic_reconfigure_options(
#   cfg/DynReconf1.cfg
#   cfg/DynReconf2.cfg
# )

###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if your package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
  INCLUDE_DIRS include
  LIBRARIES acconeer_sensor message_runtime
  CATKIN_DEPENDS message_runtime roscpp rospy std_msgs #${ALL_PROTOBUF_LIB}
  #DEPENDS system_lib
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories( #${CATKIN_DEVEL_PREFIX}/${CATKIN_GLOBAL_INCLUDE_DESTINATION}
  include  ${catkin_INCLUDE_DIRS}
  #./lib/acconeer
  #~/home/pi/catkin_ws/src/acconeer_sensor/lib/libacconeer_a111_r2c
  #home/pi/catkin_ws/src/acconeer_sensor/include
  #home/pi/catkin_ws/src/acconeer_sensor/lib
  
)

#add_subdirectory(lib)

#add_library(acconeer src/libacconeer.a)
#add_library(acconeer_a111_r2c src/libacconeer_a111_r2c.a)
#add_library(acc_service src/libacc_service.a)
#add_library(customer src/libcustomer.a)

set(OBJS
 ${CMAKE_CURRENT_LIST_DIR}/lib/libacconeer.a
 ${CMAKE_CURRENT_LIST_DIR}/lib/libacconeer_a111_r2c.a
 ${CMAKE_CURRENT_LIST_DIR}/lib/libacc_service.a
 ${CMAKE_CURRENT_LIST_DIR}/lib/libcustomer.a
 ${CMAKE_CURRENT_LIST_DIR}/lib/acc_board_rpi_xc112_r2b_xr112_r2b.o
)

add_executable(talker src/talker.cpp ${OBJS}
)
target_link_libraries(talker ${catkin_LIBRARIES} ${OBJS} #${CMAKE_CURRENT_LIST_DIR}/lib/libshared.so
  #/home/pi/catkin_ws/src/acconeer_sensor/lib/libacconeer.a
  #acconeer
  #/home/pi/catkin_ws/src/acconeer_sensor/lib/libacconeer_a111_r2c.a
  #acconeer_a111_r2c
  #/home/pi/catkin_ws/src/acconeer_sensor/lib/libacc_service.a
  #acc_service
  #/home/pi/catkin_ws/src/acconeer_sensor/lib/libcustomer.a
  #customer
)
set_source_files_properties(
  ${OBJS}
  PROPERTIES
  EXTERNAL_OBJECT true
  GENERATED true
)


## Declare a C++ library
# add_library(lib libacconeer.a libacconeer_a111_r2c.a libacc_service.a#${PROJECT_NAME}
#   lib/${PROJECT_NAME}/acconeer/libacconeer.a
#   lib/${PROJECT_NAME}/acconeer_a111_r2c/libacconeer_a111_r2c.a
#   lib/${PROJECT_NAME}/acc_service/libacc_service.a
#	acconeer STATIC IMPORTED
#	acconeer_a111_r2c STATIC IMPORTED
#	acc_service STATIC IMPORTED
 #)
#set_property(
#  TARGET acconeer PROPERTY IMPORTED_LOCATION /home/pi/catkin_ws/src/acconeer_sensor
#  TARGET acconeer_a111_r2c PROPERTY IMPORTED_LOCATION /home/pi/catkin_ws/src/acconeer_sensor
#  TARGET acc_service PROPERTY IMPORTED_LOCATION /home/pi/catkin_ws/src/acconeer_sensor)
#set_target_properties(talker PROPERTIES LINKER_LANGUAGE BINARY)
#add_library(acconeer src/libacconeer.a)
#add_library(acconeer_a111_r2c src/libacconeer_a111_r2c.a)
#add_library(acc_service src/libacc_service.a)
#add_library(customer src/libcustomer.a)
add_dependencies(talker acconeer_sensor_generate_messages_cpp)



add_executable(topic_subscriber src/topic_subscriber.cpp)
target_link_libraries(listener ${catkin_LIBRARIES})
add_dependencies(topic_subscriber acconeer_sensor_generate_messages_cpp)
## Add cmake target dependencies of the library
## as an example, code may need to be generated before libraries
## either from message generation or dynamic reconfigure
# add_dependencies(${PROJECT_NAME} ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

## Declare a C++ executable
## With catkin_make all packages are built within a single CMake context
## The recommended prefix ensures that target names across packages don't collide
# add_executable(${PROJECT_NAME}_node src/acconeer_sensor_node.cpp)

## Rename C++ executable without prefix
## The above recommended prefix causes long target names, the following renames the
## target back to the shorter version for ease of user use
## e.g. "rosrun someones_pkg node" instead of "rosrun someones_pkg someones_pkg_node"
# set_target_properties(${PROJECT_NAME}_node PROPERTIES OUTPUT_NAME node PREFIX "")

## Add cmake target dependencies of the executable
## same as for the library above
# add_dependencies(${PROJECT_NAME}_node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

## Specify libraries to link a library or executable target against
# target_link_libraries(${PROJECT_NAME}_node
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
# install(TARGETS ${PROJECT_NAME} ${PROJECT_NAME}_node
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
include(GNUInstallDirs)

install(TARGETS talker
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
#############
## Testing ##
#############

## Add gtest based cpp test target and link libraries
# catkin_add_gtest(${PROJECT_NAME}-test test/test_acconeer_sensor.cpp)
# if(TARGET ${PROJECT_NAME}-test)
#   target_link_libraries(${PROJECT_NAME}-test ${PROJECT_NAME})
# endif()

## Add folders to be run by python nosetests
# catkin_add_nosetests(test)
