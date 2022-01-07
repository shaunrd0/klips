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
    #[[NAME]]    OpenGL-Cmake
    DESCRIPTION  "Example project for building OpenGL projects with CMake"
    LANGUAGES    CXX
)

add_library(lib-opengl-test "src/lib-opengl-test.cpp")
target_include_directories(lib-opengl-test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Find OpenGL package
find_package(OpenGL REQUIRED)
if (OPENGL_FOUND)
  # Link opengl-test executable to OpenGL
  target_include_directories(lib-opengl-test PUBLIC ${OPENGL_INCLUDE_DIR})
  target_link_libraries(lib-opengl-test PUBLIC ${OPENGL_LIBRARIES})
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
  target_include_directories(lib-opengl-test PUBLIC ${GLUT_INCLUDE_DIR})
  target_link_libraries(lib-opengl-test PUBLIC ${GLUT_LIBRARIES})
else()
  message(
      "Error: CMake was unable to find the GLUT package\n"
      "Please install GLUT (freeglut3-dev) and try again\n"
  )
endif()

# Add test executable
add_executable(opengl-test "apps/test-gl.cpp")
target_link_libraries(opengl-test PRIVATE lib-opengl-test)
target_include_directories(opengl-test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
