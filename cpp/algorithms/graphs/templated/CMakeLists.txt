################################################################################
## Author: Shaun Reed                                                         ##
## Legal: All Content (c) 2022 Shaun Reed, all rights reserved                ##
## About: A basic CMakeLists to test templated graph implementation           ##
##                                                                            ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0   ##
################################################################################

cmake_minimum_required(VERSION 3.15)

project(
    #[[NAME]]   TemplatedGraph
    VERSION     1.0
    DESCRIPTION "Practice implementing and using templated graphs in C++"
    LANGUAGES CXX
)
message(STATUS "[Klips] Configuring example: ${PROJECT_NAME}")

add_executable(algo-graphs-templated graph.cpp)
