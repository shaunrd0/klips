################################################################################
## Author: Shaun Reed                                                         ##
## Legal: All Content (c) 2022 Shaun Reed, all rights reserved                ##
## About: A basic CMakeLists configuration to practice selection sort         ##
##                                                                            ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0   ##
################################################################################

cmake_minimum_required(VERSION 3.16)

project (
    #[[NAME]]   SelectionSort
    VERSION     1.0
    DESCRIPTION "A project for practicing selection sort in C++"
    LANGUAGES   CXX
)

add_executable(
    algo-sort-select select-sort.cpp
    lib-select.cpp lib-select.h
)
