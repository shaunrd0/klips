# Roles

Some simple Ansible roles created with `ansible-galaxy init <role> --offline` command

klips/ansible/roles/...
 - core - Role to configure a new host with basic authentication / package settings
 - docker - Role to install docker, docker-compose, configure docker user group
 - nginx - Role to install and configure a new nginx webserver on a host 

All of these roles assume you are using the apt package manager, and running a Debian / Ubuntu system. 

core
------------

A simple role for configuring a set of packages / settings on a new Ubuntu host using Ansible.

Packages Added / Configured
 - Git
  - Configure / set user name and email
 - SSH
  - MOTD (Template, replacable, displayed on login.)
  - PAM (Template, replacable, authusers file to bypass)
  - authusers (Add users to file to bypass PAM settings)
 - Vim
  - Install Vim
  - Run https://github.com/shaunrd0/klips/blob/master/scripts/setup-vim.sh


docker
------------

A simple role for installing Docker and Docker Compose on a new Ubuntu host using Ansible. 


nginx
------------

A simple role for installing and configuring nginx on a new Ubuntu host using Ansible. Supports templates for index.html and custom nginx.conf

