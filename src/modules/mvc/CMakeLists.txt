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

add_util()
message(STATUS "add_library ${MODULE}")
add_library(${MODULE} ${SOURCES} ${HEADERS})
#target_include_directories(${MODULE} PUBLIC "${CMAKE_CURRENT_LIST_DIR}/../..")

#--------------------------------------------------------------------------------
# OpenCV
#--------------------------------------------------------------------------------
find_opencv()
find_qt5()
find_cgal()
find_eigen()

qt5_use_modules(${MODULE} Widgets OpenGL Core)
