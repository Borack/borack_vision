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

