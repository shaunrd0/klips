###############################################################################
## Author: Shaun Reed                                                        ##
## Legal: All Content (c) 2019 Shaun Reed, all rights reserved               ##
##                                                                           ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0  ##
##############################################################################
# Root CMakeLists.txt of cpp practice 4-inheritance

# Define CMake version
cmake_minimum_required(VERSION 3.15)

project(       # Define project
  inheritance  # Project name
  DESCRIPTION  "Example project for class inheritance"
  LANGUAGES    CXX
  )

# Pass this to program to control debug output
option (DB_CONF "Should we debug and configure files with cmake values?" ON)
option (DB_BUILD "Should we run the build in debug mode?" OFF)
option (EXE_BUILD "Should we build the executable?" ON)

add_library(             # Add Library
  lib-inherit            # Library Name
  "src/lib-inherit.cpp"  # Sources..
  "src/lib-inherit.h"
)

target_include_directories(        # When calling library, include a directory
  lib-inherit                      # Library name
  PUBLIC                           #
    "${CMAKE_CURRENT_SOURCE_DIR}"  # Source directory of exe including our library
)

if (EXE_BUILD)
  set(BUILD_STATUS "Building default executable")
  include(FindPkgConfig)
  pkg_search_module(SDL2 REQUIRED sdl2)
  include_directories(${SDL2_INCLUDE_DIRS})

  add_executable(         # Creating executable
    inherited             # Exe name
    "apps/inherited.cpp"  # Exe Source(s)
  )
  target_link_libraries(  # Linking the exe to library
    inherited        # Executable to link
    PRIVATE          #
      lib-inherit    # Library to link
      ${SDL2_LIBRARIES}
  )
elseif(DB_BUILD)
  set(BUILD_STATUS "Building in debug mode")

  # Create compile_commands.json for linter
  set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

  target_compile_definitions(inherited PRIVATE BUILD_STATUS=${BUILD_STATUS})
elseif(DB_CONF)
  set(BUILD_STATUS "Building in debug mode, configuring files")

  # Configure header file with CMake variables defined in src/lib-inherit.h.in
  # @ONLY is specified, only variables of the form @VAR@ will be replaced and ${VAR} will be ignored.
  # configure_file(src/lib-inherit.h src/lib-inherit.h @ONLY)
  configure_file(apps/inherited.cpp apps/inherited.cpp @ONLY)
 
  # Create compile_commands.json for linter
  set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
endif()
#target_compile_definitions(inherited PRIVATE BUILD_STATUS=${BUILD_STATUS})

