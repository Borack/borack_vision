cmake_minimum_required(VERSION 2.8)

#--------------------------------------------------------------------------------
# Project files
#--------------------------------------------------------------------------------

set(PROJECT_NAME borack_vision_2)
project(${PROJECT_NAME})

set(SOURCES  main.cpp
            mainwindow.cpp
)

set(HEADERS mainwindow.hpp
)

set(QRC_FILES
#   main.qrc
)

set(QML_SOURCES
 #  qml/main.qml
 #  qml/FileOpener.qml
 #  qml/ImageViewer.qml
)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

#--------------------------------------------------------------------------------
# QT5
#--------------------------------------------------------------------------------
find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)

# Enable automoc
set(CMAKE_AUTOMOC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

QT5_ADD_RESOURCES(QRC_OUT ${QRC_FILES})


#--------------------------------------------------------------------------------
# OpenCV
#--------------------------------------------------------------------------------
set(OpenCV_DIR /opt/dacuda/opencv-2.4.3_clang/share/OpenCV )
find_package(OpenCV REQUIRED)


#--------------------------------------------------------------------------------
# Executable
#--------------------------------------------------------------------------------
add_executable(${PROJECT_NAME} ${SOURCES} ${QRC_OUT} ${QML_SOURCES})
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})

qt5_use_modules(${PROJECT_NAME} Widgets Qml Quick Core)
