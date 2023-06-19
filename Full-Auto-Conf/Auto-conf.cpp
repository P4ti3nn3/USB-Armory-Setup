#include <iostream>
#include <string>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <array>
#include <cstdlib>
#include <iomanip>
#include <sys/wait.h>
#include <fstream>
#include <thread>
#include <cstring>
//black        30         40
//red          31         41
//green        32         42
//yellow       33         43
//blue         34         44
//magenta      35         45
//cyan         36         46
//white        37         47

using namespace std;

//clean command execution
void executeCommandAndWait(const std::string& command) {
    std::string sudoCommand = "sudo " + command;

    FILE* pipe = popen(sudoCommand.c_str(), "r");
    if (!pipe) {
        std::cerr << "Error when command is executed : " << command << std::endl;
        return;
    }

    char buffer[128];
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        std::cout << buffer;  // display command output in realtime
    }

    pclose(pipe);
}

int main(void){
    //start of tool//////////////////////////
    char x;
    std::cout << "Welcome to the Auto-conf tool for USB Armory \033[1;43m\033[1;30mMK II\033[0m"<<endl<<endl;
    std::cout << "\033[1;31m!\33[0mIf you're \033[1;33mRoot\33[0m, press \033[1;32m<ENTER>\33[0m, else \033[1;31m<Ctrl + C>\33[0m :"<<endl;
    getchar();
    std::cout << "\033[1;31m!\33[0mSet the \033[1;33mUSB switch\33[0m on \033[1;33muSd mode\33[0m, then, \033[1;32m<ENTER>\33[0m :"<<endl;
    getchar();

    //as USB/////////////////////////////////
    std::cout<<"\33[1;30m------------------------------------------------------------------\33[0m"<<endl;
    std::cout<<"\33[1;34mSet the Armory as USB...\33[0m"<<endl;
    std::string asUsb = "./.pkg/armory-boot/armory-boot-usb -i ./.pkg/armory-boot/armory-ums.imx";
    executeCommandAndWait(asUsb); //command for as USB
    std::this_thread::sleep_for(std::chrono::seconds(5)); //wait till the end


    
    cout<<"\33[1;36mThe Armory is set as USB.\33[0m"<<endl<<endl;

    //load the image///////////////////////////
    std::cout<<"\33[1;30m------------------------------------------------------------------\33[0m"<<endl;
    std::cout<<"\33[1;34mLoading of the image, please wait...\33[0m"<<endl;
    std::string lImage = "dd if=./.pkg/armory-2023-05-24.raw of=/dev/sdb bs=1M conv=fsync";
    executeCommandAndWait(lImage); //command to load image
    std::this_thread::sleep_for(std::chrono::seconds(5));



    cout<<"\33[1;36mImage loaded.\33[0m"<<endl<<endl;

    //enable internet access////////////////////////
    cout<<"\33[1;30m------------------------------------------------------------------\33[0m"<<endl;
    cout << "\033[1;31m!\33[0mSet back the \033[1;33mUSB switch\33[0m, then, \033[1;32m<ENTER>\33[0m :"<<endl;
    getchar();
    cout<<"\33[1;34mLoading of the network configuration, please wait...\33[0m"<<endl;
    system("/bin/sleep 30");

    system("/sbin/ip link set enx1a5589a26942 up");
    system("/sbin/ip addr add 10.0.0.2/24 dev enx1a5589a26942");
    system("/sbin/iptables -t nat -A POSTROUTING -s 10.0.0.1/32 -o wlp2s0 -j MASQUERADE");
    system("/bin/echo 1 > /proc/sys/net/ipv4/ip_forward");

    cout<<"\33[1;36mNetwork configuration set.\33[0m"<<endl<<endl;

    //access the key//////////////
    cout<<"\33[1;30m------------------------------------------------------------------\33[0m"<<endl;
    cout<<"\33[1;34mEnter the Armory code : \33[0m"<<endl;
    system("/bin/sleep 10");
    system("ssh usbarmory@10.0.0.1");

}

//made by P4ti3nn3
