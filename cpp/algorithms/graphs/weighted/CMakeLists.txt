################################################################################
## Author: Shaun Reed                                                         ##
## Legal: All Content (c) 2021 Shaun Reed, all rights reserved                ##
## About: A basic CMakeLists configuration to test RBT implementation         ##
##                                                                            ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0   ##
################################################################################
#

cmake_minimum_required(VERSION 3.15)

project(
    #[[NAME]]   WeightedGraph
    VERSION     1.0
    DESCRIPTION "Practice implementing and using weighted graphs in C++"
    LANGUAGES CXX
)

add_library(lib-graph-weighted "lib-graph.cpp")

add_executable(graph-test-weighted "graph.cpp")
target_link_libraries(graph-test-weighted lib-graph-weighted)
