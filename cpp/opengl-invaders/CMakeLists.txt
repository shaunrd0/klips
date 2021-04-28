###############################################################################
## Author: Shaun Reed                                                        ##
## Legal: All Content (c) 2019 Shaun Reed, all rights reserved               ##
##                                                                           ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0  ##
###############################################################################

# Define CMake version
cmake_minimum_required(VERSION 3.16)

project(       # Define project
    invaders  # Project name
    DESCRIPTION  "Space invaders remake using OpenGL and CPP"
    LANGUAGES    CXX
    )

# Pass this to program to control debug output
option (EXE_BUILD "Should we build the executable?" ON)

add_library(             # Add Library
    lib-invaders            # Library Name
    "src/lib-invaders.cpp"  # Sources..
    "src/lib-invaders.h"
    )

target_include_directories(        # When calling library, include a directory
    lib-invaders                      # Library name
    PUBLIC                           #
    "${CMAKE_CURRENT_SOURCE_DIR}"  # Source directory of exe including our library
    )

if (EXE_BUILD)
  set(BUILD_STATUS "Building default executable")
  include(FindOpenGL)
  include(FindGLUT)
  include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIR})

  add_executable(         # Creating executable
      invaders             # Exe name
      "app/invaders.cpp"  # Exe Source(s)
      )

  # Link the executable with OpenGL libraries
  target_link_libraries(  # Linking the exe to library
      invaders        # Executable to link
      PUBLIC          #
      lib-invaders    # Library to link
      ${OPENGL_LIBRARIES}
      )

  # Link the executable with OpenGL Utility Toolkit
  target_link_libraries(  # Linking the exe to library
      invaders        # Executable to link
      PUBLIC          #
      lib-invaders    # Library to link
      ${GLUT_LIBRARIES}
      )
endif()
