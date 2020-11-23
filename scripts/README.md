# Scripts

#### newuser.sh 
 - Script to add new user, run with sudo if you want to configure / allow user to sudo
 - `./adduser` - (Prints help text)
 - `./adduser <name> <userID>` - (Command doesn't need sudo if new user doesn't need sudo)
 - `sudo ./adduser <name> <userID>`
 - `sudo ./adduser jeff 1005` - (Creates jeff user and assign userID to 1005)
 - Follow prompts to configure password / sudo depending on needs of new user 
 - After the user is created, append them to any needed groups with `sudo usermod -aG groupname username` 


#### fix-vbox.sh
 - Script to fix a common issue in vbox VMs
 - Fix for issue where a portion of the VM screen is not clickable
