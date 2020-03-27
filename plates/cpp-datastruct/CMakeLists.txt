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

# # Location of our header files
# # include_directories(./include)
# include_directories(${PROJECT_BINARY_DIR})
# include_directories( ${CMAKE_BINARY_DIR}/generated/ )


# # Additional directories to expect a CMakeLists.txt
# # add_subdirectory(src)
# # add_subdirectory(apps)

# # Configure includes to consider cmake variables
# configure_file(${INCLUDE_DIR}/lib-datastruct.h.in ${CMAKE_BINARY_DIR}/generated/lib-datastruct.h)

# # /apps/CMakeLists.txt
# # Create a variable to reference any sources to add
# set(LIB_DS_SRC ${SRC_DIR}/lib-datastruct.cpp)
# # Create our library
# add_library(lib-datastruct ${LIB_DS_SRC})
# # Point the library to directories containing any includes it might need
# target_include_directories(lib-datastruct PUBLIC "${INCLUDE_DIR}")

# # /src/CMakeLists.txt
# # Create a variable to reference our driver program source code
# set(DRIVER_SRC ${APPS_DIR}/driver.cpp)
# # Add the executable to the build list
# add_executable(Driver ${DRIVER_SRC})
# # Link custom libraries to our executable
# target_link_libraries(Driver lib-datastruct)

# # target_include_directories(Driver PUBLIC "${INCLUDE_DIR}")
