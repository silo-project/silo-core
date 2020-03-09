cmake_minimum_required(VERSION 3.15)
project(silo)

set(CMAKE_CXX_STANDARD 17)

include_directories("include")

add_executable(silo src/main.cpp)
