# Before starting
This repository is an unofficial tutorial for helping to setup an [USB Armory Mk II](https://github.com/usbarmory/usbarmory/wiki/Mk-II-Introduction).

# 1. Download the image
Debian base image [here](https://github.com/usbarmory/usbarmory/wiki/Available-images).

Uncompress it :

    sudo xz -d <image.xz>

# 2. Get all prerequies

    bc binfmt-support bzip2 fakeroot gcc gcc-arm-linux-gnueabihf git gnupg make parted rsync qemu-user-static wget xz-utils zip debootstrap sudo dirmngr bison flex libssl-dev kmod
    
# 3. Acces the USB Armory as a storage device
## A) Set the switch on uSd without any uSd card pluged in.
![image](https://user-images.githubusercontent.com/115619908/204819286-eadf91fa-6218-4c4e-9a7e-ac1a31a585d9.png)


## B) Download the armory-ums
The [armory-ums.imx](https://github.com/usbarmory/armory-ums/releases) file.

## C) Set up the armory-boot tool
git clone the armory-boot tool and compil it:

    git clone https://github.com/usbarmory/armory-boot
    cd armory-boot && make armory-boot-usb
    
## D) Finish the process
Move the .imx file into the armory-boot repository.

Execute the command below:

    sudo armory-boot-usb -i armory-ums.imx
    
# 4. Load the image on the USB Armory

    sudo dd if=<image.raw> of=/dev/<sdX> bs=1M conv=fsync

It can take a few minutes.

Set back the switch on the internal storage.

# 5. Enable an internet access
On your host:

In the file /etc/modules, add the line:

    g_ether
    
In the file /etc/modprobe.d/usbarmory.conf, add the line:

    options g_ether use_eem=0 dev_addr=aa:bb:cc:dd:ee:f1 host_addr=aa:bb:cc:dd:ee:f2
    
You can now, in a terminal, execute this commands with your conf (do ip addr for information about your conf):

    # bring the USB virtual Ethernet interface up
    /sbin/ip link set <ethernet interface of the USB> up
    
    # set the host IP address
    /sbin/ip addr add 10.0.0.2/24 dev <ethernet interface of the USB>
    
    # enable masquerading for outgoing connections towards wireless interface
    /sbin/iptables -t nat -A POSTROUTING -s 10.0.0.1/32 -o <wireless interface of the host> -j MASQUERADE
    
    # enable IP forwarding
    echo 1 > /proc/sys/net/ipv4/ip_forward


# 6. Acces the key
Connect the key via ssh:

    ssh usbarmory@10.0.0.1
    
with the password "usbarmory".

If a message pop up, follow the instructions.

Now on the USB, ping internet for confirm that the conf is working:

    ping 8.8.8.8
    
If it works, the base configuration is over, else, you may have made a mistake.

# 7. Scan an USB when it's plug
## A) Update/upgrade your USB

    apt-get -y update
    
    apt-get -y upgrade
    
    apt-get install software-properties-common build-essential curl -y

## B) Download ClamAv on the USB
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
    
## C) Create a script

    
   
    
        
    

