################################################################################
## Author: Shaun Reed                                                         ##
## Legal: All Content (c) 2022 Shaun Reed, all rights reserved                ##
## About: A project for practicing the state C++ design pattern               ##
##                                                                            ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0   ##
################################################################################

cmake_minimum_required(VERSION 3.15)

project(
    #[[NAME]]   State
    VERSION     1.0
    DESCRIPTION "An example of the state design pattern in C++"
    LANGUAGES   CXX
)
add_compile_options("-Wall")

add_executable(
    patterns-state main.cpp
    state.cpp state.hpp
)
