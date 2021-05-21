Docker
=========

An ansible role to configure docker on a remote host. This can be used to 
configure one or several servers with basic docker and docker-compose settings.

Requirements
------------

This role will only function correctly on Ubuntu servers, or some debian 
derivative that also uses the `apt` package manager.

Role Variables
--------------

`docker_users: [user1, user2]`
 * Existing users that the role will add to the docker groups to ensure 
   command access

Example Playbook
----------------

First, make sure all settings within `defaults/main.yml` are correct for your
server. All settings and their purposes are outline in the section above.

Create a new ansible play. You can name it whatever you want, but this
example play will simply be named `docker.yml`.

```yml
---
- hosts: testserver
  become: yes
  roles:
  - docker
```

Make sure the IP for `testserver` is correct in the `/etc/ansible/hosts` file -
```
[testserver]
123.123.123.123:22
```

Run the play!

```bash
ansible-playbook docker.yml
```

License
-------

BSD

Author Information
------------------

Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0

TODO: Update to follow the more recent official docker installation instructions
