################################################################################
## Author: Shaun Reed                                                         ##
## Legal: All Content (c) 2022 Shaun Reed, all rights reserved                ##
## About: A root project for practicing C++ multithreading                    ##
##                                                                            ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0   ##
################################################################################

cmake_minimum_required(VERSION 3.16)

project(
    #[[NAME]]   Multithreading
    VERSION     1.0
    DESCRIPTION "Practice with multithreaded programming in C++"
    LANGUAGES   CXX
)
message(STATUS "[Klips] Configuring example: ${PROJECT_NAME}")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
add_compile_options("-Wall")

add_subdirectory(conditions)
add_subdirectory(deadlock)
add_subdirectory(livelock)
add_subdirectory(race-condition)
