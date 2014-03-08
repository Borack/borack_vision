# Get module name
set(MODULE borack_vision)
project(${MODULE})

set(SOURCES
        main.cpp
        customscene.cpp
        customview.cpp
        mainwindow.cpp
        sourcescene.cpp
        targetscene.cpp
)
set(HEADERS
        customscene.hpp
        customview.hpp
        mainwindow.hpp
        sourcescene.hpp
        targetscene.hpp
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
find_cgal()

add_executable(${MODULE} ${SOURCES} ${HEADERS} ${QRC_OUT} ${UI_HEADERS})

#--------------------------------------------------------------------------------
# Modules
#--------------------------------------------------------------------------------

option(MODULE_MVC "Build with the 'Coordinates for instant image cloning' module" ON)
if(MODULE_MVC)
    add_module(mvc)
#    add_definitions(-DMODULE_MVC)
endif(MODULE_MVC)


option(MODULE_PHOTOMONTAGE "Build with the 'Interactive Digital Photomontage' module" ON)
if(MODULE_PHOTOMONTAGE)
    add_module(photomontage)
#    add_definitions(-DMODULE_PHOTOMONTAGE)
endif(MODULE_PHOTOMONTAGE)



get_property(ALL_MODULE_LIBS GLOBAL PROPERTY MODULE_LIBS)
message(STATUS "Linking against these internal libraries: ${ALL_MODULE_LIBS}")



target_link_libraries(${MODULE} ${ALL_MODULE_LIBS})

find_opencv()


#qt5_use_modules(${MODULE} Widgets OpenGL Core)

