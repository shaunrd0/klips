###############################################################################
## Author: Shaun Reed                                                        ##
## Legal: All Content (c) 2021 Shaun Reed, all rights reserved               ##
## About: A root project for practicing sorting algorithms in C++            ##
##                                                                           ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0  ##
##############################################################################
#
cmake_minimum_required(VERSION 3.15)

project (
    #[[NAME]]   Sorting-Algorithms
    VERSION     1.0
    DESCRIPTION "A project for practicing various sorting algorithms in C++"
    LANGUAGES   CXX
)

add_subdirectory(merge)
add_subdirectory(selection)
add_subdirectory(insertion)
add_subdirectory(bubble)
add_subdirectory(heap)
add_subdirectory(quick)
add_subdirectory(count)
