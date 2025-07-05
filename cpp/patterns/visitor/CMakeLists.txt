################################################################################
## Author: Shaun Reed                                                         ##
## Legal: All Content (c) 2022 Shaun Reed, all rights reserved                ##
## About: A project for practicing the visitor C++ design pattern             ##
##                                                                            ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0   ##
################################################################################

cmake_minimum_required(VERSION 3.15)

project(
    #[[NAME]]   Visitor
    VERSION     1.0
    DESCRIPTION "An example of the visitor design pattern in C++"
    LANGUAGES   CXX
)
message(STATUS "[Klips] Configuring example: ${PROJECT_NAME}")
add_compile_options("-Wall")

add_executable(
    patterns-visitor main.cpp
    visitor.cpp visitor.hpp
)
