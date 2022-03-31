################################################################################
## Author: Shaun Reed                                                         ##
## Legal: All Content (c) 2022 Shaun Reed, all rights reserved                ##
## About: A project for practicing C++ design patterns                        ##
##                                                                            ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0   ##
################################################################################

cmake_minimum_required(VERSION 3.15)

project(
    #[[NAME]]   DesignPatterns
    VERSION     1.0
    DESCRIPTION "A project for practicing various design patterns in C++"
    LANGUAGES   CXX
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(singleton)
add_subdirectory(adapter)
add_subdirectory(bridge)
add_subdirectory(factory)
add_subdirectory(prototype)
add_subdirectory(abstract-factory)
add_subdirectory(state)
add_subdirectory(observer)
add_subdirectory(visitor)
