# Before starting
This part is a tutorial for automatise the scan of any USB on the armory

# Prerequisite
Before starting, you need to set the mounting point of your USB.

First, find your USB key with:

    fdisk -l
    
It will be name "sda" or "sdb"

After this, create the location witch:

    mkdir /mnt
    mkdir /mnt/usb
    
And then, you can mount your key:

    sudo mount /dev/<name of key>1 /mnt/usb
    
You can automatise this process by adding a new rule in "/etc/udev/rules.d":

    nano 90-usb.rules
    
    <add the line below>
    SUBSYSTEM=="block", ACTION=="add", KERNELS=="sd[!0-9]", RUN+="/usr/bin/mount /dev/sd[!0-9]1 /mnt/usb"
    
Then restart udev:

    sudo systemctl restart udev
    
If after this, it doesn't work, then, in `/lib/systemd/system`, modify the file named `systemd-udevd.service` by replacing the [Service] part with :



# 1) Update/upgrade your USB armory

    apt-get -y update
    
    apt-get -y upgrade
    
    apt-get install software-properties-common build-essential curl -y

# 2) Add a SWAP partition on the Armory
First of all, create the file that is gonna be the SWAP part. :

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
Follow this commands:

    #become root
    sudo su -
    
    #dowload ClamAv daemon
    apt-get install clamav clamav-daemon
    
    #start the daemon
    systemctl start clamav-daemon

check that it works:

    #check the status
    systemctl status clamav-daemon
    
If status is failed, else skip this part:

go to :

    database.clamav.net/main.cvd
    database.clamav.net/daily.cvd
    
or download it [here](https://github.com/P4ti3nn3/USB-Armory-Setup/releases/tag/cvd).
    
Put this two files in /var/lib/clamav and restart

    systemctl stop clamav-daemon
    
    systemctl start clamav-daemon
    
# 4) Create a script
On /home/usbarmory execute :

    nano scan.sh
  
and then enter the following code :

    #!/bin/bash
    clamscan /mnt/usb/<name of usb>
  
Execute the following line for giving the proper rights to the script

    chmod 755 scan.sh
  
# 5) Automatise the execution of the script when USB is plugged
In /etc/udev/rules.d do :

    nano 90-usb.rules
  
and write :

    SUBSYSTEM=="block", ACTION=="add", KERNELS=="sd[!0-9]", RUN+="/home/usbarmory/scan.sh"
  
 Then restart udev :
 
    sudo service udev restart

Now when a USB is plugged, the Armory will scan it.

