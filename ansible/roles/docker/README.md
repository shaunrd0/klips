docker
=========

A simple role for installing Docker and Docker Compose on a new Ubuntu host using Ansible. 

Requirements
------------

Expects that the host is using apt package manager, and running a Debian / Ubuntu system. 

Role Variables
--------------

Found in `.../roles/docker/defaults/main.yml`
```
---
docker_users: [user1, user2]
```

#### Docker Group Configuration Variable - 

docker_users - A list of users to configure / add to the docker group

Example Playbook
----------------

After setting the users to configure with Docker in `.../defaults/main.yml`, create the following play.yml and run `ansible-playbook play.yml` after setting the correct hosts in your `/etc/ansible/hosts` file.

```
---
- hosts: docker-host
  become: yes
  roles:
    - docker
```

Feel free to rename play.yml, hosts group name, etc. Just be sure it reflects to your settings in the related files.

