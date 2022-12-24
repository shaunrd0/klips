################################################################################
## Author: Shaun Reed                                                         ##
## Legal: All Content (c) 2022 Shaun Reed, all rights reserved                ##
## About: Example of making widget plugins for Qt Designer                    ##
##                                                                            ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0   ##
################################################################################

cmake_minimum_required(VERSION 3.15)

project(
    #[[NAME]]       DesignerPlugin
    VERSION         1.0
    DESCRIPTION     "Example of a widget plugin for Qt Designer"
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
if (WIN32)
    set(QT_PLUGIN_INSTALL_DIR
        "${QT_DIR}/Tools/QtCreator/bin/plugins/designer"
    )
else()
    set(QT_PLUGIN_INSTALL_DIR
        "${QT_DIR}/Tools/QtCreator/lib/Qt/plugins/designer"
    )
endif()
# This should be set to your Qt6 installation directory.
set(QT_INSTALL_DIR "${QT_DIR}/6.3.1/gcc_64/" CACHE PATH "Path to Qt6 install")
list(APPEND CMAKE_PREFIX_PATH "${QT_INSTALL_DIR}")

find_package(Qt6 REQUIRED COMPONENTS UiPlugin Core Gui Widgets)

# Creating the plugin

qt_add_library(widget-plugin)
target_sources(widget-plugin PRIVATE
    text-view.cpp text-view.h
    widget-plugin.cpp widget-plugin.h
)
set_target_properties(widget-plugin PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)
target_link_libraries(widget-plugin PUBLIC
    Qt::UiPlugin Qt::Core Qt::Gui Qt::Widgets
)

install(TARGETS widget-plugin
    RUNTIME DESTINATION "${QT_PLUGIN_INSTALL_DIR}"
    BUNDLE DESTINATION "${QT_PLUGIN_INSTALL_DIR}"
    LIBRARY DESTINATION "${QT_PLUGIN_INSTALL_DIR}"
)

# Application that will use the widget plugin

qt_add_executable(widget-app
    widget-app.cpp widget-app.h widget-app.ui
    main.cpp
)
target_link_libraries(widget-app PRIVATE
    Qt::Widgets widget-plugin
)
