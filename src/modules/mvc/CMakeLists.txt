setup_module()

set(SOURCES
            meanvalue_seamless_cloning.cpp
            mesh2d.cpp
            mvc_sourcescene.cpp
            mvc_targetscene.cpp

)

set(HEADERS
            meanvalue_seamless_cloning.hpp
            mvc_types.hpp
            mesh2d.hpp
            mvc_sourcescene.hpp
            mvc_targetscene.hpp
)

message(STATUS "add_library ${MODULE}")
add_library(${MODULE} ${SOURCES} ${HEADERS})

add_core(utilities)
find_opencv()
find_eigen()
find_cgal()

qt5_use_modules(${MODULE} Widgets OpenGL)
