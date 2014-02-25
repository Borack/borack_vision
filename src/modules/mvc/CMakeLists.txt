setup_module()

set(SOURCES
            meanvalue_seamless_cloning.cpp
            mesh2d.cpp
)

set(HEADERS
            meanvalue_seamless_cloning.hpp
            mvc_types.hpp
            mesh2d.hpp
)

message(STATUS "add_library ${MODULE}")
add_library(${MODULE} ${SOURCES} ${HEADERS})

add_util()


find_opencv()
find_cgal()
find_eigen()

qt5_use_modules(${MODULE} Widgets OpenGL)
