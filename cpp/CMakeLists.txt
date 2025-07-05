################################################################################
## Author: Shaun Reed                                                         ##
## Legal: All Content (c) 2025 Shaun Reed, all rights reserved                ##
## About: A root project for practicing C++                                   ##
##        This project can be built to debug and run all nested projects      ##
##        Or, any subdirectory with a project() statement can be selected     ##
##                                                                            ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0   ##
################################################################################

cmake_minimum_required(VERSION 3.15)

project(
    #[[NAME]]   Klips
    VERSION     1.0
    DESCRIPTION "A root project for several small cpp practice projects"
    LANGUAGES   CXX
)
message(STATUS "[Klips] Configuring example: ${PROJECT_NAME}")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
add_compile_options("-Wall")

option(KLIPS_CCACHE "Enable ccache" ON)

if (KLIPS_CCACHE)
  find_program(SCCACHE_PATH sccache)
  if(SCCACHE_PATH)
    message(STATUS "[Klips] Found sccache: ${SCCACHE_PATH}")
    set(CMAKE_CXX_COMPILER_LAUNCHER ${SCCACHE_PATH})
    set(CMAKE_C_COMPILER_LAUNCHER ${SCCACHE_PATH})
  else()
    message(STATUS "[Klips] Failed to find sccache, falling back to ccache.")
    find_program(CCACHE_PATH ccache)
    if(CCACHE_PATH)
      message(STATUS "[Klips] Found ccache: ${CCACHE_PATH}")
      set(CMAKE_CXX_COMPILER_LAUNCHER ${CCACHE_PATH})
      set(CMAKE_C_COMPILER_LAUNCHER ${CCACHE_PATH})
    else()
      message(WARNING "[Klips] Failed to find sccache and ccache. Compilation will not be cached.")
    endif()
  endif()
endif()

add_subdirectory(algorithms)
add_subdirectory(catch2)
add_subdirectory(cmake-example)
add_subdirectory(cryptography)
add_subdirectory(datastructs)
add_subdirectory(graphics)
add_subdirectory(multithreading)
add_subdirectory(patterns)

find_package(Qt6 COMPONENTS UiPlugin Core Gui Widgets)
if (NOT Qt6_FOUND)
  message(
      WARNING
      "[Klips] Qt examples will not be built.\n"
      "On Ubuntu 24.04 Qt6 can be installed using apt:\n"
      "  sudo apt install qt6-base-dev qt6-tools-dev\n"
  )
else()
  add_subdirectory(qt)
endif()
