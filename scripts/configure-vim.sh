#!/bin/bash
## Author: Shaun Reed | Contact: shaunrd0@gmail.com | URL: www.shaunreed.com ##
## A custom bash script for building cmake projects.                         ##
## Intended to be ran in root directory of the project alongside CMakeLists  ##
###############################################################################

printf "\nEnter 1 to configure, 2 to revert configuration."
printf "\nAny other value will exit."
printf "\nConfiguring Vim will overwrite your current ~/.vimrc!\n"

read cChoice

if [ $cChoice -eq 1 ] ; then
  
  # Clone klips repository - 
  git clone https://github.com/shaunrd0/klips temp/

  # Clean up files we don't need from the repo
  mkdir config-vim
  mv temp/README.md config-vim/ && mv temp/configs/ config-vim/
  rm -R temp/

  # Replace our .vimrc in the home directory
  mkdir config-vim/backup/
  mv -f ~/.vimrc config-vim/backup/.vimrc.bak
  cp config-vim/configs/.vimrc ~/

  # Reinstall Pathogen plugin manager for vim
  # https://github.com/tpope/vim-pathogen
  
  # Remove Pathogen
  rm ~/.vim/autoload/pathogen.vim
  
  # Install Pathogen
  mkdir -p ~/.vim/autoload ~/.vim/bundle && \
  curl -LSso ~/.vim/autoload/pathogen.vim https://tpo.pe/pathogen.vim

  # Remove all plugins / repositories added by config tool
  rm -R ~/.vim/bundles/supertab/

  # clone all repos into pathogen plugin directory
  (cd ~/.vim/bundles/ && \
   git clone https://github.com/ervandew/supertab)


else
printf "\nExiting..\n"
fi

