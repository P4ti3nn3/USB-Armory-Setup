**DISCLAIMER : ITS AN EXPERIMENTAL PART AND IT'S NOT FINISHED**

# Foreword
This part is dedicated to the design and the application of severals requierments for the USB armory.

![USB-Armory](https://user-images.githubusercontent.com/115619908/215988459-6f9821be-21ea-47f6-9442-b856f0a5ce15.png)

# I - Requirements
**Sanity check** : The USB Armory shall verify if the USB plugged isn't infected.

**File transfer** : The USB Armory shall transfer file to the computer to witch it's plugged.

**Traffic control** : The USB Armory shall block all forbiden download from the computer.

# II - Sanity check
This part reffer to this [section](https://github.com/P4ti3nn3/USB-Armory-Setup/tree/main/Secured-USB/1-ClamAV) of the repository.

# III - File transfer
Soon...

# IV - Traffic control
For the moment, the configuration allow the main computer to access the key's files but the reverse scenario isn't possible.
![USB-Armory-Traffic](https://user-images.githubusercontent.com/115619908/216015933-190c2bb5-0e16-41ce-8a9f-a4c842d50042.png)

This configuration got the advantage to block any export from the main PC.

# (V - Note and observation)
**This part is dedicated to contain all advencements and observation concerning the project**

When the Armory is considerated as a storage device, there is different type of behavior for the file:

## 1 - Creating from host to /home
Forbiden because in read only

## 2 - Deleting from host to /home
`rm` work. From the host, the update is efficient directly but from the Armory, we need to wait for 30s.

## 3 - Executing from host to /home
For a script that create a file it's forbiden because in read only.

For a script that reboot, it reboot the host.

## 4 - Creating from armory
From armory, it's efficient directly but from the host there is two case. 

If you havn't opened the filesystem before, you need to wait for 30s, else, it need a reboot for see the new file. 

## 5 - Deleting from armory
From armory, it's efficient directly but from the host there is two case. 

If you havn't opened the filesystem before, you need to wait for 30s, else, it need a reboot for unsee the new file. 

## 6 - Read files

<img width="476" alt="paramUsb" src="https://user-images.githubusercontent.com/115619908/220124169-2ff3a3f9-bc5e-4472-940e-bb42c7a872b1.png">

## Idea for improving
As we see it before, we can't download file from a USB that is plugged to the USB Armory from the host.

An idea for bypass this is to create a repository on the Armory where after the scan we can put all the files we want to download and delete it after unplugging the key.

## Improvement setup
Create a new repository with `mkdir /home/usbarmory/usbContent`.

Create a new script with `nano usbTransfer.sh` and add this content into it:

    #!/bin/bash
    /bin/cp -r /media/usb0 /home/usbarmory/usbContent/
    
Make it executable with `sudo chmod a+x usbTransfer.sh` and move it into the same repository as your USB Scanner.

You can now create a main plug file with `nano usbPlugMain.sh` and add:

    #!/bin/bash
    /bin/bash /home/usbarmory/usbPlug/scanUsb.sh && /bin/bash /home/usbarmory/usbPlug/usbTransfer.sh
    
Make it executable with `sudo chmod a+x usbPlugMain.sh`.

Now you can create a last script with `nano mainUnPlug.sh` and add:

    #!/bin/bash
    /bin/rm /home/usbarmory/usbContent/usb0

In `/etc/usbmount/mount.d` you can create `10_usb_rules` and add this :

    #!/bin/bash
    /bin/bash /home/usbarmory/usbPlug/mainPlug.sh
    
    
    
## News
Curently, I'm working on a new problem. In fact, now udev doesn't wait for UsbMount to copy the file so it doesn't copy anything. It's realy strange because it append without any reasons.

Need to dig in [this](https://askubuntu.com/questions/673650/copying-a-file-from-a-usb-storage-if-it-exist-with-udev-rules).

**Update :** it's the solution.

