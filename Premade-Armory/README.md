# Before starting
In this part I give you a pre-compilated image for your Armory with all necessary setting for making a USB firewalling interface.

# 1. Download the pre-compilated image
Armory pre-compilated image [here](https://google.com).

Uncompress it :

    sudo tar -xzvf <image.tar.gz>

# 2. Get all prerequies
On your device with `apt get`, get all this packages:

    bc binfmt-support bzip2 fakeroot gcc gcc-arm-linux-gnueabihf git gnupg make parted rsync qemu-user-static wget xz-utils zip debootstrap sudo dirmngr bison flex libssl-dev kmod
    
# 3. Acces the USB Armory as a storage device
## A) Set the switch on uSd without any uSd card pluged in.
![uSd](https://user-images.githubusercontent.com/115619908/207088072-c9b82a70-e9fe-4610-a2cc-1eaa0ef9ad35.png)


## B) Download the armory-ums
The [armory-ums.imx](https://github.com/usbarmory/armory-ums/releases) file.

## C) Set up the armory-boot tool
`git clone` the armory-boot tool and compil it:

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

![internal](https://user-images.githubusercontent.com/115619908/207088122-b42e1c15-9156-49a5-be71-34e409257af8.png)

# 5. Enable an internet access    
You can now, in a terminal, execute this commands with your conf (do `ip addr` for information about your conf):

    # bring the USB virtual Ethernet interface up
    /sbin/ip link set <ethernet interface of the USB> up
    
    # set the host IP address
    /sbin/ip addr add 10.0.0.2/24 dev <ethernet interface of the USB>
    
    # enable masquerading for outgoing connections towards wireless interface
    /sbin/iptables -t nat -A POSTROUTING -s 10.0.0.1/32 -o <wireless interface of the host> -j MASQUERADE
    
    # enable IP forwarding
    echo 1 > /proc/sys/net/ipv4/ip_forward
    
For exemple, mine is :
    
    /sbin/ip link set enx1a5589a26942 up
    /sbin/ip addr add 10.0.0.2/24 dev enx1a5589a26942
    /sbin/iptables -t nat -A POSTROUTING -s 10.0.0.1/32 -o wlp2s0 -j MASQUERADE
    echo 1 > /proc/sys/net/ipv4/ip_forward
    
And ifconfig -a show :

![Capture d’écran_2022-12-05_14-22-19](https://user-images.githubusercontent.com/115619908/205647771-f5528805-8591-4f2b-890d-3fb05f38901b.png)



# 6. Acces the key
Unplug and the plug the key.

Connect the key via ssh:

    ssh usbarmory@10.0.0.1
    
with the password "usbarmory".

If a message pop up, follow the instructions.

Now on the USB, ping internet for confirm that the conf is working:

    ping 8.8.8.8
    
If it doesn't work, verify your configuration with the [point 5](https://github.com/P4ti3nn3/USB-Armory-Setup/tree/main/Premade-Armory#5-enable-an-internet-access).

# 7. Activation of USB Firewalling
On the key with `sudo nano /etc/usbmount/mount.d/10*`, you can delete the `#` before the conf you want.

Also, with `sudo nano /etc/usbmount/umount.d/10*`, you can delete the `#` before the conf.

Now, with `sudo restart`, restart your Armory.

# 8. How does it works
Now, when you need to check the content of a USB key, you can plug your Armory on your device.

After this, with `ssh usbarmory@10.0.0.1` you can access it.

When the USB Firewalling is enable, if you plug a USB key on the Armory, it will be scanned.

If there is bad files, they will be put in `/home/usbarmory/suspicious` and you can access other file from the key in `/home/usbarmory/usbContent`.

If you want to understand how does it work, I invite you to explore the full tutorial on this Git.
