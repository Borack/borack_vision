#--------------------------------------------------------------------------------
# OpenCV
#--------------------------------------------------------------------------------
macro(find_opencv)
    find_package(OpenCV REQUIRED)
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
    INCLUDE_DIRECTORIES( ${CMAKE_CURRENT_BINARY_DIR} )

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
endmacro(find_cgal)



#--------------------------------------------------------------------------------
# Setup Module
#--------------------------------------------------------------------------------
macro(setup_module)
    # Get module name
    get_filename_component(MODULE ${CMAKE_CURRENT_LIST_DIR} NAME)
    project(${MODULE})
endmacro(add_module)

#--------------------------------------------------------------------------------
# Add Module
#--------------------------------------------------------------------------------
macro(add_module NAME)
    set(B_PATH "/Users/sim/dev/borack_vision/src/modules/")
    add_subdirectory(${B_PATH}/${NAME} ${CMAKE_CURRENT_BINARY_DIR}/${NAME})
endmacro(add_module)

#--------------------------------------------------------------------------------
# Add Utilities
#--------------------------------------------------------------------------------
macro(add_util)
    add_module("../utilities")
endmacro(add_util)

