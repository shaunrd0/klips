Core
=========

An ansible role for deploying a default configuration for Ubuntu servers

This role installs ranger, vim with Pathogen and plugins, configures git, `.bashrc`, `.bash_aliases`, 
unattended-upgrades, SSH configurations, PAM modules, Yubikey authentication, 
and installs a custom MOTD to display on login.

Requirements
------------

None, this role will apply settings specified in `core/defaults/main.yml`
The only requirement is that we can run this play on the remote host to configure.
I test this role on Ubuntu servers.
Though the way packages are installed in this role is not specific to Ubuntu, 
locations of certain destinations for configs may be slightly different. 

**WARNING:**
As this role is a WIP, there is a *temporary* requirement to modify
`core/files/authorized_yubikeys` manually. Be sure these key prefixes match that
 of your yubikeys, and that the username also corresponds with the user on the 
 system who should be identified and authenticated by this yubikey.

Example: 
```
username:cccckey1cccc:cccckey2cccc
```

Where the user `username` can be identified by *two* yubikeys.
Both yubikeys generate OTP with a static prefix of 
`cccckey1cccc` or `cccckey2cccc`

Role Variables
--------------

`packages: [python-apt, git, vim, ssh, libpam-yubico, ranger]`
 * A list of packages to install on the system with the default package manager

`authusers: [user1, user2]`
 * The users that should bypass additional PAM authentication modules. 
   This does not include public key authentication. 
   All users must provide a valid key. This will only bypass passwords and 2FA

`ssh_port: 22`
 * The port SSH is running on the server

`auth_methods: "publickey,keyboard-interactive"`
 * Authentication methods to configure within `/etc/sshd_config` file
   
`git_email: "someemail@gmail.com"`
`git_name: "Shaun Reed"`
 * The email address and name to configure within `~/.gitconfig` file.
   This applies to the user that executes ansible plays on the remote server.
   
```yml
vim_plugins: [{ repo: 'dense-analysis/ale', dest: 'ale'},
{ repo: 'chrisbra/Colorizer', dest: 'colorizer'},
{ repo: 'ervandew/supertab', dest: 'supertab'},
{ repo: 'chrisbra/unicode.vim', dest: 'unicode'},
{ repo: 'vim-airline/vim-airline', dest: 'vim-airline'},
{ repo: 'vim-airline/vim-airline-themes', dest: 'vim-airline-themes'},
{ repo: 'mhinz/vim-signify', dest: 'signify'}
]
```
 * A list of vim plugins to install.
   These plugins will be installed for the user that executes ansible plays
   on the remote host. These will also be cloned into `/etc/skel/.vim/bundle/`, 
   making all of these plugins available for all future users created on the system.
   Vim plugins are managed by Pathogen.

`upgrades_email: someemail@gmail.com`
 * Used to configure `/etc/apt/apt.conf.d/50unattended-upgrades`.
   Email alerts will be sent to this address when automatic upgrades are performed
   

Dependencies
------------

None.

Example Playbook
----------------

First, make sure all settings within `defaults/main.yml` are correct for your
server. All settings and their purposes are outline in the section above.

Create a new ansible play. You can name it whatever you want, but this 
example play will simply be named `core.yml`.

```yml
---
- hosts: testserver
  become: yes
  roles:
  - core
```

Make sure the IP for `testserver` is correct in the `/etc/ansible/hosts` file -
```
[testserver]
123.123.123.123:22
```

Run the play!

```bash
ansible-playbook core.yml
```

License
-------

BSD

Author Information
------------------

Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0


TODO: Add variables for `authorized_yubikeys`
TODO: Add variables for configuring a custom `/etc/hosts`
TODO: Use a package manager, or official repository to install ranger
