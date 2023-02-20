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

## 1 - Created from host to /home
Forbiden because in read only

## 2 - Deleted from host to /home
`rm` work. From the host, the update is efficient directly but from the Armory, we need to wait for 30s.

## 3 - Execution from host to /home
For a script that create a file it's forbiden because in read only.
For a script that reboot, it reboot the host.


