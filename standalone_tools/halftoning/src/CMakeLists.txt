cmake_minimum_required(VERSION 2.8)

#--------------------------------------------------------------------------------
# Project files
#--------------------------------------------------------------------------------
set(PROJECT_NAME halftoning)

include(${CMAKE_CURRENT_SOURCE_DIR}/../../../cmake/Macros.cmake)

#Compiler flags
set (CMAKE_C_FLAGS "-Wno-c++11-extensions")
set (CMAKE_CXX_FLAGS "-Wno-c++11-extensions")

set(SOURCES main.cpp)
add_executable(${PROJECT_NAME} ${SOURCES}) 

    find_package(OpenCV REQUIRED)
    include_directories(${OpenCV_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
