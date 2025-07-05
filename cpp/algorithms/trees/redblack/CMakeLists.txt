################################################################################
## Author: Shaun Reed                                                         ##
## Legal: All Content (c) 2022 Shaun Reed, all rights reserved                ##
## About: A basic CMakeLists configuration to test RBT implementation         ##
##                                                                            ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0   ##
################################################################################

cmake_minimum_required(VERSION 3.15)

project (
    #[[NAME]]   RedBlackTree
    VERSION     1.0
    DESCRIPTION "A project for testing red-black tree algorithms"
    LANGUAGES   CXX
)
message(STATUS "[Klips] Configuring example: ${PROJECT_NAME}")

add_executable(
    algo-trees-redblack driver.cpp
    redblack.cpp redblack.h
)
