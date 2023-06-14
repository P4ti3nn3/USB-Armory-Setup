# Before starting
**In this part I give you a auto-configuration script for your Armory with all necessary setting for making a USB firewalling interface.**

# 1. Download the auto-conf folder
You can find the bash script [here](https://github.com/P4ti3nn3/USB-Armory-Setup/releases/tag/Auto-Conf) and you can download it.

Uncompress it :

    sudo tar -xzvf auto-conf.tar.gz

# 2. Execute and follow the instructions
Execute this script in root by doing :

    sudo ./auto-conf/Auto-conf

There is some instructions that showing up. You need to pay attention to each one to configure your Armory properly.

# 3. Activation of USB Firewalling
On the key with `sudo nano /etc/usbmount/mount.d/10_plug`, you can delete the `#` before the conf you want.

Also, with `sudo nano /etc/usbmount/umount.d/10_unplug`, you can delete the `#` before the conf.

Now, with `sudo restart`, restart your Armory.

# 4. How does it works
Now, when you need to check the content of a USB key, you can plug your Armory on your device.

After this, with `ssh usbarmory@10.0.0.1` you can access it.

When the USB Firewalling is enable, if you plug a USB key on the Armory, it will be scanned.

If there is bad files, they will be put in `/home/usbarmory/suspicious` and you can access other file from the key in `/home/usbarmory/usbContent`.

If you want to understand how does it work, I invite you to explore the full tutorial on this Git starting by the [Secured USB part](https://github.com/P4ti3nn3/USB-Armory-Setup/tree/main/Secured-USB).
