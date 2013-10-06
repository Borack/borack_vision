cmake_minimum_required(VERSION 2.8)

#--------------------------------------------------------------------------------
# Project files
#--------------------------------------------------------------------------------

set(PROJECT_NAME borack_vision)
project(${PROJECT_NAME})

set(SOURCES  main.cpp

)

set(QRC_FILES
   main.qrc
)

set(QML_SOURCES
   qml/main.qml
)

#--------------------------------------------------------------------------------
# QT5
#--------------------------------------------------------------------------------
find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)

QT5_ADD_RESOURCES(QRC_OUT ${QRC_FILES})


#--------------------------------------------------------------------------------
# Executable
#--------------------------------------------------------------------------------
add_executable(${PROJECT_NAME} ${SOURCES} ${QRC_OUT} ${QML_SOURCES})

qt5_use_modules(${PROJECT_NAME} Widgets Qml Quick)
