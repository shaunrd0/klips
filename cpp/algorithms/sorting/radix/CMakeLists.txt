################################################################################
## Author: Shaun Reed                                                         ##
## Legal: All Content (c) 2022 Shaun Reed, all rights reserved                ##
## About: A basic CMakeLists configuration to practice radix sort             ##
##                                                                            ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0   ##
################################################################################

cmake_minimum_required(VERSION 3.16)

project (
    #[[NAME]]   RadixSort
    VERSION     1.0
    DESCRIPTION "A project for practicing radix sort in C++"
    LANGUAGES   CXX
)

add_executable(
    algo-sort-radix radix-sort.cpp
    lib-counting.cpp lib-counting.hpp
    lib-radix.cpp lib-radix.hpp
)
