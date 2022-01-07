###############################################################################
## Author: Shaun Reed                                                        ##
## Legal: All Content (c) 2020 Shaun Reed, all rights reserved               ##
## About: A basic CMakeLists configuration to practice merge sort            ##
##                                                                           ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0  ##
###############################################################################

cmake_minimum_required(VERSION 3.17)
project(MergeSort LANGUAGES CXX)

add_executable(merge-sort "merge-sort.cpp")

add_library(lib-merge "lib-merge.cpp")
target_link_libraries(merge-sort lib-merge)
