################################################################################
## Author: Shaun Reed                                                         ##
## Legal: All Content (c) 2022 Shaun Reed, all rights reserved                ##
## About: An example of a circular singly linked list implementation          ##
##                                                                            ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0   ##
################################################################################

cmake_minimum_required(VERSION 3.15)

project (
    #[[NAME]]   CircleSingleList
    VERSION     1.0
    DESCRIPTION "Project for testing circular singly linked list implementation"
    LANGUAGES   CXX
)

add_executable(
    data-circular-singly-linked-list driver.cpp
    circlesinglelist.cpp circlesinglelist.h
)
