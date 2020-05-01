cmake_minimum_required(VERSION 3.15)
project(silo-core)

set(CMAKE_CXX_STANDARD 17)

include_directories("include")

add_executable(silo-core src/main.cpp src/node.cpp src/value.cpp src/sender.cpp src/receiver.cpp src/Gates/buffer_gate.cpp src/simulation.cpp include/errorflag.h)
