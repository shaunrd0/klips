###############################################################################
## Author: Shaun Reed                                                        ##
## Legal: All Content (c) 2021 Shaun Reed, all rights reserved               ##
## About: A basic CMakeLists configuration to practice quick sort            ##
##                                                                           ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0  ##
###############################################################################

cmake_minimum_required(VERSION 3.16)
project(QuickSort LANGUAGES CXX)

add_executable(quick-sort "quick-sort.cpp")

add_library(lib-quick "lib-quick.cpp")
target_link_libraries(quick-sort lib-quick)
