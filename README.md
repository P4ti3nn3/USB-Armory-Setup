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

## B) Download the armory-ums
[armory-ums.imx](https://github.com/usbarmory/armory-ums/releases)

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

# 5. Acces the key
Set back the switch on the internal storage.

Connect the key via ssh:

    ssh usbarmory@10.0.0.1
    
with the password "usbarmory".
    
# 6. Enable an internet access
