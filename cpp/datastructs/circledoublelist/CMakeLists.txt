###############################################################################
## Author: Shaun Reed                                                        ##
## Legal: All Content (c) 2020 Shaun Reed, all rights reserved               ##
## About: An example of a circular doubly linked list implementation         ##
##                                                                           ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0  ##
##############################################################################
## CMakeLists.txt
#

CMAKE_MINIMUM_REQUIRED(VERSION 3.2)

# Define the project name
project(CircleDouble)
# Define source files
set(SRC driver.cpp circledoublelist.cpp)
# Build an executable
add_executable(CircleDoubleDriver ${SRC})
