cmake_minimum_required(VERSION 3.0.0)

project(robot-server)

add_subdirectory(libraries/rpi_ws281x)

add_executable(robot-server main.cxx libraries/RPI_MPU6050_I2C/MPU6050.cpp)
target_include_directories(robot-server PUBLIC ./libraries/rpi_ws281x)
target_include_directories(robot-server PUBLIC ./libraries/RPI_MPU6050_I2C)
target_link_libraries(robot-server ws2811)