################################################################################
## Author: Shaun Reed                                                         ##
## Legal: All Content (c) 2025 Shaun Reed, all rights reserved                ##
##                                                                            ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0   ##
################################################################################

# Define CMake version
cmake_minimum_required(VERSION 3.15)

include(FetchContent)
project(
    #[[NAME]]    OpenGL-Cmake
    DESCRIPTION  "Example project for building OpenGL projects with CMake"
    LANGUAGES    CXX
)
message(STATUS "[Klips] Configuring example: ${PROJECT_NAME}")

add_library(graphics-lib-opengl src/lib-opengl-test.cpp)
target_include_directories(graphics-lib-opengl PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Find OpenGL package
find_package(OpenGL)
if (NOT OPENGL_FOUND)
  message(
      "[Klips] Error: CMake was unable to find OpenGL.\n"
      "On Ubuntu 24.04 OpenGL can be installed using apt:\n"
      "  sudo apt install libopengl-dev libgl1-mesa-dev mesa-common-dev libglu1-mesa-dev\n"
  )
endif()
# Link opengl-test executable to OpenGL
message(STATUS "[Klips] Found OpenGL: ${OPENGL_INCLUDE_DIR}")
target_include_directories(graphics-lib-opengl PUBLIC ${OPENGL_INCLUDE_DIR})
target_link_libraries(graphics-lib-opengl PUBLIC ${OPENGL_LIBRARIES})

find_package(GLUT QUIET)
if(NOT GLUT_FOUND)
  message(
      FATAL_ERROR
      "[Klips] Failed to fetch GLUT. Could not find dependency X11 input libraries.\n"
      "On Ubuntu 24.04 Xi can be installed using apt:\n"
      "  sudo apt install libxi-dev\n"
      "Alternatively, on Ubuntu 24.04 GLUT can be installed with apt:\n"
      "  sudo apt install freeglut3-dev\n"
  )
endif()
message(STATUS "[Klips] Found GLUT: ${GLUT_INCLUDE_DIR}")
# Link lib-opengl-test executable to GLUT
target_include_directories(graphics-lib-opengl PUBLIC ${GLUT_INCLUDE_DIR})
target_link_libraries(graphics-lib-opengl PUBLIC ${GLUT_LIBRARIES})

# Add test executable
add_executable(graphics-cmake-opengl apps/test-gl.cpp)
target_link_libraries(graphics-cmake-opengl PRIVATE graphics-lib-opengl)
target_include_directories(graphics-cmake-opengl PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
