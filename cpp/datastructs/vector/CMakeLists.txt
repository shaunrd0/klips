################################################################################
## Author: Shaun Reed                                                         ##
## Legal: All Content (c) 2022 Shaun Reed, all rights reserved                ##
## About: A basic CMakeLists configuration to test Vector implementation      ##
##                                                                            ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0   ##
################################################################################

cmake_minimum_required(VERSION 3.15)

project (
    #[[NAME]]   VectorDriver
    VERSION     1.0
    DESCRIPTION "A project for testing a basic Vector implementation"
    LANGUAGES   CXX
)

add_executable(
    data-vectors driver.cpp
    vector.cpp vector.h
)
