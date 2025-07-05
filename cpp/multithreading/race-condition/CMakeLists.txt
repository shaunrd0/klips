################################################################################
## Author: Shaun Reed                                                         ##
## Legal: All Content (c) 2022 Shaun Reed, all rights reserved                ##
## About: An example and solution for race conditions in C++                  ##
##                                                                            ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0   ##
################################################################################

cmake_minimum_required(VERSION 3.16)

project(
    #[[NAME]]   RaceCondition
    VERSION     1.0
    DESCRIPTION "Example and solution for race conditions"
    LANGUAGES   CXX
)
message(STATUS "[Klips] Configuring example: ${PROJECT_NAME}")

add_executable(
    multithread-race-condition driver.cpp
)

target_link_libraries(multithread-race-condition pthread)
