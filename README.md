# klips

This repository is a collection of code snippets that I reuse, clone, or frequently refer to. This can be cloned as a whole or just viewed / copied as needed, used to lay out templates / automate tasks for larger projects.

The snippets are organized within topic-labeled folders. 'plates' is short-hand for templates, and houses all folders / projects that can be copied and edited / adjusted locally as templates for larger projects.

Other directories could contain configuration files, bash exports, scripts, etc.

All snippets will be listed below with the directories in the master branch. If you are not on master, I cant guarentee anything will be anywhere unless otherwise described.

### Contents

```
https://github.com/shaunrd0/...
klips/
├── ansible
│   ├── apt-up.yml
│   ├── core.yml
│   ├── docker.yml
│   ├── hosts
│   ├── make-host.yml
│   ├── nginx.yml
│   └── roles
│       ├── core
│       ├── docker
│       └── nginx
├── configs
│   ├── .vimrc
│   └── .vimrc-README
├── plates
│   ├── cpp-cmake
│   └── cpp-launcher
├── README.md
├── refs
│   └── doxygenROT
└── scripts
    ├── adduser.sh
    ├── cmake-build.sh
    ├── README.md
    └── setup-vim.sh
```

### ansible

Ansible roles, playbooks

Playbooks
 - apt-up.yml - Playbook to update servers / groups ad hoc
 - core.yml  - Playbook example for using core configuration role
 - docker.yml - Playbook example for using docker install role (Debian / Ubuntu)
 - hosts - Sample / partially default ansible hosts file
 - make-host.yml - Playbook example for using multiple roles together to create a new host
 - nginx.yml - Playbook example for using nginx role 

Roles 
 - Basic ansible role created with ansible-galaxy command
 - core - Role to configure a new host with basic authentication / package settings
 - docker - Role to install docker, docker-compose, configure docker user group (Debian / Ubuntu)
 - nginx - Role to install and configure a new nginx webserver on a host 

### configs
 - .vimrc - Various settings for vim, can be copied or used with setup-vim.sh) 
 - .vimrc-README - What these settings do, output when setup-vim.sh is ran.) 

### plates  
 - cpp-cmake - Simple cpp executable template, built using cmake
 - cpp-launcher - Simple cpp launcher template, built using cmake. Easily expandable.

### refs
 - doxygenROT - Basic rule-of-thumb for Doxygen commenting

### scripts

adduser.sh - Script to add new user, run with sudo if you want to configure / allow user to sudo
 - `./adduser` - (Print help text)
 - `./adduser <name> <userID>` - (Don't need sudo if new user doesn't need it)
 - `sudo ./adduser <name> <userID>`
 - `sudo ./adduser jeff 1005` - (Create jeff user and assign userID to 1005)
 - Follow prompts to configure password / sudo depending on needs of new user 
 
cmake-build.sh 
 - Script to toss around and build cmake projects
 
README.md
 - Further clarification of scripts

setup-vim.sh
 - Script for setting up vim configuration
 - Includes Pathogen Plugin manager
 - Includes auto-completion (Clang_completion)
 - Supertab completion interaction (Tab to interact with completion context)
 - Syntax highlighting
 - Tabsize 2, use spaces in place of tabs
 - auto indentation, mouse interaction when supported
 - Custom keybind (Ctrl-e for jumping windows || Ctrl-w still works if not in a tabbed terminal where the same will close the tab)
 - See klips/configs/.vimrc-README for more information


