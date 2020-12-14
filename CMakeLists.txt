cmake_minimum_required(VERSION 3.14)
project(MyEigen)

set(CMAKE_CXX_STANDARD 14)

include(cmake/lidanBase.cmake)
include(cmake/LidanBuild.cmake)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/
                    ${CMAKE_CURRENT_SOURCE_DIR}/datatype)

ADD_SUBSRC(datatypedir datatype)

add_executable(MyEigen ${datatypedir} EigenLidan.h main.cpp)