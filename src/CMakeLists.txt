cmake_minimum_required(VERSION 2.8)

#--------------------------------------------------------------------------------
# Project files
#--------------------------------------------------------------------------------
set(PROJECT_NAME borack_vision_2)

cmake_policy(SET CMP0043 NEW)
set(CMAKE_PREFIX_PATH /usr/local/Qt-5.4.0/5.4/clang_64/lib/cmake /opt/local/share/CGAL/cmake )
message(STATUS "CMAKE_PREFIX_PATH = ${CMAKE_PREFIX_PATH}")

# Compiler flags
set (CMAKE_C_FLAGS "-Wno-c++11-extensions")
set (CMAKE_CXX_FLAGS "-Wno-c++11-extensions")

project(${PROJECT_NAME})

# Setup paths
include(${CMAKE_CURRENT_SOURCE_DIR}/../cmake/Macros.cmake)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../cmake/)


#--------------------------------------------------------------------------------
# Application layer - always required
#--------------------------------------------------------------------------------
add_app()
#add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/app)
#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/app)

