###############################################################################
## Author: Shaun Reed                                                        ##
## Legal: All Content (c) 2021 Shaun Reed, all rights reserved               ##
## About: A root project for practicing C++ data structure implementations   ##
##                                                                           ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0  ##
##############################################################################
#
cmake_minimum_required(VERSION 3.15)

project (
    #[[NAME]]   DataStructures
    VERSION     1.0
    DESCRIPTION "A project for practicing various data structures in C++"
    LANGUAGES   CXX
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(binarysearchtree)
add_subdirectory(circledoublelist)
add_subdirectory(circlesinglelist)
add_subdirectory(doublelist)
add_subdirectory(maxheap)
add_subdirectory(queuelist)
add_subdirectory(singlelist)
add_subdirectory(stacklist)
add_subdirectory(vector)

# Add subdirectory for examples of templated data stuctures
add_subdirectory(templates)
