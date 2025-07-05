################################################################################
## Author: Shaun Reed                                                         ##
## Legal: All Content (c) 2022 Shaun Reed, all rights reserved                ##
## About: A basic CMakeLists configuration to practice quick sort             ##
##                                                                            ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0   ##
################################################################################

cmake_minimum_required(VERSION 3.16)

project (
    #[[NAME]]   QuickSort
    VERSION     1.0
    DESCRIPTION "A project for practicing quick sort in C++"
    LANGUAGES   CXX
)
message(STATUS "[Klips] Configuring example: ${PROJECT_NAME}")

add_executable(
    algo-sort-quick quick-sort.cpp
    lib-quick.cpp lib-quick.hpp
)
