###############################################################################
## Author: Shaun Reed                                                        ##
## Legal: All Content (c) 2021 Shaun Reed, all rights reserved               ##
##                                                                           ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0  ##
##############################################################################
#

# Define CMake version
cmake_minimum_required(VERSION 3.15)

project(
    #[[NAME]]    SDL-Cmake
    DESCRIPTION  "Example project for building SDL projects with CMake"
    LANGUAGES    CXX
)

# Add Library
add_library(
    lib-sdl-test            # Library Name
    "src/lib-sdl-test.cpp"  # Sources..
    "src/lib-sdl-test.h"
)

target_include_directories(            # When calling library, include a directory
    lib-sdl-test                       # Library name
    PUBLIC                             # Visibility
    "${CMAKE_CURRENT_SOURCE_DIR}/src"  # Source directory for library
    )

# Search for SDL2 package
find_package(SDL2 REQUIRED sdl2)

# If SDL2 was found successfully, link to lib-sdl-test
if (SDL2_FOUND)
  # Any target that links with this library will also link to SDL2
  # + Because we choose PUBLIC visibility
  target_include_directories(lib-sdl-test PUBLIC ${SDL2_INCLUDE_DIRS})
  target_link_libraries(lib-sdl-test PUBLIC "${SDL2_LIBRARIES}")

  # Creating executable
  add_executable(
      sdl-test              # Exe name
      "apps/sdl-test.cpp"   # Exe Source(s)
  )

  # Linking the exe to library
  target_link_libraries(
      sdl-test              # Executable to link
      PRIVATE               # Visibility
      lib-sdl-test          # Library to link
  )

else()
  message(
      "Error: CMake was unable to find SDL2 package.\n"
      "Please install the libsdl2-dev package and try again.\n"
  )
endif()
