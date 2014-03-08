setup_module()

set(SOURCES
            photomontage.cpp

)

set(HEADERS
            photomontage.hpp
)

message(STATUS "add_library ${MODULE}")
add_library(${MODULE} ${SOURCES} ${HEADERS})

add_util()
add_3rd(gco-v3.0)
find_opencv()
find_eigen()

qt5_use_modules(${MODULE} Core)
