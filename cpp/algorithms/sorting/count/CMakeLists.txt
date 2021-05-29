###############################################################################
## Author: Shaun Reed                                                        ##
## Legal: All Content (c) 2021 Shaun Reed, all rights reserved               ##
## About: A basic CMakeLists configuration to practice counting sort         ##
##                                                                           ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0  ##
###############################################################################

cmake_minimum_required(VERSION 3.16)
project(CountingSort LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(counting-sort "counting-sort.cpp")

add_library(lib-counting "lib-counting.cpp")
target_link_libraries(counting-sort lib-counting)
