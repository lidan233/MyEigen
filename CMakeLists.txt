cmake_minimum_required(VERSION 3.14)
project(MyEigen)

set(CMAKE_CXX_STANDARD 14)

include(cmake/lidanBase.cmake)
include(cmake/LidanBuild.cmake)

include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/
        ${CMAKE_CURRENT_SOURCE_DIR}/datatype
        ${CMAKE_CURRENT_SOURCE_DIR}/solveMatrix
        )

ADD_SUBSRC(datatypedir datatype)
ADD_SUBSRC(solveMatrixdir solveMatrix)


add_executable(MyEigen ${datatypedir} ${solveMatrixdir} EigenLidan.h main.cpp)