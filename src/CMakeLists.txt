cmake_minimum_required(VERSION 2.8)

#--------------------------------------------------------------------------------
# Project files
#--------------------------------------------------------------------------------

set(PROJECT_NAME borack_vision_2)
project(${PROJECT_NAME})

# Setup paths
include(${CMAKE_CURRENT_SOURCE_DIR}/../cmake/Macros.cmake)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../cmake/)

#--------------------------------------------------------------------------------
# Core - always required 
#--------------------------------------------------------------------------------
#add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/utilities)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}) #FIXME: should be done in the core/CMakeLists.txt
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/core)


#--------------------------------------------------------------------------------
# Modules
#--------------------------------------------------------------------------------
option(MODULE_MVC "Build with the 'Coordinates for instant image cloning' module" ON)
if(MODULE_MVC)
#        include_directories(${CMAKE_CURRENT_SOURCE_DIR}/modules/mvc) #FIXME: should be done in the core/CMakeLists.txt
#        include_directories(${CMAKE_CURRENT_SOURCE_DIR}) #FIXME: should be done in the core/CMakeLists.txt
#        add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/modules/mvc)
endif(MODULE_MVC)

option(MODULE_PHOTOMONTAGE "Build with the 'Interactive Digital Photomontage' module" ON)
if(MODULE_PHOTOMONTAGE)
#        add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/modules/photomontage)
#        include_directories(${CMAKE_CURRENT_SOURCE_DIR}/modules/photomontage) #FIXME: should be done in the core/CMakeLists.txt

#        add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/3rd_party/gco-v3.0)
#        include_directories(${CMAKE_CURRENT_SOURCE_DIR}/3rd_party/gco-v3.0) #FIXME: should be done in the core/CMakeLists.txt
endif(MODULE_PHOTOMONTAGE)




find_package(OpenCV REQUIRED)


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

#--------------------------------------------------------------------------------
# Eigen
#--------------------------------------------------------------------------------
find_package(Eigen3 REQUIRED)
include_directories( "${EIGEN3_INCLUDE_DIR}" )

#--------------------------------------------------------------------------------
# CGAL
#--------------------------------------------------------------------------------
find_package(CGAL REQUIRED)
include( ${CGAL_USE_FILE} )



#--------------------------------------------------------------------------------
# Executable
#--------------------------------------------------------------------------------
#add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} ${QRC_OUT} ${UI_HEADERS})
#target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS} ${CGAL_LIBRARIES} ${CGAL_3RD_PARTY_LIBRARIES})

#qt5_use_modules(${PROJECT_NAME} Widgets OpenGL Core)
