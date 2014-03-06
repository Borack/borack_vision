setup_module()

set(SOURCES
        GCoptimization.cpp
        graph.cpp
        LinkedBlockList.cpp
        maxflow.cpp
)

set(HEADERS
        block.h
        energy.h
        GCoptimization.h
        graph.h
        LinkedBlockList.h
)

message(STATUS "add_library ${MODULE}")
add_library(${MODULE} ${SOURCES} ${HEADERS})
