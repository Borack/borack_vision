cmake_minimum_required(VERSION 2.8)

#--------------------------------------------------------------------------------
# Project files
#--------------------------------------------------------------------------------
set(PROJECT_NAME borack_vision_2)

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

