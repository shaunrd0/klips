################################################################################
## Author: Shaun Reed                                                         ##
## Legal: All Content (c) 2021 Shaun Reed, all rights reserved                ##
## About: A root project for practicing graph algorithms in C++               ##
##                                                                            ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0   ##
################################################################################
#

cmake_minimum_required(VERSION 3.15)

project(
    #[[NAME]]   ObjectGraph
    VERSION     1.0
    DESCRIPTION "Practice implementing and using object graphs in C++"
    LANGUAGES CXX
)

add_library(lib-graph-object "lib-graph.cpp")

add_executable(graph-test-object "graph.cpp")
target_link_libraries(graph-test-object lib-graph-object)
