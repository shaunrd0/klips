#!/bin/bash
## Author: Shaun Reed | Contact: shaunrd0@gmail.com | URL: www.shaunreed.com ##
## A custom bash script for building cmake projects.                         ##
## Intended to be ran in root directory of the project alongside CMakeLists  ##
###############################################################################

# Infinite while loop - break on conditions
while true
do

  printf "\nEnter 1 to build, 2 to cleanup previous build, 0 to exit.\n"
  read bChoice

  if [ $bChoice -eq 1 ] # Build project
  then
    mkdir build
    (cd build && cmake .. && cmake --build .)
  elif [ $bChoice -eq 2 ] ; then # Cleanup build
    rm -Rv build/*
  elif [ $bChoice -eq 0 ] ; then # Exit script
    break
  else
    continue
  fi
  
done

