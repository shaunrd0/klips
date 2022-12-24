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

find_package(Qt6 REQUIRED COMPONENTS UiPlugin Core Gui Widgets)

# Creating a library with two plugins for the collection.
qt_add_library(widget-plugin-library
    textview.cpp textview.h
    widgetplugin.cpp widgetplugin.h
)
target_sources(widget-plugin-library PRIVATE
    textview.cpp textview.h
    treeview.cpp treeview.h
    widgetplugin.cpp widgetplugin.h
)
set_target_properties(widget-plugin-library PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)
target_link_libraries(widget-plugin-library
    PUBLIC Qt::UiPlugin Qt::Core Qt::Gui Qt::Widgets
)

install(TARGETS widget-plugin-library
    RUNTIME DESTINATION "${QT_PLUGIN_LIBRARY_DIR}"
    BUNDLE DESTINATION "${QT_PLUGIN_LIBRARY_DIR}"
    LIBRARY DESTINATION "${QT_PLUGIN_LIBRARY_DIR}"
)

generate_export_header(widget-plugin-library)

# Creating the collection

qt_add_library(widget-plugin-collection
    widgetplugincollection.cpp widgetplugincollection.h
)
target_link_libraries(widget-plugin-collection
    Qt6::Widgets Qt6::UiPlugin widget-plugin-library
)
install(TARGETS widget-plugin-collection
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

qt_add_executable(widget-app
    widgetapp.cpp widgetapp.h widgetapp.ui
    main.cpp
)
target_link_libraries(widget-app
    PRIVATE Qt::Widgets widget-plugin-library
)
