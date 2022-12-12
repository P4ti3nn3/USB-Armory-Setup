#!/bin/bash
read -n 1 -p "Enter when USB switch back and blinking" mainmeinput
filename1='/etc/modules'
filename2='/etc/modprobe.d/usbarmory.conf'
echo "g_ether" >> $filename1
echo "options g_ether use_eem=0 dev_addr=aa:bb:cc:dd:ee:f1 host_addr=aa:bb:cc:dd:ee:f2" >> $filename2
sleep 1
/sbin/ip link set enx1a5589a26942 up
sleep 1
/sbin/ip addr add 10.0.0.2/24 dev enx1a5589a26942
sleep 1
/sbin/iptables -t nat -A POSTROUTING -s 10.0.0.1/32 -o wl2ps0 -j MASQUERADE
sleep 1
echo 1 > /proc/sys/net/ipv4/ip_forward
sleep 1
echo "Network configuration is done"
