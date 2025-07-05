################################################################################
## Author: Shaun Reed                                                         ##
## Legal: All Content (c) 2022 Shaun Reed, all rights reserved                ##
## About: A basic CMakeLists configuration to practice insertion sort         ##
##                                                                            ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0   ##
################################################################################

cmake_minimum_required(VERSION 3.16)

project (
    #[[NAME]]   InsertionSort
    VERSION     1.0
    DESCRIPTION "A project for practicing insertion sort in C++"
    LANGUAGES   CXX
)
message(STATUS "[Klips] Configuring example: ${PROJECT_NAME}")

add_executable(
    algo-sort-insertion insertion-sort.cpp
    lib-insertion.cpp lib-insertion.hpp
)
