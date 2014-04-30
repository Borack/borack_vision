setup_module()

set(SOURCES
            meanvalue_seamless_cloning.cpp
            mesh2d.cpp
            mvc_sourcescene.cpp
            mvc_targetscene.cpp
            mvc_window.cpp

)

set(HEADERS
            meanvalue_seamless_cloning.hpp
            mvc_types.hpp
            mesh2d.hpp
            mvc_sourcescene.hpp
            mvc_targetscene.hpp
            mvc_window.hpp
)


set(UI_FILES
            mvc_window.ui
)


message(STATUS "add_library ${MODULE}")
find_qt5()
add_library(${MODULE} ${SOURCES} ${HEADERS} ${UI_HEADERS})

add_core(ui)
add_core(utilities)
find_opencv()
find_eigen()
find_cgal()
