###############################################################################
## Author: Shaun Reed                                                        ##
## Legal: All Content (c) 2021 Shaun Reed, all rights reserved               ##
## About: A basic CMakeLists configuration to practice radix sort            ##
##                                                                           ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0  ##
###############################################################################

cmake_minimum_required(VERSION 3.16)
project(RadixSort LANGUAGES CXX)

add_executable(radix-sort "radix-sort.cpp")

add_library(lib-radix-counting "lib-counting.cpp")
add_library(lib-radix "lib-radix.cpp")

target_link_libraries(radix-sort lib-radix lib-radix-counting)
