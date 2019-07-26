###############################################################################
## Author: Shaun Reed                                                        ##
## Legal: All Content (c) 2019 Shaun Reed, all rights reserved               ##
##                                                                           ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0  ##
##############################################################################

# Create a reference / variable to refer to our source code
set(LAUNCHER_SRC launcher.cpp)

# Add our executable, naming it and linking it to our source code
add_executable(launcher ${LAUNCHER_SRC})

# Link to our custom library, defined in c-cmake/src/
target_link_libraries(launcher lib-launcher)

