################################################################################
## Author: Shaun Reed                                                         ##
## Legal: All Content (c) 2022 Shaun Reed, all rights reserved                ##
## About: An example and solution for livelocks in C++                        ##
##                                                                            ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0   ##
################################################################################

cmake_minimum_required(VERSION 3.16)

# std::scoped_lock requires C++17
set(CMAKE_CXX_STANDARD 17)
add_compile_options("-Wall")

project(
    #[[NAME]]   LiveLock
    VERSION     1.0
    DESCRIPTION "Example and solution for livelocks in C++"
    LANGUAGES   CXX
)
message(STATUS "[Klips] Configuring example: ${PROJECT_NAME}")

add_executable(
    multithread-livelock driver.cpp
)

target_link_libraries(multithread-livelock pthread)
