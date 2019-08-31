nginx
=========

A simple role for installing and configuring nginx on a new Ubuntu host using Ansible. Supports templates for index.html and custom nginx.conf

Requirements
------------

Expects that the host is using apt package manager, and running a Debian / Ubuntu system. 

Role Variables
--------------

Found in `.../roles/nginx/defaults/main.yml`
```
---
domain_name: "localhost"
nginx_root_dir: "/var/www/html/"
index_files: "index.html index.htm"
```

NGINX Configuration Variables - 

domain_name - Domain name to be used in nginx.conf, default value is the same as nginx base package default setting (localhost)

nginx_root_dir - The directory to point the default nginx server to

index_files - The files / types to be checked for content in our root directory

Example Playbook
----------------

After configuring the approprate variables in `.../defaults/main.yml`, create the following play.yml and run `ansible-playbook play.yml` after setting the correct hosts in your `/etc/ansible/hosts` file.

```
---
- hosts: nginx-server
  become: yes
  roles:
  - nginx
```

Feel free to rename play.yml, hosts group name, etc. Just be sure it reflects to your settings in the related files.


