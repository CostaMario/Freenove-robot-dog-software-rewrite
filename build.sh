#!/bin/bash

mkdir -p build
cmake -DCMAKE_TOOLCHAIN_FILE=../robot-src/Toolchain-RaspberryPi.cmake robot-src -B build
cmake --build build
chmod +x build/robot-server