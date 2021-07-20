###############################################################################
## Author: Shaun Reed                                                        ##
## Legal: All Content (c) 2021 Shaun Reed, all rights reserved               ##
## About: A root project for practicing cryptography in C++                  ##
##                                                                           ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0  ##
##############################################################################
#
cmake_minimum_required(VERSION 3.15)

project (
    #[[NAME]]   Cryptography
    VERSION     1.0
    DESCRIPTION "A project for practicing cryptography in C++"
    LANGUAGES   CXX
)

add_subdirectory(columnar-transposition)
