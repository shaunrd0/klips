################################################################################
## Author: Shaun Reed                                                         ##
## Legal: All Content (c) 2022 Shaun Reed, all rights reserved                ##
## About: A basic CMakeLists configuration to test RBT implementation         ##
##                                                                            ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0   ##
################################################################################

cmake_minimum_required(VERSION 3.15)

project(
    #[[NAME]]   WeightedGraph
    VERSION     1.0
    DESCRIPTION "Practice implementing and using weighted graphs in C++"
    LANGUAGES CXX
)

add_executable(
    algo-graphs-weighted graph.cpp
    lib-graph.cpp lib-graph.hpp
)
