###############################################################################
## Author: Shaun Reed                                                        ##
## Legal: All Content (c) 2020 Shaun Reed, all rights reserved               ##
## About: An example of a queue implementation                               ##
##                                                                           ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0  ##
##############################################################################
## CMakeLists.txt
#

cmake_minimum_required(VERSION 3.2)

# Define the project name
project(Queue)
# Define source files
set(SRC driver.cpp queuelist.cpp)
# Build an executable
add_executable(QueueDriver ${SRC})
