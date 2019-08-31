# Ansible 

A few simple roles / plays I've been able to piece together in learning how to use Ansible. 

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

