# Roles

Ansible roles created with `ansible-galaxy init <role> --offline` command

Roles 
 - core - Role to configure a new host with basic authentication / package settings
 - docker - Role to install docker, docker-compose, configure docker user group (Debian / Ubuntu)
 - fail2ban - Role to install and configure fail2ban on a new host
 - nginx - Role to install and configure a new nginx webserver on a host 
 - postfix - Role to install and configure postfix on a new host

All of these roles assume you are using the apt package manager, and running a Debian / Ubuntu system. 


core
------------

A role for configuring a set of packages / settings on a new Ubuntu host using Ansible.

### Packages Added / Configured

Git
 - Configure / set user name and email

SSH
 - MOTD (Template, replacable, displayed on login.)
 - PAM (Template, replacable, authusers file to bypass)
 - Yubikey authentication PAM module
 - authusers (Add users to file to bypass PAM settings)

Vim
 - Install Vim and customizable list of plugins

Ranger

docker
------------

Install and configure Docker and Docker Compose on a new Ubuntu host using Ansible. 


fail2ban
------------

A simple role for installing and configuring fail2ban on a new Ubuntu host using Ansible. Supports templates for jail.local settings and provides a custom filter.d directory copy custom filters to the remote host.


nginx
------------

Install and configure nginx on a new Ubuntu host using Ansible. Supports templates for index.html and custom nginx.conf


postfix
------------

Install and configure the postfix MTA on a new Ubuntu host using Ansible. Supports templates for main.cf and custom sasl_passwd

