set(SOURCES
            ${SOURCES}
	${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/converter.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/customscene.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/customview.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/mainwindow.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/sourcescene.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/targetscene.cpp
	    PARENT_SCOPE
)
set(HEADERS
            ${HEADERS}
            ${CMAKE_CURRENT_SOURCE_DIR}/converter.hpp
            ${CMAKE_CURRENT_SOURCE_DIR}/customscene.hpp
            ${CMAKE_CURRENT_SOURCE_DIR}/customview.hpp
            ${CMAKE_CURRENT_SOURCE_DIR}/mainwindow.hpp
            ${CMAKE_CURRENT_SOURCE_DIR}/sourcescene.hpp
            ${CMAKE_CURRENT_SOURCE_DIR}/targetscene.hpp
	    PARENT_SCOPE
)

set(UI_FILES 
	${CMAKE_CURRENT_SOURCE_DIR}/mainwindow.ui
	    PARENT_SCOPE
)

set(QRC_FILES
#   main.qrc
)

set(QML_SOURCES

)

#include_directories(${CMAKE_CURRENT_SOURCE_DIR})
