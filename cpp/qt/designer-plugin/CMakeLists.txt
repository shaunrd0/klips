################################################################################
## Author: Shaun Reed                                                         ##
## Legal: All Content (c) 2025 Shaun Reed, all rights reserved                ##
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

# Creating the plugin
set(WIDGET_PLUGIN widget-plugin_${PROJECT_NAME_LOWER})
qt_add_library(${WIDGET_PLUGIN})
target_sources(${WIDGET_PLUGIN} PRIVATE
    text-view.cpp text-view.h
    widget-plugin.cpp widget-plugin.h
)
set_target_properties(${WIDGET_PLUGIN} PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)
target_link_libraries(${WIDGET_PLUGIN} PUBLIC
    Qt::UiPlugin Qt::Core Qt::Gui Qt::Widgets
)

install(TARGETS ${WIDGET_PLUGIN}
    RUNTIME DESTINATION "${QT_PLUGIN_INSTALL_DIR}"
    BUNDLE DESTINATION "${QT_PLUGIN_INSTALL_DIR}"
    LIBRARY DESTINATION "${QT_PLUGIN_INSTALL_DIR}"
)

# Application that will use the widget plugin
set(WIDGET_APP widget-app_${PROJECT_NAME_LOWER})
qt_add_executable(${WIDGET_APP}
    widget-app.cpp widget-app.h widget-app.ui
    main.cpp
)
target_link_libraries(${WIDGET_APP} PRIVATE
    Qt::Widgets ${WIDGET_PLUGIN}
)
