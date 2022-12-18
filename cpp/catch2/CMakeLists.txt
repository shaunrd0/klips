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

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

Include(FetchContent)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v3.0.1
)
FetchContent_MakeAvailable(Catch2)

add_subdirectory(src)
add_subdirectory(test)
