cmake_minimum_required(VERSION 3.15)
project(silo-core LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)

#set(CMAKE_VERBOSE_MAKEFILE ON)

include(DownloadProject.cmake)

download_project(
        PROJ tinyxml2
        GIT_REPOSITORY https://github.com/leethomason/tinyxml2.git
        GIT_TAG 7.1.0
)

download_project(
        PROJ tcc
        GIT_REPOSITORY https://github.com/TinyCC/tinycc.git
        GIT_TAG release_0_9_27
)

if(WIN32)
    add_custom_target(
            tcc
            WORKING_DIRECTORY ${tcc_SOURCE_DIR}/win32
            COMMAND cmd /c "${CMAKE_SOURCE_DIR}/tcc-windows-build.bat" "${CMAKE_BINARY_DIR}"
            VERBATIM
    )
else()
    add_custom_target(
            tcc
            WORKING_DIRECTORY ${tcc_SOURCE_DIR}
            COMMAND configure
            COMMAND make
            COMMAND copy -rf include "${CMAKE_BINARY_DIR}"
            COMMAND copy -rf library "${CMAKE_BINARY_DIR}"
            COMMAND copy -f libtcc.a "${CMAKE_BINARY_DIR}"
            VERBATIM
    )
endif()

include_directories(include)
include_directories(${tcc_SOURCE_DIR})
include_directories(${tinyxml2_SOURCE_DIR})
include_directories(miniz-2.1.0)
include_directories(Crc32)
#include_directories(LuaJIT-2.0/src)
#include_directories(LuaJIT-2.0.5/src/buildvm)
include_directories(sha1)

#file(GLOB LUAJIT_SRC
#        "LuaJIT-2.0.5/src/*.c")
#file(GLOB LUAJIT_BUILDVM_SRC
#        "LuaJIT-2.0.5/src/host/*.c")

add_library(tinyxml2 ${tinyxml2_SOURCE_DIR}/tinyxml2.cpp)
add_library(silo-core-gates src/Gates/buffer_gate.cpp src/Gates/and_gate.cpp src/Gates/not_gate.cpp)
add_library(crc32 Crc32/Crc32.cpp)
add_library(miniz miniz-2.1.0/miniz.c)
add_library(sha1 sha1/sha1.cpp)

add_executable(silo-core src/main.cpp src/node.cpp src/value.cpp src/sender.cpp src/receiver.cpp src/simulation.cpp src/circuit.cpp src/FileLoader/logisim.cpp src/library.cpp src/fileloader.cpp src/FileLoader/local.cpp src/FileLoader/tcc.cpp src/tcclibrary.cpp include/tcclibrary.h src/tcpserver.cpp)
target_link_libraries(silo-core silo-core-gates tinyxml2 crc32 miniz sha1)

add_dependencies(silo-core tcc)

if(WIN32)
    target_link_libraries(silo-core ${CMAKE_BINARY_DIR}/libtcc.dll)
    #    include_directories(tcc-0.9.27)
    target_link_libraries(silo-core ${CMAKE_BINARY_DIR}/lib/libtcc1-64.a)
    target_link_libraries(silo-core ws2_32)
else()
    target_link_libraries(silo-core ${CMAKE_BINARY_DIR}/lib/libtcc.a)
    target_link_libraries(silo-core pthread)
endif()