cmake_minimum_required(VERSION 3.0.0)

project(robot-server)

add_subdirectory(libraries/rpi_ws281x)

add_executable(robot-server main.cxx)

target_include_directories(robot-server PUBLIC ./libraries/rpi_ws281x)

target_sources(robot-server PUBLIC libraries/MPU6050/MPU6050.cpp)

target_include_directories(robot-server PUBLIC ./libraries/MPU6050)
target_link_libraries(robot-server ws2811)
