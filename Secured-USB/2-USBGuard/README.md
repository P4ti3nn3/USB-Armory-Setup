# Before starting
This solution is used for allow only known USB device.

# 1) Install on the Armory the USBGuard app
Execute the command :

    apt install usbguard
  
# 2) Generate the rules policy
Execute the command :
    
    usbguard generate-policy > rules.conf
    
and check if the configuration is matching with your wish :

    nano rules.conf
    
You can add other allowed devices by adding the line :

    allow id <id of your device>
    
You can find the ID of your device with the command :

    lsusb
    
# 3) Pull the policy on the Armory
Execute the commands :

    sudo install -m 0600 -o root -g root rules.conf /etc/usbguard/rules.conf
    
    sudo systemctl restart usbguard
    
# 4) Test that it's working and adapt
Plug any unallowed usb and check if you can access to it.

If you want to modify the policy, execute the command :
    
    sudo nano /etc/usbguard/rules.conf
    
And then :

    sudo systemctl restart usbguard
    
For more personalized rules, the Github of USBGuard is available [here](https://usbguard.github.io/documentation/rule-language.html)
