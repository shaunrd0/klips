###############################################################################
## Author: Shaun Reed                                                        ##
## Legal: All Content (c) 2019 Shaun Reed, all rights reserved               ##
##                                                                           ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0  ##
##############################################################################

# Create any links we might need
set(LIB_LAUNCHER_SRC lib-launcher.cpp)

# Define our library within CMake and link to the source code
add_library(lib-launcher ${LIB_LAUNCHER_SRC})

