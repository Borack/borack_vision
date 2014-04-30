setup_module()

project(${MODULE})

set(SOURCES
        customscene.cpp
        customview.cpp
)
set(HEADERS
        customscene.hpp
        customview.hpp
)

set(UI_FILES 

)

set(QRC_FILES
#   main.qrc
)

set(QML_SOURCES

)

message(STATUS "add_library ${MODULE}")
add_library(${MODULE} ${SOURCES} ${HEADERS})

find_qt5()
qt5_use_modules(${MODULE} Widgets OpenGL)