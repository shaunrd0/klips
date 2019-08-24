# klips
Snippets that I frequently use and share

This repository is a collection of code snippets that I reuse, clone, or frequently refer to in regards to configurations or settings. This can be cloned as a whole and refered to locally as needed, or copied around and used to lay out templates for larger projects.

The snippets are organized within topic-labeled folders. 'plates' is short-hand for templates, and houses all folders / projects that can be copied and edited / adjusted locally as templates for larger projects.

Other directories could contain configuration files, bash exports, scripts, etc.

All snippets will be listed below with the directories in the master branch. If you are not on master, I cant guarentee anything will be anywhere unless otherwise described.

### Contents

```
https://github.com/shaunrd0/...
klips/
├── ansible
│   ├── apt-up.yml
│   ├── hosts
│   ├── nginx.yml
│   └── roles
├── configs
├── plates
│   ├── cpp-cmake
│   └── cpp-launcher
├── README.md
├── refs
│   └── doxygenROT
└── scripts
    ├── cmake-build.sh
    ├── README.md
    └── setup-vim.sh
```

ansible  (Ansible roles, playbooks)
 - nginx.yml (Playbook example for using nginx role)
 - hosts (Same ansible hosts file) 
 - apt-up.yml (Playbook to update servers / groups ad hoc) 
 - roles (Basic ansible role created with ansible-galaxy command) 
 -- nginx

plates (Simple cpp executable template, built using cmake) 
 - cpp-cmake  
 - cpp-launcher (Simple cpp launcher template, built using cmake. Easily expandable.) 

refs
 - doxygenROT (Basic rule-of-thumb for Doxygen commenting) 

scripts
 - cmake-build.sh (Script to toss around and build cmake projects) 
 - README.md
 - setup-vim.sh (Script for setting up vim configuration) 

configs
 - .vimrc (Various settings for vim, can be copied or used with setup-vim.sh) 
 - .vimrc-README (What these settings do, output when setup-vim.sh is ran.) 

