NGINX
=========

A role to install nginx and start a default webserver on a remote host.

Requirements
------------

None

Role Variables
--------------

`packages: [nginx]` 
 * A list of packages to install. Feel free to add more here if needed, 
    separated by commas - `package: [nginx, apache2]`


`domain_name: "localhost"`
 * The domain name to use within `nginx.conf` configurations.
   If you do not own a domain name, use localhost or your public IP here.
   

`nginx_root_dir: "/var/www/html/"`
 * Used in `nginx.conf to define the root directory of content 
   to be served on the nginx webserver.

`index_files: "index.html index.htm"`
 * Used in `nginx.conf` to define index files

Dependencies
------------

A list of other roles hosted on Galaxy should go here, plus any details in regards to parameters that may need to be set for other roles, or variables that are used from other roles.

Example Playbook
----------------

First, make sure all settings within `defaults/main.yml` are correct for your
server. All settings and their purposes are outline in the section above.

Create a new ansible play. You can name it whatever you want, but this
example play will simply be named `nginx.yml`.

```yml
---
- hosts: testserver
  become: yes
  roles:
  - nginx
```

Make sure the IP for `testserver` is correct in the `/etc/ansible/hosts` file -
```
[testserver]
123.123.123.123:22
```

Run the play!

```bash
ansible-playbook nginx.yml
```

License
-------

BSD

Author Information
------------------

Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0

TODO: Add optional task for configuring SSL
