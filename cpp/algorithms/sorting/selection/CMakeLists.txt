###############################################################################
## Author: Shaun Reed                                                        ##
## Legal: All Content (c) 2021 Shaun Reed, all rights reserved               ##
## About: A basic CMakeLists configuration to practice selection sort        ##
##                                                                           ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0  ##
###############################################################################

cmake_minimum_required(VERSION 3.16)
project(SelectionSort LANGUAGES CXX)

add_executable(select-sort "select-sort.cpp")

add_library(lib-select "lib-select.cpp")
target_link_libraries(select-sort lib-select)
