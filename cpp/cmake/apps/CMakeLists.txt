###############################################################################
## Author: Shaun Reed				                                      			     ##
## Legal: All Content (c) 2021 Shaun Reed, all rights reserved	      	     ##
##									                                                         ##
## Contact: shaunrd0@gmail.com	| URL: www.shaunreed.com | GitHub: shaunrd0  ##
##############################################################################
## This directory is for storing / compiling our executable code

# Create a reference / variable to refer to our source code
set(APP_SRC say-hello.cpp)

# Add our executable, naming it and linking it to our source code
add_executable(execute-hello ${APP_SRC})

# Link to our custom library, defined in c-cmake/src/
target_link_libraries(execute-hello lib-klips)

