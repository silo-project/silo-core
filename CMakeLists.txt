cmake_minimum_required(VERSION 3.15)
project(silo-core)

set(CMAKE_CXX_STANDARD 17)

include_directories("include")

add_library(silo-core-gates src/Gates/buffer_gate.cpp src/Gates/and_gate.cpp src/Gates/not_gate.cpp)

add_executable(silo-core src/main.cpp src/node.cpp src/value.cpp src/sender.cpp src/receiver.cpp src/simulation.cpp)
target_link_libraries(silo-core silo-core-gates)
