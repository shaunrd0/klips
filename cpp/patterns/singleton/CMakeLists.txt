################################################################################
## Author: Shaun Reed                                                         ##
## Legal: All Content (c) 2022 Shaun Reed, all rights reserved                ##
## About: A project for practicing the singleton C++ design pattern           ##
##                                                                            ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0   ##
################################################################################

cmake_minimum_required(VERSION 3.15)

project(
    #[[NAME]]   Singleton
    VERSION     1.0
    DESCRIPTION "An example of the singleton design pattern in C++"
    LANGUAGES   CXX
)
message(STATUS "[Klips] Configuring example: ${PROJECT_NAME}")

add_executable(
    patterns-singleton main.cpp
    singleton-pointer.cpp singleton-pointer.hpp
    singleton.cpp singleton.hpp
)
