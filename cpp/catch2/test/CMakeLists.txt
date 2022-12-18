################################################################################
## Author: Shaun Reed                                                         ##
## Legal: All Content (c) 2022 Shaun Reed, all rights reserved                ##
## About: Practice project for testing with catch2 framework                  ##
##                                                                            ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0   ##
################################################################################

cmake_minimum_required(VERSION 3.15)

project(
    #[[NAME]]       Catch2
    VERSION         1.0
    DESCRIPTION     "Practice project for learning Catch2"
    LANGUAGES       CXX
)

add_compile_options(-Wall)

add_executable(test_klips test_klips.cpp)
target_link_libraries(test_klips PRIVATE Catch2::Catch2WithMain klips)
target_include_directories(test_klips PRIVATE ${CMAKE_SOURCE_DIR}/include)
