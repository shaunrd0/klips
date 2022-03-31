################################################################################
## Author: Shaun Reed                                                         ##
## Legal: All Content (c) 2022 Shaun Reed, all rights reserved                ##
## About: A project for practicing the bridge C++ design pattern              ##
##                                                                            ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0   ##
################################################################################

cmake_minimum_required(VERSION 3.15)

project(
    #[[NAME]]   Bridge
    VERSION     1.0
    DESCRIPTION "An example of the bridge design pattern in C++"
    LANGUAGES   CXX
)
add_compile_options("-Wall")

add_executable(
    patterns-bridge main.cpp
    abstraction.cpp abstraction.hpp
    implementation.cpp implementation.hpp
)
