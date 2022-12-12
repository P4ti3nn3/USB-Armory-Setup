#!/bin/bash
read -n 1 -p "If root <Enter>, else <Ctrl+C>" mainmeinput
sudo chmod 700 ./confFiles/1AsUSB.sh
./confFiles/1AsUSB.sh
sudo chmod 700 ./confFiles/2LoadImage.sh
./confFiles/2LoadImage.sh
sudo chmod 700 ./confFiles/3NetwConf.sh
./confFiles/3NetwConf.sh
sudo chmod 700 ./confFiles/4Access.sh
./confFiles/4Access.sh
