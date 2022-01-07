###############################################################################
## Author: Shaun Reed                                                        ##
## Legal: All Content (c) 2021 Shaun Reed, all rights reserved               ##
## About: A basic CMakeLists configuration to practice insertion sort        ##
##                                                                           ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0  ##
###############################################################################

cmake_minimum_required(VERSION 3.16)
project(InsertionSort LANGUAGES CXX)

add_executable(insertion-sort "insertion-sort.cpp")

add_library(lib-insertion "lib-insertion.cpp")
target_link_libraries(insertion-sort lib-insertion)
