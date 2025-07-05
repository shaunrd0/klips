################################################################################
## Author: Shaun Reed                                                         ##
## Legal: All Content (c) 2025 Shaun Reed, all rights reserved                ##
## About: Practice project for using signals and slots in Qt                  ##
##                                                                            ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0   ##
################################################################################

cmake_minimum_required(VERSION 3.15)

project(
    #[[NAME]]       Slots
    VERSION         1.0
    DESCRIPTION     "Practice using signals and slots in Qt 6"
    LANGUAGES       CXX
)
message(STATUS "[Klips] Configuring example: ${PROJECT_NAME}")

add_compile_options(-Wall)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(QT_DIR "$ENV{HOME}/Code/Clones/Qt/6.3.1/gcc_64/" CACHE PATH "Path to Qt6")

list(APPEND CMAKE_PREFIX_PATH "${QT_DIR}")

find_package(Qt6 COMPONENTS Core Gui Widgets)
if (NOT Qt6_FOUND)
  message(
      FATAL_ERROR
      "[Klips] Error: CMake was unable to find Qt6 libraries.\n"
      "The example will not be built until the build is configured with these packages installed.\n"
      "On Ubuntu 24.04 Qt6 can be installed using apt:\n"
      "  sudo apt-get install qt6-base-dev qt6-tools-dev\n"
  )
endif()

qt_add_executable(slots
    text-view.cpp text-view.h
    slots-app.cpp slots-app.h
    main.cpp
)

set_target_properties(slots PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_link_libraries(slots PUBLIC Qt::Core Qt::Gui Qt::Widgets)

install(TARGETS slots
    RUNTIME DESTINATION "install/slots"
    BUNDLE DESTINATION "install/slots"
    LIBRARY DESTINATION "install/slots"
)
