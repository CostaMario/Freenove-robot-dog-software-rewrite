cmake_minimum_required(VERSION 3.0.0)

project(robot-server)

add_subdirectory(libraries/rpi_ws281x)

add_executable(robot-server main.cxx)

target_include_directories(robot-server PUBLIC ./libraries/rpi_ws281x)
target_include_directories(robot-server PUBLIC ./libraries/MPU6050)
target_include_directories(robot-server PUBLIC ./libraries/PCA9685)
#target_include_directories(robot-server PUBLIC ./libraries/wiringPi-mock/wiringPi)
#target_include_directories(robot-server PUBLIC ./libraries/Sonar)

target_sources(robot-server PUBLIC libraries/MPU6050/MPU6050.cpp)
target_sources(robot-server PUBLIC libraries/PCA9685/PCA9685.cxx)
#target_sources(robot-server PUBLIC libraries/Sonar/sonar.cxx)

target_link_libraries(robot-server ws2811)
