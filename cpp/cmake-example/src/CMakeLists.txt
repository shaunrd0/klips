###############################################################################
## Author: Shaun Reed						                                      	     ##
## Legal: All Content (c) 2022 Shaun Reed, all rights reserved	 	           ##
##								                                                    	     ##
## Contact: shaunrd0@gmail.com	| URL: www.shaunreed.com | GitHub: shaunrd0  ##
##############################################################################
## This directory is for storing source code

# Create any links we might need
set(LIB_SRC lib-klips.cpp)

# Define our library within CMake and link to the source code
add_library(lib-klips ${LIB_SRC})

