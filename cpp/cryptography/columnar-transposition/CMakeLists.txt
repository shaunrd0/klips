################################################################################
## Author: Shaun Reed                                                         ##
## Legal: All Content (c) 2021 Shaun Reed, all rights reserved                ##
## About: A root project for practicing columnar transposition cipher in C++  ##
##                                                                            ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0   ##
################################################################################

cmake_minimum_required(VERSION 3.15)

project(
    #[[NAME]]   ColumnarTransposition
    VERSION     1.0
    DESCRIPTION "Practice implementing columnar transposition in C++"
    LANGUAGES CXX
)
message(STATUS "[Klips] Configuring example: ${PROJECT_NAME}")

add_executable(
    crypto-columnar-transposition driver.cpp
    lib-cipher.cpp lib-cipher.hpp
)
