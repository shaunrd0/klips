###############################################################################
## Author: Shaun Reed                                                        ##
## Legal: All Content (c) 2022 Shaun Reed, all rights reserved               ##
## About: A basic CMakeLists configuration to practice bucket sort           ##
##                                                                           ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0  ##
###############################################################################

cmake_minimum_required(VERSION 3.16)
project(BucketSort LANGUAGES CXX)

add_executable(
    algo-sort-bucket bucket-sort.cpp
    lib-bucket.cpp lib-bucket.hpp
)
