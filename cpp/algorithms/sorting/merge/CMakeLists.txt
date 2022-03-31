################################################################################
## Author: Shaun Reed                                                         ##
## Legal: All Content (c) 2022 Shaun Reed, all rights reserved                ##
## About: A basic CMakeLists configuration to practice merge sort             ##
##                                                                            ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0   ##
################################################################################

cmake_minimum_required(VERSION 3.17)

project (
    #[[NAME]]   MergeSort
    VERSION     1.0
    DESCRIPTION "A project for practicing merge sort in C++"
    LANGUAGES   CXX
)
add_executable(
    algo-sort-merge merge-sort.cpp
    lib-merge.cpp lib-merge.h
)

