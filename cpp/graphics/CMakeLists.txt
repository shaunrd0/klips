################################################################################
## Author: Shaun Reed                                                         ##
## Legal: All Content (c) 2021 Shaun Reed, all rights reserved                ##
## About: A root project for practicing C++                                   ##
##        This project can be built to debug and run all nested projects      ##
##        Or, any subdirectory with a project() statement can be selected     ##
##                                                                            ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0   ##
################################################################################

cmake_minimum_required(VERSION 3.15)

project(
    #[[NAME]]   Graphics
    VERSION     1.0
    DESCRIPTION "A root project for practicing graphics programming in C++"
    LANGUAGES   CXX
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(opengl-cmake)
add_subdirectory(sdl-cmake)
