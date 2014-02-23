

set(SOURCES
            ${SOURCES}
            ${CMAKE_CURRENT_SOURCE_DIR}/meanvalue_seamless_cloning.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/mesh2d.cpp
            PARENT_SCOPE
)

set(HEADERS
            ${HEADERS}
            ${CMAKE_CURRENT_SOURCE_DIR}/meanvalue_seamless_cloning.hpp
            ${CMAKE_CURRENT_SOURCE_DIR}/mvc_types.hpp
            ${CMAKE_CURRENT_SOURCE_DIR}/mesh2d.hpp
            PARENT_SCOPE
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
