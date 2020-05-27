#!/bin/bash
## Author: Shaun Reed | Contact: shaunrd0@gmail.com | URL: www.shaunreed.com ##
## A custom bash script for creating new linux users.                        ##
## Syntax: ./adduser.sh <username> <userID>                                  ##
###############################################################################

if [ "$#" -ne 2 ]; then
  printf "Illegal number of parameters."
  printf "\nUsage: sudo ./adduser.sh <username> <groupid>"
  printf "\n\nAvailable groupd IDs:"
  printf "\n60001......61183 	Unused | 65520...............65533  Unused"
  printf "\n65536.....524287 	Unused | 1879048191.....2147483647  Unused\n"
  exit
fi

sudo adduser $1 --gecos "First Last,RoomNumber,WorkPhone,HomePhone" --disabled-password --uid $2

printf "\nEnter 1 if $1 should have sudo privileges. Any other value will continue and make no changes\n"
read choice
if [ $choice -eq 1 ] ; then
printf "\nConfiguring sudo for $1...\n"
sudo usermod -aG sudo $1
fi

printf "\nEnter 1 to set a password for $1, any other value will exit with no password set\n"
read choice

if [ $choice -eq 1 ] ; then
printf "\nChanging password for $1...\n"
sudo passwd $1
fi

