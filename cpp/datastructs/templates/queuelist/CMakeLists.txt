################################################################################
## Author: Shaun Reed                                                         ##
## Legal: All Content (c) 2022 Shaun Reed, all rights reserved                ##
## About: An example of a templated queue implementation                      ##
##                                                                            ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0   ##
################################################################################

cmake_minimum_required(VERSION 3.15)

project (
    #[[NAME]]   TemplatedQueue
    VERSION     1.0
    DESCRIPTION "A project for practicing templated queue implementations"
    LANGUAGES   CXX
)

add_executable(data-templates-queue driver.cpp)
