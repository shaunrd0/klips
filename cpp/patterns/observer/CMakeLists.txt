###############################################################################
## Author: Shaun Reed                                                        ##
## Legal: All Content (c) 2021 Shaun Reed, all rights reserved               ##
## About: A project for practicing the observer C++ design pattern           ##
##                                                                           ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0  ##
##############################################################################
#
cmake_minimum_required(VERSION 3.15)
project(
    #[[NAME]]   Observer
    VERSION     1.0
    DESCRIPTION "An example of the state design pattern in C++"
    LANGUAGES   CXX
)
add_compile_options("-Wall")

add_library(observer "observer.cpp")
add_executable(observer-test "main.cpp")
target_link_libraries(observer-test observer)
