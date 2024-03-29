# Before starting
This part is a tutorial for automatise the scan of any USB on the armory.

# Prerequisite part I (experimental, skip to part II for real conf.)
Before starting, you need to set the mounting point of your USB.

**You can do this by following this experimental part or with a specific tool [here](https://github.com/P4ti3nn3/USB-Armory-Setup/blob/main/Secured-USB/1-ClamAV/README.md#prerequisite-part-ii).**

First, find your USB key with `sudo fdisk -l` :
   
It will be name `sda` or `sdb`.

After this, create the location with `mkdir /mnt` and `mkdir /mnt/usb`.
    
And then, you can mount your key with `sudo mount /dev/<name of key>1 /mnt/usb`.
    
You can automatise this process by creating two scripts and by adding new rules in `/etc/udev/rules.d` with `nano 90-usb-plug.rules`and `nano 91-usb-unplug.rules` :
    
    <for 90, add the line below>
    SUBSYSTEM=="block", ACTION=="add", KERNELS=="sd[a-z][0-9]", RUN+="/bin/sleep 5", RUN+="/bin/bash /home/usbarmory/usbDev/usbPlug.sh"
    
    <for 91, add the line below>
    SUBSYSTEM=="block", ACTION=="remove", KERNELS=="sd[a-z][0-9]", RUN+="/bin/bash /home/usbarmory/usbDev/usbUnPlug.sh"

Install the "pmount" tool that allow you to mount without root rights with `apt install pmount` and do `chmod a+x /usr/bin/pmount`, `chmod a+x /usr/bin/pumount`, `chmod +s /usr/bin/pmount` and `chmod +s /usr/bin/pumount`.

Then, after `mkdir /home/usbarmory/usbDev`, you can create the two scripts :

`nano /home/usbarmory/usbDev/usbPlug.sh` :

    #!/bin/bash
    /usr/bin/pmount /dev/sd[a-z]1

`nano /home/usbarmory/usbDev/usbUnPlug.sh` :

    #!/bin/bash
    directory_name="^sd[a-zA-Z]1$"
    result=$(ls /media | grep -E $directory_name)
    directory=$result
    /usr/bin/pumount $directory

Do `sudo chmod a+x usbPlug.sh` and `sudo chmod a+x usbUnPlug.sh`.

Then restart udev with `sudo systemctl restart udev` :
    
If after this, it doesn't work, then, in `/lib/systemd/system`, modify the file named `systemd-udevd.service` by replacing the [Service] part with :

    DeviceAllow=block-* rwm
    DeviceAllow=char-* rwm
    Type=notify
    # Note that udev will reset the value internally for its workers
    OOMScoreAdjust=-1000
    Sockets=systemd-udevd-control.socket systemd-udevd-kernel.socket
    Restart=always
    RestartSec=0
    ExecStart=/lib/systemd/systemd-udevd
    ExecReload=udevadm control --reload --timeout 0
    #KillMode=mixed
    #TasksMax=infinity
    PrivateMounts=yes
    ProtectClock=yes
    ProtectHostname=yes
    #MemoryDenyWriteExecute=yes
    #RestrictAddressFamilies=AF_UNIX AF_NETLINK AF_INET AF_INET6
    #RestrictRealtime=yes
    RestrictSUIDSGID=yes
    LockPersonality=yes
    IPAddressDeny=any
    #WatchdogSec=3min

And then in the terminal :

    systemctl daemon-reload
    systemctl restart systemd-udevd.service
    systemctl restart udev


# Prerequisite part II
Another way to process is to install the [usbmount](https://github.com/rbrito/usbmount) tool :

    apt install git
    apt install debhelper build-essential
    mkdir /home/usbarmory/usbmountRepo
    cd /home/usbarmory/usbmountRepo
    git clone https://github.com/rbrito/usbmount
    cd usbmount/
    dpkg-buildpackage -us -uc -b
    cd ../
    dpkg -i usbmount_0.0.24_all.deb
    apt-get install -f

Now when you plug a key, you can access it in `/media/usb`.

# 1) Update/upgrade your USB armory

    apt-get -y update
    
    apt-get -y upgrade
    
    apt-get install software-properties-common build-essential curl -y

# 2) Add a SWAP partition on the Armory
First of all, create the file that is gonna be the SWAP partition :

    #create a file of 2Go
    fallocate -l 2G /swapfile
    
    #allow the goods rights
    chmod 600 /swapfile
    
    #make it a SWAP
    mkswap /swapfile
    swapon /swapfile
    
    #make it the default SWAP
    nano /etc/fstab
    <add the line : > /swapfile none swap defaults 0 0
    
    #use the SWAP when RAM is used over 90%
    nano /etc/sysctl.d/99-sysctl.conf
    <at the end, add the line : > vm.swappiness=10
    
    #apply swappiness
    sysctl -p
    
(For this part, this [article](https://forum.hestiacp.com/t/clamav-on-vps-2gb-ram/3536/3) was realy helpful.)

# 3) Download ClamAv on the USB
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
    
# 4) Create a script
On `/home/usbarmory` execute :

    nano .scanUsb.sh
  
and then enter the following code :

	#!/bin/bash
   	/bin/echo "	   	#############>USB pluged<#############
	   	#                                    #
	   	# wait until the end of the analyse  #
	   	#                                    #
	   	#        analyse in progress         #
	   	#                                    #
	   	#                ...                 #
	   	######################################" | wall
   	content=$(ls -l /home/usbarmory/suspicious)
   	/bin/clamscan -r --move=/home/usbarmory/suspicious /media/usb/

   	if [ "$content" != "$(ls -l /home/usbarmory/suspicious)" ]; then
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


  
Execute `chmod a+x scanUsb.sh` for giving the proper rights to the script and also `mkdir /home/usbarmory/suspicious`.
  
# 5) Automatise the execution of the script when USB is plugged
## A) First way (best way)
In `/home/usbarmory/`, do `mkdir .usbPlug` and `mv .scanUsb ./.usbPlug/`.

In `/etc/usbmount/mount.d` do :

    nano 10_plug
  
and write :

	#!/bin/bash
	/bin/bash /home/usbarmory/.usbPlug/.scanUsb
  
Do `chmod a+x /etc/usbmount/mount.d/10_plug`.
 
Then reboot the Armory :
 
    sudo reboot

Now when a USB is plugged, the Armory will scan it.

## B) Second way
In `/etc/udev/rules.d` do :

     nano 90-usb.rules
  
and write :

	 SUBSYSTEM=="block", ACTION=="add", KERNELS=="sd[a-z][0-9]", RUN+="/bin/sleep 5", RUN+="/home/usbarmory/scanUsb.sh"
  
 In `/etc/udev/udev.conf` delete the `#` for `event_timeout` and add 100000000 after `=`.
 
 Then restart udev :
 
    sudo service udev restart

Now when a USB is plugged, the Armory will scan it.

# 6) Stop auto-start of ClamAv
In some case, ClamAv may auto-start so do `sudo top`, find the PID of Clamscan and then :

	sudo kill -9 <PID>
	
After this you can disable the auto-start with :

	sudo update-rc.d clamav-daemon disable

The configuration is now done.

If you want, you can now continue with some [additional configuration](https://github.com/P4ti3nn3/USB-Armory-Setup/tree/main/Armory-Project).

