###############################################################################
## Author: Shaun Reed                                                        ##
## Legal: All Content (c) 2021 Shaun Reed, all rights reserved               ##
## About: A basic CMakeLists configuration to test BST implementation        ##
##                                                                           ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0  ##
##############################################################################
#
cmake_minimum_required(VERSION 3.15)

project (
    #[[NAME]]   BinaryTree
    VERSION     1.0
    DESCRIPTION "A project for testing BST algorithms"
    LANGUAGES   CXX
)

add_library(lib-bst "bst.cpp")

add_executable(test-bst "driver.cpp")
target_link_libraries(test-bst lib-bst)
