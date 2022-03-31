################################################################################
## Author: Shaun Reed                                                         ##
## Legal: All Content (c) 2022 Shaun Reed, all rights reserved                ##
## About: An example of a doubly linked list implementation                   ##
##                                                                            ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0   ##
################################################################################

cmake_minimum_required(VERSION 3.15)

project (
    #[[NAME]]   DoubleList
    VERSION     1.0
    DESCRIPTION "A project for testing a doubly linked list implementation"
    LANGUAGES   CXX
)

add_executable(
    data-doubly-linked-list driver.cpp
    doublelist.cpp doublelist.h
)
