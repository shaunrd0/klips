################################################################################
## Author: Shaun Reed                                                         ##
## Legal: All Content (c) 2022 Shaun Reed, all rights reserved                ##
## About: An example of a templated doubly linked list implementation         ##
##                                                                            ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0   ##
################################################################################

cmake_minimum_required(VERSION 3.15)

project (
    #[[NAME]]   TemplatedDoubleList
    VERSION     1.0
    DESCRIPTION "A project for practicing templated doubly linked list implementations"
    LANGUAGES   CXX
)

add_executable(data-templates-doubly-linked-list driver.cpp)
