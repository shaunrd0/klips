###############################################################################
## Author: Shaun Reed                                                        ##
## Legal: All Content (c) 2020 Shaun Reed, all rights reserved               ##
## About: An example of a stack implementation using linked lists            ##
##                                                                           ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0  ##
##############################################################################
## CMakeLists.txt
#

cmake_minimum_required(VERSION 3.2)

# Define the project name
project(Stack)
# Define source files
set(SRC driver.cpp stacklist.cpp)
# Build an executable
add_executable(StackDriver ${SRC})
