cmake_minimum_required(VERSION 2.8)

#--------------------------------------------------------------------------------
# Project files
#--------------------------------------------------------------------------------

set(PROJECT_NAME borack_vision)

set(SOURCES  main.cpp

)

# SET(UI_FILES mainwindow.ui
#              imageview.ui
#              cameraparameters.ui
# )
# 
# SET(QRC_FILES registration.qrc)

#--------------------------------------------------------------------------------
# QT5
#--------------------------------------------------------------------------------
find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)

QT5_WRAP_UI(UI_OUT ${UI_FILES} )
QT5_ADD_RESOURCES(QRC_OUT ${QRC_FILES})


#--------------------------------------------------------------------------------
# Executable
#--------------------------------------------------------------------------------
add_executable(${PROJECT_NAME} ${SOURCES} ${UI_OUT} ${QRC_OUT})