###############################################################################
## Author: Shaun Reed                                                        ##
## Legal: All Content (c) 2021 Shaun Reed, all rights reserved               ##
## About: A basic CMakeLists configuration to test RBT implementation        ##
##                                                                           ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0  ##
##############################################################################
#
cmake_minimum_required(VERSION 3.15)

project (
    #[[NAME]]   RedBlackTree
    VERSION     1.0
    DESCRIPTION "A project for testing red-black tree algorithms"
    LANGUAGES   CXX
)

add_library(lib-redblack "redblack.cpp")

add_executable(test-redblack "driver.cpp")
target_link_libraries(test-redblack lib-redblack)
