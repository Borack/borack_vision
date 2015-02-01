setup_module()

set(SOURCES
        pb_window.cpp

)

set(HEADERS
        pb_window.hpp
)


set(UI_FILES
        pb_window.ui
)


message(STATUS "add_library ${MODULE}")
find_qt5()
add_library(${MODULE} ${SOURCES} ${HEADERS} ${UI_HEADERS})

add_core(ui)
add_core(utilities)
find_opencv()
find_eigen()
