#!/bin/bash
sudo dd if=../usbarmory-mark-two-emmc-debian_bullseye-base_image-20221114.raw of=/dev/sdb bs=1M conv=fsync
echo "Image Loaded"
sleep 1
