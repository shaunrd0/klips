###############################################################################
## Author: Shaun Reed                                                        ##
## Legal: All Content (c) 2021 Shaun Reed, all rights reserved               ##
## About: A basic CMakeLists configuration to test Vector implementation     ##
##                                                                           ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0  ##
##############################################################################
## vector.cpp
#
cmake_minimum_required(VERSION 3.15)

# Define the project name
project(VectorDriver)
# Define source files
set(SRC driver.cpp)
# Build an executable
add_executable(TemplatedVectorDriver ${SRC})
