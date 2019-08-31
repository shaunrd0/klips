core
=========

A simple role for configuring a set of packages / settings on a new Ubuntu host using Ansible.

Packages Added / Configured
 - Git
 -- Configure / set user name and email
 - SSH
 -- MOTD (Template, replacable, displayed on login.)
 -- PAM (Template, replacable, authusers file to bypass)
 -- authusers (Add users to file to bypass PAM settings)
 - Vim
 -- Install Vim
 -- Run https://github.com/shaunrd0/klips/scripts/setup-vim.sh

Requirements
------------

Expects that the host is using apt package manager, and running a Debian / Ubuntu system. 

Role Variables
--------------

Found in `.../roles/core/defaults/main.yml`
```
---
packages: [git, vim, ssh]
ssh_port: 22
auth_methods: "publickey,keyboard-interactive"
git_email: "user@domain.com"
git_name: "First Last"
hostname: "localhost"
domain_name: "www.localhost.com"
```

Basic package installation variable - 

packages - A list of packages to install when running core configuration. Add package to this list and it will be installed on your new host. Further configuration will need to be done manually, unless the role is modified otherwise.

SSH Configuration Variables - 

ssh_port - The port to configure SSH to listen on

auth_methods - Authentication methods to allow SSH base configuration to use. Otherwise, specify a match within the sshd_config

MOTD Configuration Variables - 

hostname - The hostname of the box you are using, used in the MOTD for a host-specific greeting, so you know which host you are logged into when glancing between terminals.

domain_name - The domain name, if available, associated with this host.

Git Configuration Variables - 

git_email - Email address to configure with Git

git_name - Full name to configure with Git (First Last || Shaun Reed)

Example Playbook
----------------

After configuring the appropriate variables in `.../defaults/main.yml`, create the following play.yml and run `ansible-playbook play.yml` after setting the correct hosts in your `/etc/ansible/hosts` file.

```
---
- hosts: core
  become: yes
  roles:
  - core
```

Feel free to rename play.yml, hosts group name, etc. Just be sure it reflects to your settings in the related files.

