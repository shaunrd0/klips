###############################################################################
## Author: Shaun Reed                                                        ##
## Legal: All Content (c) 2021 Shaun Reed, all rights reserved               ##
## About: A root project for practicing algorithms in C++                    ##
##                                                                           ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0  ##
##############################################################################
#
cmake_minimum_required(VERSION 3.15)

project (
    #[[NAME]]   Trees
    VERSION     1.0
    DESCRIPTION "A project for practicing algorithms using trees in C++"
    LANGUAGES   CXX
)

add_subdirectory(binary)
add_subdirectory(redblack)
