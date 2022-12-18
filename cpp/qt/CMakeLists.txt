################################################################################
## Author: Shaun Reed                                                         ##
## Legal: All Content (c) 2022 Shaun Reed, all rights reserved                ##
## About: A root project for practicing Qt 6 projects in C++                  ##
##                                                                            ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0   ##
################################################################################

cmake_minimum_required(VERSION 3.15)

project(
    #[[NAME]]   Klips
    VERSION     1.0
    DESCRIPTION "A root project for several small cpp practice projects"
    LANGUAGES   CXX
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
add_compile_options("-Wall")

add_subdirectory(designer)
add_subdirectory(slots)
