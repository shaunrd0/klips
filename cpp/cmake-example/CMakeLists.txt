################################################################################
## Author: Shaun Reed							                                            ##
## Legal: All Content (c) 2022 Shaun Reed, all rights reserved	 	            ##
## About: A template project for getting started working with CMake           ##
##								                                                    	      ##
## Contact: shaunrd0@gmail.com	| URL: www.shaunreed.com | GitHub: shaunrd0   ##
################################################################################

# Define the version of CMake
cmake_minimum_required(VERSION 3.15)

# CMake options
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Compiler options
add_compile_options("-Wall")

# Define the your project name
project (
    #[[NAME]]   CMakeTemplate
    VERSION     1.0
    DESCRIPTION "A basic CMake template for C++ projects"
    LANGUAGES   CXX
)

# Include any directories the compiler may need
include_directories(./include)

# Point CMake to look for more CMakeLists within the following directories
add_subdirectory(src)
add_subdirectory(apps)
