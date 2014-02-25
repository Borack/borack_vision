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

#--------------------------------------------------------------------------------
# Modules
#--------------------------------------------------------------------------------

option(MODULE_MVC "Build with the 'Coordinates for instant image cloning' module" ON)
if(MODULE_MVC)
    add_module(mvc)
endif(MODULE_MVC)


option(MODULE_PHOTOMONTAGE "Build with the 'Interactive Digital Photomontage' module" ON)
if(MODULE_PHOTOMONTAGE)
#        add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/modules/photomontage)
#        include_directories(${CMAKE_CURRENT_SOURCE_DIR}/modules/photomontage) #FIXME: should be done in the core/CMakeLists.txt

#        add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/3rd_party/gco-v3.0)
#        include_directories(${CMAKE_CURRENT_SOURCE_DIR}/3rd_party/gco-v3.0) #FIXME: should be done in the core/CMakeLists.txt
endif(MODULE_PHOTOMONTAGE)



get_property(ALL_MODULE_LIBS GLOBAL PROPERTY MODULE_LIBS)
message(STATUS "Linking against these internal libraries: ${ALL_MODULE_LIBS}")

find_cgal()

add_executable(${MODULE} ${SOURCES} ${HEADERS} ${QRC_OUT} ${UI_HEADERS})
target_link_libraries(${MODULE} ${OpenCV_LIBS} ${CGAL_LIBRARIES} ${CGAL_3RD_PARTY_LIBRARIES} ${ALL_MODULE_LIBS})

find_opencv()


#qt5_use_modules(${MODULE} Widgets OpenGL Core)

