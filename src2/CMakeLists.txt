cmake_minimum_required(VERSION 2.8)

#--------------------------------------------------------------------------------
# Project files
#--------------------------------------------------------------------------------

set(PROJECT_NAME borack_vision_2)
project(${PROJECT_NAME})

set(SOURCES  main.cpp
            mainwindow.cpp
            customscene.cpp
            customview.cpp
            sourcescene.cpp
            targetscene.cpp
)

set(HEADERS mainwindow.hpp
            customscene.hpp
            customview.hpp
            sourcescene.hpp
            targetscene.hpp
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
# Executable
#--------------------------------------------------------------------------------
add_executable(${PROJECT_NAME} ${SOURCES} ${QRC_OUT} ${UI_HEADERS})
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})

qt5_use_modules(${PROJECT_NAME} Widgets OpenGL Core)
