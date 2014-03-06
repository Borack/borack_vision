#--------------------------------------------------------------------------------
# OpenCV
#--------------------------------------------------------------------------------
macro(find_opencv)
    find_package(OpenCV REQUIRED)
    include_directories(${OpenCV_INCLUDE_DIRS})
    target_link_libraries(${MODULE} ${OpenCV_LIBS})
endmacro()


#--------------------------------------------------------------------------------
# QT5
#--------------------------------------------------------------------------------
macro(find_qt5)
    find_package(Qt5Core REQUIRED)
    find_package(Qt5Widgets REQUIRED)
    find_package(Qt5OpenGL REQUIRED)

    # Find includes in corresponding build directories
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
    # Enable automoc
    set(CMAKE_AUTOMOC ON)
    QT5_WRAP_UI(UI_HEADERS ${UI_FILES})

    set(CMAKE_INCLUDE_CURRENT_DIR ON)
    include_directories( ${CMAKE_CURRENT_BINARY_DIR} )

    QT5_ADD_RESOURCES(QRC_OUT ${QRC_FILES})
endmacro(find_qt5)


#--------------------------------------------------------------------------------
# Eigen
#--------------------------------------------------------------------------------
macro(find_eigen)
    find_package(Eigen3 REQUIRED)
    include_directories( "${EIGEN3_INCLUDE_DIR}" )
endmacro(find_eigen)


#--------------------------------------------------------------------------------
# CGAL
#--------------------------------------------------------------------------------
macro(find_cgal)
    find_package(CGAL REQUIRED)
    include( ${CGAL_USE_FILE} )
#    include_directories( ${CGAL_3RD_PARTY_INCLUDE_DIRS})

#    #Expand the list of libs we have to link to with this module
#    get_filename_component(MODULE_NAME ${MODULE_PATH} NAME)
#    set_property(GLOBAL APPEND PROPERTY MODULE_LIBS ${CGAL_LIBRARIES} ${CGAL_3RD_PARTY_LIBRARIES})
endmacro(find_cgal)


#--------------------------------------------------------------------------------
# Setup Module
#--------------------------------------------------------------------------------
macro(setup_module)
    # Get module name
    get_filename_component(MODULE ${CMAKE_CURRENT_LIST_DIR} NAME)
    project(${MODULE})
endmacro(setup_module)

#--------------------------------------------------------------------------------
# Add Module
#--------------------------------------------------------------------------------
macro(add_module NAME)
     set(B_PATH "/Users/sim/dev/borack_vision/src/modules/") #Should be an ENV variable
     set(MODULE_PATH ${B_PATH}/${NAME})
     get_filename_component(MODULE_NAME ${MODULE_PATH} NAME)


     if(NOT TARGET ${MODULE_NAME}) #Make sure that we only add this module once
        add_subdirectory(${MODULE_PATH} ${CMAKE_CURRENT_BINARY_DIR}/${NAME})
        include_directories(${MODULE_PATH})

        #Expand the list of libs we have to link to with this module
        set_property(GLOBAL APPEND PROPERTY MODULE_LIBS ${MODULE_NAME})
    endif()

    if(TARGET ${MODULE})
        target_link_libraries(${MODULE} ${MODULE_NAME})
    endif()
endmacro(add_module)

#--------------------------------------------------------------------------------
# Add Utilities
#--------------------------------------------------------------------------------
macro(add_util)
    add_module("../utilities")
endmacro(add_util)

#--------------------------------------------------------------------------------
# Add 3rd party libraries (source code)
#--------------------------------------------------------------------------------
macro(add_3rd NAME)
    add_module("../3rd_party/${NAME}")
endmacro(add_3rd)

