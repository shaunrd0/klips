###############################################################################
## Author: Shaun Reed                                                        ##
## Legal: All Content (c) 2021 Shaun Reed, all rights reserved               ##
## About: A project for practicing the abstract factory C++ design pattern   ##
##                                                                           ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0  ##
##############################################################################
#
cmake_minimum_required(VERSION 3.15)
project(
    #[[NAME]]   AbstractFactory
    VERSION     1.0
    DESCRIPTION "An example of the abstract factory design pattern in C++"
    LANGUAGES   CXX
)
add_compile_options("-Wall")

add_executable(
    patterns-abstract-factory main.cpp
    parts.cpp parts.hpp
    abstract-factory.cpp abstract-factory.hpp
)
