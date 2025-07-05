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
message(STATUS "[Klips] Configuring example: ${PROJECT_NAME}")

add_compile_options(-Wall)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

Include(FetchContent)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v3.4.0
)
FetchContent_MakeAvailable(Catch2)

add_library(klips SHARED src/klips.cpp)
target_include_directories(klips PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(test_klips src/test_klips.cpp)
target_link_libraries(test_klips PUBLIC Catch2::Catch2WithMain klips)
