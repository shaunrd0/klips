### Scripts

I write these scripts for my own use, and you may need to tweak them slightly to suit your needs. 

Never run a script you can't read or understand. Comments can be found in the scripts, usually explaining them block-by-block. Below is my personal use cases for the scripts, to provide further insight into how I use them and how they might be useful to you.

adduser.sh
------------

This script was made on Ubuntu when creating a few users across multiple hosts. Syntax requires at least 2 arguments when running the script, otherwise help text will be output warning of correct usage and available options. The script can be used to configure sudo on a new user if the script itself is ran with sudo. Otherwise, creating a default user with or without a password is possible without sudo. If the script is ran on an existing user or a userID that is already in use is passed, no changes will happen in user-creation but you may still allow the user to sudo and change their password. 

Syntax - 

`./adduser` (Help text)
`./adduser jeff 1005` (Create user jeff with userID 1005, can't configure sudo, prompt for possible password creation)

`sudo ./adduser` (Help text)
`sudo ./adduser jeffy 1010` (Create user jeffy with userID 1010, can configure sudo, possible password creation)

Didn't configure sudo, and don't want to do so manually? Re-run the script on the existing user just as above, and accept the prompt for sudo configuration.
`sudo ./adduser jeff 1005` (User creation will fail, follow prompts to configure sudo and / or reset user password)

cmake-build.sh
------------

I usually run this script within whatever directory I'm working in, hence the infinite loop, I leave the script running until I'm done with my work and move to a new directory / cmake project.


setup-vim.sh
------------

To use this script, run `sudo ./setup-vim.sh` as seen below. Vim configs used for this script are stored in `/etc/config-vim/`. When the script runs into previous vimrc configs they are backed up into `/etc/config-vim/backups/`

```bash
cloud_user@shaunrd03c:~$ ./setup-vim.sh 
This script must be ran with sudo...
sudo ./setup-vim.sh
cloud_user@shaunrd03c:~$ sudo ./setup-vim.sh 

Enter 1 to configure vim with the Klips repository, any other value to exit.
The up-to-date .vimrc config can be found here: https://github.com/shaunrd0/klips/tree/master/configs
Configuring Vim with this tool will update / upgrade your packages


1

Updating, upgrading required packages...
Hit:1 http://us-east-1.ec2.archive.ubuntu.com/ubuntu bionic InRelease
Hit:2 http://us-east-1.ec2.archive.ubuntu.com/ubuntu bionic-updates InRelease
Hit:3 http://us-east-1.ec2.archive.ubuntu.com/ubuntu bionic-backports InRelease
Hit:4 http://security.ubuntu.com/ubuntu bionic-security InRelease                        
Reading package lists... Done                                                            
Building dependency tree       
Reading state information... Done
32 packages can be upgraded. Run 'apt list --upgradable' to see them.
Reading package lists... Done
Building dependency tree       
Reading state information... Done
Calculating upgrade... Done
The following packages were automatically installed and are no longer required:
  linux-aws-headers-4.15.0-1043 linux-headers-4.15.0-1043-aws linux-image-4.15.0-1043-aws
  linux-modules-4.15.0-1043-aws
Use 'sudo apt autoremove' to remove them.
The following packages will be upgraded:
  bind9-host bsdutils dnsutils dpkg dpkg-dev fdisk libbind9-160 libblkid1 libdns-export1100 libdns1100
  libdpkg-perl libfdisk1 libirs160 libisc-export169 libisc169 libisccc160 libisccfg160 libldap-2.4-2
  libldap-common liblwres160 libmount1 libprocps6 libsmartcols1 libsoup-gnome2.4-1 libsoup2.4-1
  libuuid1 mount procps snapd util-linux uuid-runtime xkb-data
32 upgraded, 0 newly installed, 0 to remove and 0 not upgraded.
Need to get 20.5 MB of archives.
After this operation, 1001 kB of additional disk space will be used.
Reading package lists... Done
Building dependency tree       
Reading state information... Done
git is already the newest version (1:2.17.1-1ubuntu0.4).
vim is already the newest version (2:8.0.1453-1ubuntu1.1).
The following packages were automatically installed and are no longer required:
  linux-aws-headers-4.15.0-1043 linux-headers-4.15.0-1043-aws linux-image-4.15.0-1043-aws
  linux-modules-4.15.0-1043-aws
Use 'sudo apt autoremove' to remove them.
0 upgraded, 0 newly installed, 0 to remove and 0 not upgraded.

Gathering resources from Klips repository..
Cloning into 'temp'...
remote: Enumerating objects: 339, done.
remote: Counting objects: 100% (339/339), done.
remote: Compressing objects: 100% (221/221), done.
remote: Total 339 (delta 135), reused 283 (delta 82), pack-reused 0
Receiving objects: 100% (339/339), 59.76 KiB | 19.92 MiB/s, done.
Resolving deltas: 100% (135/135), done.
mkdir: created directory '/etc/config-vim'
'temp/README.md' -> '/etc/config-vim/README.md'
'temp/configs/' -> '/etc/config-vim/configs'
'temp/configs/.vimrc' -> '/etc/config-vim/configs/.vimrc'
'temp/configs/.vimrc-README' -> '/etc/config-vim/configs/.vimrc-README'
'temp/configs/fail2ban' -> '/etc/config-vim/configs/fail2ban'
'temp/configs/fail2ban/README.md' -> '/etc/config-vim/configs/fail2ban/README.md'
'temp/configs/fail2ban/jail.local' -> '/etc/config-vim/configs/fail2ban/jail.local'
'temp/configs/fail2ban/nginx-nohome.conf' -> '/etc/config-vim/configs/fail2ban/nginx-nohome.conf'
'temp/configs/fail2ban/nginx-noproxy.conf' -> '/etc/config-vim/configs/fail2ban/nginx-noproxy.conf'
'temp/configs/fail2ban/nginx-noscript.conf' -> '/etc/config-vim/configs/fail2ban/nginx-noscript.conf'

Klips configs gathered
See /etc/config-vim/README.md for more information.

mkdir: created directory '/etc/config-vim/backup/'

Backup directory created - /etc/config-vim/backup/
mv: cannot stat '/home/cloud_user/.vimrc': No such file or directory
mv: cannot stat '/etc/skel/.vimrc': No such file or directory
renamed '/usr/share/vim/vimrc' -> '/etc/config-vim/backup/share/vimrc'
renamed '/etc/vim/vimrc' -> '/etc/config-vim/backup/etc/vimrc'
Your local .vimrc configurations have been stashed in /etc/config-vim/backup/

New ~/.vimrc configuration installed.
New /etc/skel/.vimrc configuration installed.
New /etc/vim/vimrc configuration installed.

Removing any previous installations of Pathogen...

Installing Pathogen plugin manager for Vim....

If they don't exist, we will create the following directories:
/usr/share/vim/vimfiles/autoload/    /usr/share/vim/vimfiles/bundle/mkdir: created directory '/usr/share/vim/vimfiles/autoload'
mkdir: created directory '/usr/share/vim/vimfiles/bundle'

Pathogen has been installed! Plugins plugins can now be easily installed.

Removing plugins installed by this tool...
rm: cannot remove '/usr/share/vim/vimfiles/bundle/*': No such file or directory
/usr/share/vim/vimfiles/bundle ~

Installing updated plugins...
Cloning into 'supertab'...
remote: Enumerating objects: 687, done.
remote: Total 687 (delta 0), reused 0 (delta 0), pack-reused 687
Receiving objects: 100% (687/687), 186.15 KiB | 20.68 MiB/s, done.
Resolving deltas: 100% (267/267), done.

Supertab plugin has been installed

Cloning into 'clang_complete'...
remote: Enumerating objects: 2720, done.
remote: Total 2720 (delta 0), reused 0 (delta 0), pack-reused 2720
Receiving objects: 100% (2720/2720), 725.96 KiB | 25.03 MiB/s, done.
Resolving deltas: 100% (1132/1132), done.

Clang Completion plugin has been installed


Vim has been configured with the Klips repository.

Configuration Changes: 
~
Packages Installed / Updated:
- vim, git, clang

Vimrc Settings:
- tabwidth is 2, and set to insert SPACE characters instead of TAB symbols with expandtab
- shiftwidth is 2 so we can compensate for the conflict with default tab settings
- autoindent is on, when moving to a newline vim will indent to the current depth
- syntax highlighting is on
- mouse interaction is enabled when supported by connecting systems
-- https://github.com/shaunrd0/klips/tree/master/configs

Plugin Settings:
- Pathogen vim plugin manager has been installed and .vimrc configured for its use.
-- Install new vim plugins by cloning their repositories into ~/.vim/bundle/
-- https://github.com/tpope/vim-pathogen

- Clang_complete vim plugin has been installed and .vimrc configured for its use.
- Code-completion is enabled with default clang_complete settings
-- https://github.com/xavierd/clang_complete
--If you have issues with Clang_complete library linking / loading, check the directory / commands below - 
cd /usr/lib/x86_64-unknown-linux
ln -s libclang.so.1 libclang.so

- Supertab vim plugin has been installed and .vimrc configured for its use.
- Allows the use of TAB to enable code-completion context menu
-- https://github.com/ervandew/supertab

- Enable nocp
-- Ensures vim is not set to be compatible with older versions of vi
-- Removing this could diable enhancements on some systems
-- :help 'compatible' within vim for more information

- Define backspace scope
-- Ensures that backspace has the permissions to remove all character types

- Custom Keybindings
- The keybind (Ctrl-e <ARROW KEY>) allows switching between split vim windows 
-- Ctrl-w is the default setting, which closes tabbed shells on Chrome OS

- Backups previous vimrc configurations
-- If they were present, previous vim files are stored in /etc/config-vim/backups/
cloud_user@shaunrd03c:~$ 
```

Now just open a file in vim to test things out

