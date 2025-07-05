################################################################################
## Author: Shaun Reed                                                         ##
## Legal: All Content (c) 2022 Shaun Reed, all rights reserved                ##
## About: Example of making a collection of widget plugins for Qt Designer    ##
##                                                                            ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0   ##
################################################################################

cmake_minimum_required(VERSION 3.15)

project(
    #[[NAME]]       DesignerPluginCollection
    VERSION         1.0
    DESCRIPTION     "Example of a widget plugin collection for Qt Designer"
    LANGUAGES       CXX
)
message(STATUS "[Klips] Configuring example: ${PROJECT_NAME}")
# Lowercase string to use as a slug for executable names for identification.
string(TOLOWER ${PROJECT_NAME} PROJECT_NAME_LOWER)

include(GenerateExportHeader)

add_compile_options(-Wall)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_SHARED_MODULE_PREFIX "")

set(QT_DIR "$ENV{HOME}/Code/Clones/Qt/" CACHE PATH "Path to Qt6")
# Qt Designer will look in different locations if WIN / Unix.
# These paths are for using Qt Designer integrated within Qt Creator.
# Standalone Qt Designer may use different paths.
if (WIN32)
    set(QT_PLUGIN_INSTALL_DIR
        "${QT_DIR}/Tools/QtCreator/bin/plugins/designer"
    )
    # This path may be different on windows. I have not tested this.
    set(QT_PLUGIN_LIBRARY_DIR
        "${QT_DIR}/Tools/QtCreator/lib/Qt/lib"
    )
else()
    set(QT_PLUGIN_INSTALL_DIR
        "${QT_DIR}/Tools/QtCreator/lib/Qt/plugins/designer"
    )
    set(QT_PLUGIN_LIBRARY_DIR
        "${QT_DIR}/Tools/QtCreator/lib/Qt/lib"
    )
endif()
# This should be set to your Qt6 installation directory.
set(QT_INSTALL_DIR "${QT_DIR}/6.3.1/gcc_64/" CACHE PATH "Path to Qt6 install")
list(APPEND CMAKE_PREFIX_PATH "${QT_INSTALL_DIR}")

find_package(Qt6 COMPONENTS UiPlugin Core Gui Widgets)
if (NOT Qt6_FOUND)
    message(
        FATAL_ERROR
        "[Klips] Error: CMake was unable to find Qt6 libraries.\n"
        "The example will not be built until the build is configured with these packages installed.\n"
        "On Ubuntu 24.04 Qt6 can be installed using apt:\n"
        "  sudo apt-get install qt6-base-dev qt6-tools-dev\n"
    )
endif()

# Creating a library with two plugins for the collection.
set(WIDGET_PLUGIN_LIBRARY widget-plugin-library_${PROJECT_NAME_LOWER})
qt_add_library(${WIDGET_PLUGIN_LIBRARY}
    textview.cpp textview.h
    widgetplugin.cpp widgetplugin.h
)
target_sources(${WIDGET_PLUGIN_LIBRARY} PRIVATE
    textview.cpp textview.h
    treeview.cpp treeview.h
    widgetplugin.cpp widgetplugin.h
)
set_target_properties(${WIDGET_PLUGIN_LIBRARY} PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)
target_link_libraries(${WIDGET_PLUGIN_LIBRARY}
    PUBLIC Qt::UiPlugin Qt::Core Qt::Gui Qt::Widgets
)

install(TARGETS ${WIDGET_PLUGIN_LIBRARY}
    RUNTIME DESTINATION "${QT_PLUGIN_LIBRARY_DIR}"
    BUNDLE DESTINATION "${QT_PLUGIN_LIBRARY_DIR}"
    LIBRARY DESTINATION "${QT_PLUGIN_LIBRARY_DIR}"
)

generate_export_header(${WIDGET_PLUGIN_LIBRARY}
    BASE_NAME widget_plugin_library
    EXPORT_FILE_NAME "${CMAKE_CURRENT_BINARY_DIR}/widget-plugin-library_export.h"
)

# Creating the collection
set(WIDGET_PLUGIN_COLLECTION widget-plugin-collection_${PROJECT_NAME_LOWER})
qt_add_library(${WIDGET_PLUGIN_COLLECTION}
    widgetplugincollection.cpp widgetplugincollection.h
)
target_link_libraries(${WIDGET_PLUGIN_COLLECTION}
    Qt6::Widgets Qt6::UiPlugin ${WIDGET_PLUGIN_LIBRARY}
)
install(TARGETS ${WIDGET_PLUGIN_COLLECTION}
    RUNTIME DESTINATION "${QT_PLUGIN_INSTALL_DIR}"
    BUNDLE DESTINATION "${QT_PLUGIN_INSTALL_DIR}"
    LIBRARY DESTINATION "${QT_PLUGIN_INSTALL_DIR}"
)

# Application that will use the widget plugin

set(APP_DIR ${CMAKE_CURRENT_SOURCE_DIR})
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/app-dir.h.in"
    "${CMAKE_CURRENT_SOURCE_DIR}/app-dir.h"
    @ONLY
)

set(WIDGET_APP widget-app_${PROJECT_NAME_LOWER})
qt_add_executable(${WIDGET_APP}
    widgetapp.cpp widgetapp.h widgetapp.ui
    main.cpp
)
target_link_libraries(${WIDGET_APP}
    PRIVATE Qt::Widgets ${WIDGET_PLUGIN_LIBRARY}
)
