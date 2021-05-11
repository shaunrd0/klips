###############################################################################
## Author: Shaun Reed                                                        ##
## Legal: All Content (c) 2021 Shaun Reed, all rights reserved               ##
## About: A project for practicing the singleton C++ design pattern          ##
##                                                                           ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0  ##
##############################################################################
#
cmake_minimum_required(VERSION 3.15)

project(
    #[[NAME]]   Singleton
    VERSION     1.0
    DESCRIPTION "An example of the singleton design pattern in C++"
    LANGUAGES   CXX
)

add_library(singleton "singleton.cpp")
add_executable(singleton-test "main.cpp")
target_link_libraries(singleton-test singleton)
