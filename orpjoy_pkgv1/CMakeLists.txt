cmake_minimum_required(VERSION 3.8)
project(orpjoy_pkgv1)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
add_executable(jsub src/joy_sub.cpp)
ament_target_dependencies(jsub rclcpp std_msgs)
target_link_libraries(jsub wiringPi)
add_executable(jpub src/joy_pub.cpp)
ament_target_dependencies(jpub rclcpp std_msgs)



install(TARGETS
  jsub
  jpub
  DESTINATION lib/${PROJECT_NAME})
ament_package()
