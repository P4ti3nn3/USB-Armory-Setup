# Before starting
This part is a tutorial for automatise the scan of any USB on the armory

# 1) Update/upgrade your USB

    apt-get -y update
    
    apt-get -y upgrade
    
    apt-get install software-properties-common build-essential curl -y

# 2) Download ClamAv on the USB
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
    
# 3) Create a script
On /home/usbarmory execute :

    nano scan.sh
  
and then enter the following code :

    #!/bin/bash
    clamscan /dev/sdb
  
Execute the following line for giving the proper rights to the script

    chmod 755 scan.sh
  
# 4) Automatise the execution of the script when USB is plugged
In /etc/udev/rules.d do :

    nano 90-usb.rules
  
and write :

    ACTION=="add", ATTRS{idVendor}=="****", ATTRS{idProduct}=="****", RUN+="/home/usbarmory/scan.sh"
  
 Then restart udev :
 
    sudo service udev restart

Now when a USB is plugged, the Armory will scan it.
