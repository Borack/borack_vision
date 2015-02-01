# Get module name
set(MODULE borack_vision)
project(${MODULE})

set(SOURCES
        main.cpp
        mainwindow.cpp
)
set(HEADERS
        mainwindow.hpp
)

set(UI_FILES 
        mainwindow.ui
)

set(QRC_FILES
#   main.qrc
)

set(QML_SOURCES

)

find_qt5()

add_executable(${MODULE} ${SOURCES} ${HEADERS} ${QRC_OUT} ${UI_HEADERS})

#--------------------------------------------------------------------------------
# Modules
#--------------------------------------------------------------------------------

option(MODULE_MVC "Build with the 'Coordinates for instant image cloning' module" ON)
if(MODULE_MVC)
find_cgal()
    add_module(mvc)
#    add_definitions(-DMODULE_MVC)
    add_core(ui)
endif(MODULE_MVC)

option(MODULE_PHOTOMONTAGE "Build with the 'Interactive Digital Photomontage' module" ON)
if(MODULE_PHOTOMONTAGE)
    add_module(photomontage)
#    add_definitions(-DMODULE_PHOTOMONTAGE)
    add_core(ui)
endif(MODULE_PHOTOMONTAGE)

option(MODULE_PYRAMID_BLENDING "Build with the 'A multiresolution spline with application to image mosaics' module" ON)
if(MODULE_PYRAMID_BLENDING)
    add_module(pyramid_blending)
#    add_definitions(-DMODULE_PHOTOMONTAGE)
    add_core(ui)
endif(MODULE_PYRAMID_BLENDING)

get_property(ALL_MODULE_LIBS GLOBAL PROPERTY MODULE_LIBS)
message(STATUS "Linking against these internal libraries: ${ALL_MODULE_LIBS}")

target_link_libraries(${MODULE} ${ALL_MODULE_LIBS})

find_opencv()
