setup_module()

set(SOURCES
        converter.cpp
)

set(HEADERS
        converter.hpp
)


message(STATUS "add_library ${MODULE}")
add_library(${MODULE} ${SOURCES} ${HEADERS})

#--------------------------------------------------------------------------------
# OpenCV
#--------------------------------------------------------------------------------
find_opencv()
find_eigen()
find_qt5()

qt5_use_modules(${MODULE} Widgets)
