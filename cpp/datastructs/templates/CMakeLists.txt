################################################################################
## Author: Shaun Reed                                                         ##
## Legal: All Content (c) 2022 Shaun Reed, all rights reserved                ##
## About: A root project for practicing templated data structures in C++      ##
##                                                                            ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0   ##
################################################################################

cmake_minimum_required(VERSION 3.15)

project (
    #[[NAME]]   TemplatedStructures
    VERSION     1.0
    DESCRIPTION "A project for practicing templated data structures in C++"
    LANGUAGES   CXX
)
message(STATUS "[Klips] Configuring example: ${PROJECT_NAME}")

add_subdirectory(doublelist)
add_subdirectory(queuelist)
add_subdirectory(stacklist)
add_subdirectory(vector)
