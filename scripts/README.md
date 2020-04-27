### scripts
adduser.sh - Script to add new user, run with sudo if you want to configure / allow user to sudo
 - `./adduser` - (Print help text)
 - `./adduser <name> <userID>` - (Don't need sudo if new user doesn't need it)
 - `sudo ./adduser <name> <userID>`
 - `sudo ./adduser jeff 1005` - (Create jeff user and assign userID to 1005)
 - Follow prompts to configure password / sudo depending on needs of new user 

