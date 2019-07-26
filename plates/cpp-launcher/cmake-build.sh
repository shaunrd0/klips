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

  # Build loop
  # If input read is == 1
  if [ $bChoice -eq 1 ]
  then
    mkdir build
    (cd build && cmake .. && cmake --build .)
  fi

  # Clean-up loop
  # If input read is == 2
  if [ $bChoice -eq 2 ]
  then
    rm -Rv build/*
  fi

  # Exit loops, all other input - 

  # If input read is >= 3, exit
  if [ $bChoice -ge 3 ]
  then
    break 
  fi
  
  # If input read is <= 0, exit
  if [ $bChoice -le 0 ]
  then
    break
  fi

  # Bash will print an error if symbol or character input

done

