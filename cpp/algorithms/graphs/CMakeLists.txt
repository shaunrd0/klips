###############################################################################
## Author: Shaun Reed                                                        ##
## Legal: All Content (c) 2022 Shaun Reed, all rights reserved               ##
## About: A root project for practicing graph algorithms in C++              ##
##                                                                           ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0  ##
##############################################################################

cmake_minimum_required(VERSION 3.15)

project (
    #[[NAME]]   Graphs
    VERSION     1.0
    DESCRIPTION "A project for practicing algorithms using graphs in C++"
    LANGUAGES   CXX
)
message(STATUS "[Klips] Configuring example: ${PROJECT_NAME}")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(object)
add_subdirectory(simple)
add_subdirectory(templated)
add_subdirectory(weighted)
