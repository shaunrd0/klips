###############################################################################
## Author: Shaun Reed                                                        ##
## Legal: All Content (c) 2021 Shaun Reed, all rights reserved               ##
## About: An example of a doubly linked list implementation                  ##
##                                                                           ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0  ##
##############################################################################
#
cmake_minimum_required(VERSION 3.15)

# Define the project name
project(DoubleList)
# Define source files
set(SRC driver.cpp doublelist.cpp)
# Build an executable
add_executable(DoubleListDriver ${SRC})
