**(This part is dedicated to the auto configuration of the Armory Mk II by using some script)**

# First part : Instalation of base configuration from the PC

## I - Installation of the tool

First of all, you need to install the tool [here](https://github.com/P4ti3nn3/USB-Armory-Setup/releases/tag/Final-conf), it will allow you to push the base image to the Armory.

## II - Run the tool

First, uncompress the tool and then as **root** move into the folder : `cd ./auto-conf-c`. You can now run the tool : `./Auto-conf`.

## III - Follow the steps

If it's the first time you run the tool, answer `yes` to `Are the needed packages allready installed ?`.

Then sellect `complete installation` for the classic configuration.

Wait a few minutes and then you can follow the nexts steps.

At the step `Loading of the armory utils`, if the message `connection refused` show up, re run the tool but select `Armory utils sharing` and answer `yes` to the message.

You can now access the key for the next part.

# Second part : secured configuration

Now on the Armory do :

    sudo su -
    cd /home/usbarmory/armory-utils
    ./step1

It will reboot the Armory so after the reboot, reconnect to it and do :

    sudo su -
    cd /home/usbarmory/armory-utils
    ./step2

It will reboot the Armory so after the reboot, reconnect to it and do :

    sudo su -
    cd /home/usbarmory/armory-utils
    ./step3

It will take a few time but a menu will show up, the base configuration is `complete security` so select it, it will reboot the Armory so after the reboot, reconnect to it and do :

    sudo su -
    cd /home/usbarmory/.usbmountRepo
    ./step4

When it's over, the Armory is ready to use, you can test it by pluging a usb on it. 
