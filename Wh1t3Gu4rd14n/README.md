# Before starting
This part is the adaptation of the Armory one to make it compliance with any Debian system and transform it into a white station (Station Blanche).

# Prerequisite
First of all, on terminal we need to create a repository dedicated to the White Guardian :

    mkdir /home/user/whiteguardian

Then we need to install the [usbmount](https://github.com/rbrito/usbmount) tool :

    apt install git
    apt install debhelper build-essential
    mkdir /home/user/usbmountRepo
    cd /home/user/usbmountRepo
    git clone https://github.com/rbrito/usbmount
    cd usbmount/
    dpkg-buildpackage -us -uc -b
    cd ../
    dpkg -i usbmount_0.0.24_all.deb
    apt-get install -f

Now when you plug a key, you can access it in `/media/usb`.

# 1) Update/upgrade your system : 

    apt-get -y update
    
    apt-get -y upgrade
    
    apt-get install software-properties-common build-essential curl -y


# 2) Download ClamAv on the system
Follow this commands :

    #become root
    sudo su -
    
    #dowload ClamAv daemon
    apt-get install clamav clamav-daemon
    
    #start the daemon
    systemctl start clamav-daemon

check that it works :

    #check the status
    systemctl status clamav-daemon
    
If status is failed, else skip this part :

go to :

    database.clamav.net/main.cvd
    database.clamav.net/daily.cvd
    
or download it [here](https://github.com/P4ti3nn3/USB-Armory-Setup/releases/tag/cvd).
    
Put this two files in `/var/lib/clamav` and then restart :

    systemctl stop clamav-daemon
    
    systemctl start clamav-daemon
    
# 3) Create a script
On `/home/user/whiteguardian` execute :

    nano .scanUsb.sh
  
and then enter the following code :

	#!/bin/bash
   	/bin/echo "	#############>USB pluged<#############
	   	#                                    #
	   	# wait until the end of the analyse  #
	   	#                                    #
	   	#        analyse in progress         #
	   	#                                    #
	   	#                ...                 #
	   	######################################" | wall
   	content=$(ls -l /home/user/white/guardian/suspicious)
   	/bin/clamscan -i -r -v --move=/home/user/whiteguardian/suspicious /media/usb*/ | tee /home/user/clamscan.log

   	if [ "$content" != "$(ls -l /home/user/white/guardian/suspicious)" ]; then
	   	/bin/echo "	          /analyse completed\          
	
	   	##############>Result<################
	   	#                                    #
	   	#            /!\WARNING/!\           #
	   	#     Suspicious file(s) detected    #
	   	#  check /home/usbarmory/suspicious  #
	   	#                                    #
	   	######################################" | wall

   	else
	   	/bin/echo "               /analyse completed\          

	   	##############>Result<################
	   	#                                    #
	   	#         All files seems ok.        #
	   	#                                    #
	   	######################################" | wall
   	fi


  
Execute `chmod a+x .scanUsb.sh` for giving the proper rights to the script and also `mkdir /home/user/whiteguardian/suspicious`.
  
# 4) Automatise the execution of the script when USB is plugged
In `/home/user/whiteguardian`, do `mkdir .usbPlug` and `mv .scanUsb ./.usbPlug/`.

In `/etc/usbmount/mount.d` do :

    nano 10_plug
  
and write :

	#!/bin/bash
	/bin/bash /home/user/whiteguardian/.usbPlug/.scanUsb.sh
  
Do `chmod a+x /etc/usbmount/mount.d/10_plug`.
 
Then reboot the system :
 
    sudo reboot

Now when a USB is plugged, the guardian will scan it.

The Scan configuration is now done.



