##################################################################################
# A fix for a common issue found in virtual box                                   #
# Corrects unclickable portions of the screen within the VM                       #
#                                                                                 #
# https://forums.linuxmint.com/viewtopic.php?t=247850                             #
# https://askubuntu.com/questions/1014172/virtualbox-unresponsive-area-on-desktop #
##################################################################################
# fix-vbox.sh

ps aux www |grep 'VBoxClient --draganddrop' | awk '{print $2}' | xargs kill

