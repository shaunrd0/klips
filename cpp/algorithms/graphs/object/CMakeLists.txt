################################################################################
## Author: Shaun Reed                                                         ##
## Legal: All Content (c) 2022 Shaun Reed, all rights reserved                ##
## About: A root project for practicing graph algorithms in C++               ##
##                                                                            ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0   ##
################################################################################

cmake_minimum_required(VERSION 3.15)

project(
    #[[NAME]]   ObjectGraph
    VERSION     1.0
    DESCRIPTION "Practice implementing and using object graphs in C++"
    LANGUAGES CXX
)
message(STATUS "[Klips] Configuring example: ${PROJECT_NAME}")

add_executable(
    algo-graphs-object graph.cpp
    lib-graph.cpp lib-graph.hpp
)
