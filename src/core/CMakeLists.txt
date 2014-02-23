# Get module name
set(MODULE borack_vision)
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


find_qt5()
find_cgal()

add_module(mvc)
#add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/../modules/mvc" "${PROJECT_BINARY_DIR}/../modules/mvc")
#include_directories("${CMAKE_CURRENT_SOURCE_DIR}/..")
include_directories("/Users/sim/dev/borack_vision/src")

message(STATUS "add_library ${MODULE}")
message(STATUS "add_library ${MVC}")
#add_executable(${MODULE} ${SOURCES} ${HEADERS} ${UI_FILES})
add_executable(${MODULE} ${SOURCES} ${HEADERS} ${QRC_OUT} ${UI_HEADERS})
target_link_libraries(${MODULE} ${OpenCV_LIBS} ${CGAL_LIBRARIES} ${CGAL_3RD_PARTY_LIBRARIES} )
#target_include_directories(${MODULE} PUBLIC "${CMAKE_CURRENT_LIST_DIR}/../.." )


find_opencv()

find_eigen()

qt5_use_modules(${MODULE} Widgets OpenGL Core)

