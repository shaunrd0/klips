################################################################################
## Author: Shaun Reed                                                         ##
## Legal: All Content (c) 2022 Shaun Reed, all rights reserved                ##
## About: Practice project for testing with catch2 framework                  ##
##                                                                            ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0   ##
################################################################################

cmake_minimum_required(VERSION 3.15)

project(
    #[[NAME]]       Catch2
    VERSION         1.0
    DESCRIPTION     "Practice project for learning Catch2"
    LANGUAGES       CXX
)

add_compile_options(-Wall)
add_definitions("-std=c++17")

add_library(klips SHARED klips.cpp)
target_include_directories(klips PRIVATE ${CMAKE_SOURCE_DIR}/include)
