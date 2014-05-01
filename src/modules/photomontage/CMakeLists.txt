setup_module()

set(SOURCES
            photomontage.cpp
            pm_sourcescene.cpp
            pm_targetscene.cpp
            pm_window.cpp
            pm_sourcewidget.cpp
)

set(HEADERS
            photomontage.hpp
            pm_sourcescene.hpp
            pm_targetscene.hpp
            pm_window.hpp
            pm_modes.hpp
)

set(UI_FILES
            pm_window.ui
            pm_sourcewidget.ui
)

message(STATUS "add_library ${MODULE}")
find_qt5()
add_library(${MODULE} ${SOURCES} ${HEADERS} ${UI_HEADERS})

add_core(ui)
add_core(utilities)

add_3rd(gco-v3.0)
find_opencv()
find_eigen()
