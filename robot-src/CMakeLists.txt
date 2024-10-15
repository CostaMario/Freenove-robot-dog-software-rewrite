cmake_minimum_required(VERSION 3.30.0)

add_subdirectory(libraries/rpi_ws281x)

add_executable(robot-server main.cxx)
target_include_directories(robot-server PUBLIC ./libraries/rpi_ws281x)
target_link_libraries(robot-server ws2811)