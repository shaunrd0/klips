################################################################################
## Author: Shaun Reed                                                         ##
## Legal: All Content (c) 2021 Shaun Reed, all rights reserved                ##
##                                                                            ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0   ##
################################################################################

# Define CMake version
cmake_minimum_required(VERSION 3.15)

project(
    #[[NAME]]    OpenGL-Cmake
    DESCRIPTION  "Example project for building OpenGL projects with CMake"
    LANGUAGES    CXX
)

add_library(graphics-lib-opengl src/lib-opengl-test.cpp)
target_include_directories(graphics-lib-opengl PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Find OpenGL package
find_package(OpenGL REQUIRED)
if (OPENGL_FOUND)
  # Link opengl-test executable to OpenGL
  target_include_directories(graphics-lib-opengl PUBLIC ${OPENGL_INCLUDE_DIR})
  target_link_libraries(graphics-lib-opengl PUBLIC ${OPENGL_LIBRARIES})
else()
  message(
      "Error: CMake was unable to find the OpenGL package\n"
      "Please install OpenGL and try again\n"
  )
endif()

# Find GLUT package
find_package(GLUT REQUIRED)
if (GLUT_FOUND)
  # Link lib-opengl-test executable to GLUT
  target_include_directories(graphics-lib-opengl PUBLIC ${GLUT_INCLUDE_DIR})
  target_link_libraries(graphics-lib-opengl PUBLIC ${GLUT_LIBRARIES})
else()
  message(
      "Error: CMake was unable to find the GLUT package\n"
      "Please install GLUT (freeglut3-dev) and try again\n"
  )
endif()

# Add test executable
add_executable(graphics-cmake-opengl apps/test-gl.cpp)
target_link_libraries(graphics-cmake-opengl PRIVATE graphics-lib-opengl)
target_include_directories(graphics-cmake-opengl PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
