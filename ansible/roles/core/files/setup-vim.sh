#!/bin/bash
# Author: Shaun Reed | Contact: shaunrd0@gmail.com | URL: www.shaunreed.com ##
## A custom bash script to configure vim with my preferred settings          ##
## Run as user with sudo within directory to store / stash .vimrc configs    ##
###############################################################################


printf "\nUpdating, upgrading required packages...\n"
sudo apt -y update && sudo apt -y upgrade
sudo apt install vim git 

# Clone klips repository in a temp directory
git clone https://github.com/shaunrd0/klips temp/
# Relocate the files we need and remove the temp directory
mkdir -pv /etc/config-vim
mv -fuv temp/README.md /etc/config-vim/ && mv -fuv temp/configs/.vimrc* /etc/config-vim/
rm -Rf temp/
printf "\n${GREEN}Klips config files updated"\
  "\nSee $PWD/etc/config-vim/README.md for more information.${NORMAL}\n\n"

# Create backup dir for .vimrc
mkdir -pv /etc/config-vim/backup/
printf "\n${GREEN}Backup directory created - $PWD/etc/config-vim/backup/${NORMAL}\n"

# Stash the current .vimrc
mv -bv /home/kansible/.vimrc /etc/config-vim/backup/
printf "${RED}Your local .vimrc has been stashed in $PWD/etc/config-vim/backup/${NORMAL}\n\n"

# Copy our cloned config into the user home directory
cp /etc/config-vim/.vimrc /home/kansible/
printf "${GREEN}New /home/kansible/.vimrc configuration installed.${NORMAL}\n"

# Reinstall Pathogen plugin manager for vim
# https://github.com/tpope/vim-pathogen
printf "\n${RED}Removing any previous installations of Pathogen...${NORMAL}\n"
sudo rm -f /home/kansible/.vim/autoload/pathogen.vim

# Install Pathogen
printf "\n${GREEN}Installing Pathogen plugin manager for Vim....\n"\
  "\nIf they don't exist, we will create the following directories:\n"\
  "/home/kansible/.vim/autoload/    ~/.vim/bundle/${NORMAL}"
mkdir -pv /home/kansible/.vim/autoload ~/.vim/bundle && \
  sudo curl -LSso /home/kansible/.vim/autoload/pathogen.vim https://tpo.pe/pathogen.vim
printf "\n${GREEN}Pathogen has been installed! Plugins plugins can now be easily installed.\n"\
  "Clone any plugin repositories into /home/kansible/.vim/bundles${NORMAL}\n"

# Remove any plugins managed by this config tool (Klips)
printf "\n${RED}Removing plugins installed by this tool...${NORMAL}\n"
sudo rm -R /home/kansible/.vim/bundle/*

# Clone plugin repos into pathogen plugin directory 
printf "\n${GREEN}Installing updated plugins...${NORMAL}\n"
git clone https://github.com/ervandew/supertab /home/kansible/.vim/bundle/supertab && \
  printf "\n${GREEN}Supertab plugin has been installed${NORMAL}\n\n" && \
  git clone https://github.com/xavierd/clang_complete /home/kansible/.vim/bundle/clang_complete && \
  printf "\n${GREEN}Clang Completion plugin has been installed${NORMAL}\n\n"
vimConf=( "\n${UNDERLINE}Vim has been configured with the Klips repository.${NORMAL}" \
  "\nConfiguration Changes: " )
printf '%b\n' "${vimConf[@]}"
sudo cat /etc/klips/configs/.vimrc-README

