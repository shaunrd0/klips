################################################################################
## Author: Shaun Reed                                                         ##
## Legal: All Content (c) 2022 Shaun Reed, all rights reserved                ##
## About: An example of a circular doubly linked list implementation          ##
##                                                                            ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0   ##
################################################################################

cmake_minimum_required(VERSION 3.15)

project (
    #[[NAME]]   CircleDoubleList
    VERSION     1.0
    DESCRIPTION "Project for testing circular doubly linked list implementation"
    LANGUAGES   CXX
)
message(STATUS "[Klips] Configuring example: ${PROJECT_NAME}")

add_executable(
    data-circular-doubly-linked-list driver.cpp
    circledoublelist.cpp circledoublelist.h
)
