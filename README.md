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

    mv <file.imx> <armory-boot location>

Execute the command below:

    sudo armory-boot-usb -i armory-ums.imx
    
# 4. Load the image on the USB Armory
With the command :

    fdisk -l

locate the USB armory and replace the sdX below with it :

    sudo dd if=<image.raw> of=/dev/<sdX> bs=1M conv=fsync

It can take a few minutes.

Set back the switch on the internal storage.

![image](https://user-images.githubusercontent.com/115619908/204820264-d00449f2-79b2-4acd-8f75-162b4ad24212.png)

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
    
If it works, the base configuration is over, else restart your network or check your configuration.

# 7. Resize the size
While on the Armory, do :
    
    ls /dev/mmcblk*
    
You should have a result like "/dev/mmcblk1" so you can do :

    fdisk /dev/mmcblk1
    
Then enter "p" and keep in mind the start of the partition.

Now, enter this in order : 

    d
    n
    <enter>
    <start of the partition>
    <enter>
    yes
    w
    
It's over, the storage has been resized.


   
    
        
    

