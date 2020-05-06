cmake_minimum_required(VERSION 3.15)
project(silo-core LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)

#set(CMAKE_VERBOSE_MAKEFILE ON)

include_directories(include)
include_directories(tinyxml2-7.1.0)
include_directories(Crc32)
#include_directories(LuaJIT-2.0/src)
#include_directories(LuaJIT-2.0.5/src/buildvm)

#file(GLOB LUAJIT_SRC
#        "LuaJIT-2.0.5/src/*.c")
#file(GLOB LUAJIT_BUILDVM_SRC
#        "LuaJIT-2.0.5/src/host/*.c")

add_library(tinyxml2 tinyxml2-7.1.0/tinyxml2.cpp)
add_library(silo-core-gates src/Gates/buffer_gate.cpp src/Gates/and_gate.cpp src/Gates/not_gate.cpp)
add_library(crc32 Crc32/Crc32.cpp)
add_library(miniz miniz-2.1.0/miniz.c)


# ./configure
# make libtcc.a

# *nix
# IN "tcc-0.9.27"


# ./build-tcc.bat

# Windows
# IN "tcc-0.9.27/win32"

add_executable(silo-core src/main.cpp src/node.cpp src/value.cpp src/sender.cpp src/receiver.cpp src/simulation.cpp src/circuit.cpp src/FileLoader/logisim.cpp src/library.cpp src/fileloader.cpp src/FileLoader/local.cpp src/FileLoader/tcc.cpp src/tcclibrary.cpp include/tcclibrary.h)
target_link_libraries(silo-core silo-core-gates tinyxml2 crc32 miniz)

if(WIN32)
    include_directories(tcc-0.9.27/win32/libtcc)
    target_link_libraries(silo-core ${CMAKE_SOURCE_DIR}/tcc-0.9.27/win32/libtcc.dll)
#    include_directories(tcc-0.9.27)
    target_link_libraries(silo-core ${CMAKE_SOURCE_DIR}/tcc-0.9.27/win32/lib/libtcc1-64.a)
else()
    include_directories(tcc-0.9.27)
    target_link_libraries(silo-core ${CMAKE_SOURCE_DIR}/tcc-0.9.27/libtcc.a)
endif()
