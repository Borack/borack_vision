# Get module name
get_filename_component(MODULE ${CMAKE_CURRENT_LIST_DIR} NAME)
project(${MODULE})

set(SOURCES
        main.cpp
        converter.cpp
        customscene.cpp
        customview.cpp
        mainwindow.cpp
        sourcescene.cpp
        targetscene.cpp
)
set(HEADERS
           converter.hpp
           customscene.hpp
           customview.hpp
           mainwindow.hpp
           sourcescene.hpp
           targetscene.hpp
)

set(UI_FILES 
        mainwindow.ui
)

set(QRC_FILES
#   main.qrc
)

set(QML_SOURCES

)

#add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/../modules/mvc" "${PROJECT_BINARY_DIR}/../modules/mvc2")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/..")

message(STATUS "add_library ${MODULE}")
add_library(${MODULE} ${SOURCES} ${HEADERS})
#target_include_directories(${MODULE} PUBLIC "${CMAKE_CURRENT_LIST_DIR}/../.." )


find_opencv()
find_qt5()
find_eigen()
find_cgal()

qt5_use_modules(${MODULE} Widgets OpenGL Core)

