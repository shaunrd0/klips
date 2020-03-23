###############################################################################
## Author: Shaun reserved                                                    ##
## Legal: All Content (c) 2020 Shaun Reed, all rights reserved               ##
##                                                                           ##
## Contact: shaunrd0@gmail.com	| URL: www.shaunreed.com | GitHub: shaunrd0  ##
##############################################################################

# Define the version of CMake
cmake_minimum_required(VERSION 3.10)
# Name and version of our project
project(DataStruct VERSION 0.1)
# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Create path variables relative to root directory (CMAKE_SOURCE_DIR)
set(APPS_DIR ./apps)
set(SRC_DIR ./src)
set(INCLUDE_DIR ./include)
set(DRIVER_SRC ${APPS_DIR}/driver.cpp)
set(LIB_DS_SRC ${SRC_DIR}/lib-datastruct.cpp)

add_library(lib-ds ${LIB_DS_SRC})

add_executable(Driver ${DRIVER_SRC})

target_link_libraries(Driver PUBLIC lib-ds)

target_include_directories(lib-ds PUBLIC ${INCLUDE_DIR})

# configure_file(${INCLUDE_DIR}/lib-datastruct.h.in ${CMAKE_BINARY_DIR}/generated/lib-datastruct.h)
# include_directories( ${CMAKE_BINARY_DIR}/generated/ )
