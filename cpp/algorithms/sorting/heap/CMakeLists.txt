###############################################################################
## Author: Shaun Reed                                                        ##
## Legal: All Content (c) 2021 Shaun Reed, all rights reserved               ##
## About: A basic CMakeLists configuration to practice heap sort             ##
##                                                                           ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0  ##
###############################################################################

cmake_minimum_required(VERSION 3.16)
project(HeapSort LANGUAGES CXX)

add_executable(
    algo-sort-heap heap-sort.cpp
    lib-heap.cpp lib-heap.hpp
)

