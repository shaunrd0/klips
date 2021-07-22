################################################################################
## Author: Shaun Reed                                                         ##
## Legal: All Content (c) 2021 Shaun Reed, all rights reserved                ##
## About: A basic CMakeLists to test templated graph implementation           ##
##                                                                            ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0   ##
################################################################################
#

cmake_minimum_required(VERSION 3.15)

project(
    #[[NAME]]   TemplatedGraph
    VERSION     1.0
    DESCRIPTION "Practice implementing and using templated graphs in C++"
    LANGUAGES CXX
)

#add_library(lib-graph-templated "lib-graph.cpp")

add_executable(graph-test-templated "graph.cpp")
#target_link_libraries(graph-test-templated lib-graph-templated)
