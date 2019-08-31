### Scripts

I write these scripts for my own use, and you may need to tweak them slightly to suit your needs. 

Never run a script you can't read or understand. Comments can be found in the scripts, usually explaining them block-by-block. Below is my personal use cases for the scripts, to provide further insight into how I use them and how they might be useful to you.

#### adduser.sh

This script was made on Ubuntu when creating a few users across multiple hosts. Syntax requires at least 2 arguments when running the script, otherwise help text will be output warning of correct usage and available options. The script can be used to configure sudo on a new user if the script itself is ran with sudo. Otherwise, creating a default user with or without a password is possible without sudo. If the script is ran on an existing user or a userID that is already in use is passed, no changes will happen in user-creation but you may still allow the user to sudo and change their password. 

Syntax - 

./adduser (Help text)
./adduser jeff 1005 (Create user jeff with userID 1005, can't configure sudo, prompt for possible password creation)

sudo ./adduser (Help text)
sudo ./adduser jeffy 1010 (Create user jeffy with userID 1010, can configure sudo, possible password creation)

Didn't configure sudo, and don't want to do so manually? Re-run the script on the existing user just as above, and accept the prompt for sudo configuration.
sudo ./adduser jeff 1005 (User creation will fail, follow prompts to configure sudo and / or reset user password)

#### cmake-build.sh

I usually run this script within whatever directory I'm working in, hence the infinite loop, I leave the script running until I'm done with my work and move to a new directory / cmake project.


#### setup-vim.sh

To use this script, copy it to a safe directory where we can store previous / future vimrc configurations and run it as a user with sudo privelages. See below for example commands and output.

```bash

cloud_user@shaunrd02c:~$ pwd
/home/cloud_user
cloud_user@shaunrd02c:~$ ls
klips
cloud_user@shaunrd02c:~$ cp klips/scripts/setup-vim.sh .
cloud_user@shaunrd02c:~$ ./setup-vim.sh 

Enter 1 to configure vim with the Klips repository, any other value to exit.
The up-to-date .vimrc config can be found here: https://github.com/shaunrd0/klips/tree/master/configs
Configuring Vim with this tool will update / upgrade your packages

1

Updating, upgrading required packages...
... ( Reduced output ) ...
remote: Compressing objects: 100% (58/58), done.
remote: Total 92 (delta 28), reused 79 (delta 18), pack-reused 0
Unpacking objects: 100% (92/92), done.
mkdir: created directory 'config-vim'
renamed 'temp/README.md' -> 'config-vim/README.md'

Klips config files updatedmkdir: created directory 'config-vim/backup/'

Backup directory created - /home/cloud_user/config-vim/backup/
renamed '/home/cloud_user/.vimrc' -> 'config-vim/backup/.vimrc'
Your local .vimrc has been stashed in /home/cloud_user/config-vim/backup/

New ~/.vimrc configuration installed.

Removing any previous installations of Pathogen...

Installing Pathogen plugin manager for Vim....

Pathogen has been installed! Plugins plugins can now be easily installed.

Removing plugins installed by this tool...

Installing updated plugins...
Cloning into 'supertab'...
remote: Enumerating objects: 687, done.
remote: Total 687 (delta 0), reused 0 (delta 0), pack-reused 687
Receiving objects: 100% (687/687), 186.15 KiB | 2.36 MiB/s, done.
Resolving deltas: 100% (267/267), done.

Supertab plugin has been installed

Cloning into 'clang_complete'...
remote: Enumerating objects: 2720, done.
remote: Total 2720 (delta 0), reused 0 (delta 0), pack-reused 2720
Receiving objects: 100% (2720/2720), 727.21 KiB | 2.04 MiB/s, done.
Resolving deltas: 100% (1132/1132), done.

Clang Completion plugin has been installed


Vim has been configured with the Klips repository.

Configuration Changes: 
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

- Supertab vim plugin has been installed and .vimrc configured for its use.
- Allows the use of TAB to enable code-completion context menu
-- https://github.com/ervandew/supertab

cloud_user@shaunrd02c:~$ ls
config-vim  klips  setup-vim.sh
cloud_user@shaunrd02c:~$ ls -R config-vim/
config-vim/:
README.md  backup  configs

config-vim/backup:

config-vim/configs:
cloud_user@shaunrd02c:~$

```

Now just open a file in vim to test things out

