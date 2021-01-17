###############################################################################
## Author: Shaun Reed                                                        ##
## Legal: All Content (c) 2020 Shaun Reed, all rights reserved               ##
## About: A basic CMakeLists configuration to practice selection sort        ##
##                                                                           ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0  ##
###############################################################################

cmake_minimum_required(VERSION 3.17)
project(SelectionSort LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(select-sort "select-sort.cpp")

add_library(lib-select "lib-select.cpp")
target_link_libraries(select-sort lib-select)
