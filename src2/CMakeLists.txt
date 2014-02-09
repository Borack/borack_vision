cmake_minimum_required(VERSION 2.8)

#--------------------------------------------------------------------------------
# Project files
#--------------------------------------------------------------------------------

set(PROJECT_NAME borack_vision_2)
project(${PROJECT_NAME})

# Setup paths
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../cmake/)

set(SOURCES  main.cpp
            converter.cpp
            customscene.cpp
            customview.cpp
            mainwindow.cpp
            meanvalue_seamless_cloning.cpp
            sourcescene.cpp
            targetscene.cpp
            mesh2d.cpp
)

set(HEADERS
            converter.hpp
            customscene.hpp
            customview.hpp
            mainwindow.hpp
            meanvalue_seamless_cloning.hpp
            sourcescene.hpp
            targetscene.hpp
            mvc_types.hpp
            mesh2d.hpp
)

set(UI_FILES mainwindow.ui)

set(QRC_FILES
#   main.qrc
)

set(QML_SOURCES

)


#--------------------------------------------------------------------------------
# QT5
#--------------------------------------------------------------------------------
find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5OpenGL REQUIRED)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Enable automoc
set(CMAKE_AUTOMOC ON)
QT5_WRAP_UI(UI_HEADERS ${UI_FILES})

set(CMAKE_INCLUDE_CURRENT_DIR ON)
INCLUDE_DIRECTORIES( ${CMAKE_CURRENT_BINARY_DIR} )

QT5_ADD_RESOURCES(QRC_OUT ${QRC_FILES})


#--------------------------------------------------------------------------------
# OpenCV
#--------------------------------------------------------------------------------
set(OpenCV_DIR /opt/dacuda/opencv-2.4.3_clang/share/OpenCV )
find_package(OpenCV REQUIRED)


#--------------------------------------------------------------------------------
# Eigen
#--------------------------------------------------------------------------------
find_package(Eigen3 REQUIRED)
include_directories( "${EIGEN3_INCLUDE_DIR}" )

#--------------------------------------------------------------------------------
# CGAL
#--------------------------------------------------------------------------------
find_package(CGAL REQUIRED)
include( ${CGAL_USE_FILE} )



#--------------------------------------------------------------------------------
# Executable
#--------------------------------------------------------------------------------
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} ${QRC_OUT} ${UI_HEADERS})
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS} ${CGAL_LIBRARIES})

qt5_use_modules(${PROJECT_NAME} Widgets OpenGL Core)
