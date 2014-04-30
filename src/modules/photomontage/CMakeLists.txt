setup_module()

set(SOURCES
            photomontage.cpp
            pm_sourcescene.cpp
            pm_targetscene.cpp
)

set(HEADERS
            photomontage.hpp
            pm_sourcescene.hpp
            pm_targetscene.cpp
)

message(STATUS "add_library ${MODULE}")
add_library(${MODULE} ${SOURCES} ${HEADERS})

add_core(ui)
add_core(utilities)

add_3rd(gco-v3.0)
find_opencv()
find_eigen()

qt5_use_modules(${MODULE} Core)
