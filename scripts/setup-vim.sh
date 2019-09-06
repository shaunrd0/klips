#!/bin/bash
## Author: Shaun Reed | Contact: shaunrd0@gmail.com | URL: www.shaunreed.com ##
## A custom bash script to configure vim with my preferred settings          ##
## Run as user with sudo within directory to store / stash .vimrc configs    ##
###############################################################################

# For easy colorization of printf
GREEN=$(tput setaf 2)
RED=$(tput setaf 1)
UNDERLINE=$(tput smul)
NORMAL=$(tput sgr0)


welcome=( "\nEnter 1 to configure vim with the Klips repository, any other value to exit." \
  "The up-to-date .vimrc config can be found here: https://github.com/shaunrd0/klips/tree/master/configs" \
  "${RED}Configuring Vim with this tool will update / upgrade your packages${NORMAL}\n\n")

printf '%b\n' "${welcome[@]}"
read cChoice

if [ $cChoice -eq 1 ] ; then
  
  printf "\nUpdating, upgrading required packages...\n"
  sudo apt -y update && sudo apt -y upgrade
  sudo apt install vim git 

  # Clone klips repository in a temp directory
  git clone https://github.com/shaunrd0/klips temp/
  # Relocate the files we need and remove the temp directory
  sudo mkdir -pv /etc/config-vim
  sudo cp -fruv temp/README.md /etc/config-vim/
  
  sudo cp -fruv temp/configs/ /etc/config-vim/
  
  rm -Rf temp/
  printf "\n${GREEN}Klips config files updated"
  printf "\nSee /etc/config-vim/README.md for more information.${NORMAL}\n\n"

  # Create backup dir for .vimrc
  sudo mkdir -pv /etc/config-vim/backup/
  printf "\n${GREEN}Backup directory created - /etc/config-vim/backup/${NORMAL}\n"

  # Stash the current .vimrc
  sudo mv -bv ~/.vimrc /etc/config-vim/backup/
  printf "${RED}Your local .vimrc has been stashed in /etc/config-vim/backup/${NORMAL}\n\n"

  # Copy our cloned config into the user home directory
  sudo cp /etc/config-vim/configs/.vimrc ~/
  printf "${GREEN}New ~/.vimrc configuration installed.${NORMAL}\n"

  # Copy our cloned config into the global user directories
  sudo cp /etc/config-vim/configs/.vimrc /usr/share/vim/vimfiles/vimrc
  sudo cp /etc/config-vim/configs/.vimrc /etc/vim/vimrc

  # Reinstall Pathogen plugin manager for vim
  # https://github.com/tpope/vim-pathogen
  printf "\n${RED}Removing any previous installations of Pathogen...${NORMAL}\n"
  sudo rm -f /usr/share/vim/vimfiles/autoload/pathogen.vim
  
  # Install Pathogen
  printf "\n${GREEN}Installing Pathogen plugin manager for Vim....\n"
	printf "\nIf they don't exist, we will create the following directories:\n"
	printf  "/usr/share/vim/vimfiles/autoload/    /usr/share/vim/vimfiles/bundle/${NORMAL}"
  mkdir -pv /usr/share/vim/vimfiles/autoload /usr/share/vim/vimfiles/bundle && \
  sudo curl -LSso /usr/share/vim/vimfiles/autoload/pathogen.vim https://tpo.pe/pathogen.vim
  printf "\n${GREEN}Pathogen has been installed! Plugins plugins can now be easily installed.\n"\
         "Clone any plugin repositories into /usr/share/vim/vimfiles/bundles${NORMAL}\n"

  # Remove any plugins managed by this config tool (Klips)
  printf "\n${RED}Removing plugins installed by this tool...${NORMAL}\n"
  sudo rm -R /usr/share/vim/vimfiles/bundle/*

  # Clone plugin repos into pathogen plugin directory 
  printf "\n${GREEN}Installing updated plugins...${NORMAL}\n"
  git clone https://github.com/ervandew/supertab /usr/share/vim/vimfiles/bundle/supertab && \
  printf "\n${GREEN}Supertab plugin has been installed${NORMAL}\n\n" && \
  git clone https://github.com/xavierd/clang_complete /usr/share/vim/vimfiles/bundle/clang_complete && \
  printf "\n${GREEN}Clang Completion plugin has been installed${NORMAL}\n\n"
  vimConf=( "\n${UNDERLINE}Vim has been configured with the Klips repository.${NORMAL}" \
    "\nConfiguration Changes: " )
  printf '%b\n' "${vimConf[@]}"


else
printf "\nExiting..\n"
fi

sudo cat /etc/config-vim/configs/.vimrc-README


