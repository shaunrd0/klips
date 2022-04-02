################################################################################
## Author: Shaun Reed                                                         ##
## Legal: All Content (c) 2022 Shaun Reed, all rights reserved                ##
## About: An example and solution for deadlocks in C++                        ##
##                                                                            ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0   ##
################################################################################

cmake_minimum_required(VERSION 3.16)

# std::scoped_lock requires C++17
set(CMAKE_CXX_STANDARD 17)
add_compile_options("-Wall")

project(
    #[[NAME]]   Deadlock
    VERSION     1.0
    DESCRIPTION "Example and solution for deadlocks in C++"
    LANGUAGES   CXX
)

add_executable(
    multithread-deadlock driver.cpp
)

target_link_libraries(multithread-deadlock pthread)
