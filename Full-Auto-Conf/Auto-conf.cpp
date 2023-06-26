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
#include <regex>
//black        30         40
//red          31         41
//green        32         42
//yellow       33         43
//blue         34         44
//magenta      35         45
//cyan         36         46
//white        37         47



using namespace std;

//////////////////////////////////////////////////////////////////
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

//////////////////////////////////////////////////////////////////
//search for USB Armory
string searchPeriph() {
    std::string command = "sudo fdisk -l";
    std::string result;

    //////////////////////////////////////////////////////////////////
    // Command and storage
    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) {
        std::cerr << "Error when command is executed : " << std::endl;
        return "";
    }

    const int buffer_size = 128;
    char buffer[buffer_size];
    while (fgets(buffer, buffer_size, pipe) != nullptr) {
        result += buffer;
    }

    pclose(pipe);

    //////////////////////////////////////////////////////////////////
    // Regex
    std::regex regex("/dev/sd[b-z]");

    //////////////////////////////////////////////////////////////////
    // Search for regex
    std::smatch match;
    if (std::regex_search(result, match, regex)) {
        std::string device = match.str();
        std::cout << "\33[1;32mDevice found : \33[0m" << device << std::endl;
        std::string storedDevice = device;
        return storedDevice;

    } else {
        std::cerr << "\33[1;31mDevice not found.\33[0m" << std::endl;
    }
    return "";
}

//////////////////////////////////////////////////////////////////
//install needed packages
void neededPack(){
    std::string a = "apt install bc -y";
    std::string b = "apt install binfmt-support -y";
    std::string c = "apt install bzip2 -y";
    std::string d = "apt install fakeroot -y";
    std::string e = "apt install gcc -y";
    std::string f = "apt install gcc-arm-linux-gnueabihf -y";
    std::string g = "apt install git -y";
    std::string h = "apt install gnupg -y";
    std::string i = "apt install make -y";
    std::string j = "apt install parted -y";
    std::string k = "apt install rsync -y";
    std::string l = "apt install qemu-user-static -y";
    std::string m = "apt install wget -y";
    std::string n = "apt install xz-utils -y";
    std::string o = "apt install zip -y";
    std::string p = "apt install debootstrap -y";
    std::string q = "apt install sudo -y";
    std::string r = "apt install dirmngr -y";
    std::string s = "apt install bison -y";
    std::string t = "apt install flex -y";
    std::string u = "apt install libssl-dev -y";
    std::string v = "apt install kmod -y";
    std::string w = "apt install pv -y"; 
    executeCommandAndWait(a);
    std::this_thread::sleep_for(std::chrono::seconds(1)); //wait till the end
    executeCommandAndWait(b);
    std::this_thread::sleep_for(std::chrono::seconds(1)); //wait till the end
    executeCommandAndWait(c);
    std::this_thread::sleep_for(std::chrono::seconds(1)); //wait till the end
    executeCommandAndWait(d);
    std::this_thread::sleep_for(std::chrono::seconds(1)); //wait till the end
    executeCommandAndWait(e);
    std::this_thread::sleep_for(std::chrono::seconds(1)); //wait till the end
    executeCommandAndWait(f);
    std::this_thread::sleep_for(std::chrono::seconds(1)); //wait till the end
    executeCommandAndWait(g);
    std::this_thread::sleep_for(std::chrono::seconds(1)); //wait till the end
    executeCommandAndWait(h);
    std::this_thread::sleep_for(std::chrono::seconds(1)); //wait till the end
    executeCommandAndWait(i);
    std::this_thread::sleep_for(std::chrono::seconds(1)); //wait till the end
    executeCommandAndWait(j);
    std::this_thread::sleep_for(std::chrono::seconds(1)); //wait till the end
    executeCommandAndWait(k);
    std::this_thread::sleep_for(std::chrono::seconds(1)); //wait till the end
    executeCommandAndWait(l);
    std::this_thread::sleep_for(std::chrono::seconds(1)); //wait till the end
    executeCommandAndWait(m);
    std::this_thread::sleep_for(std::chrono::seconds(1)); //wait till the end
    executeCommandAndWait(n);
    std::this_thread::sleep_for(std::chrono::seconds(1)); //wait till the end
    executeCommandAndWait(o);
    std::this_thread::sleep_for(std::chrono::seconds(1)); //wait till the end
    executeCommandAndWait(p);
    std::this_thread::sleep_for(std::chrono::seconds(1)); //wait till the end
    executeCommandAndWait(q);
    std::this_thread::sleep_for(std::chrono::seconds(1)); //wait till the end
    executeCommandAndWait(r);
    std::this_thread::sleep_for(std::chrono::seconds(1)); //wait till the end
    executeCommandAndWait(s);
    std::this_thread::sleep_for(std::chrono::seconds(1)); //wait till the end
    executeCommandAndWait(t);
    std::this_thread::sleep_for(std::chrono::seconds(1)); //wait till the end
    executeCommandAndWait(u);
    std::this_thread::sleep_for(std::chrono::seconds(1)); //wait till the end
    executeCommandAndWait(v);
    std::this_thread::sleep_for(std::chrono::seconds(1)); //wait till the end
    executeCommandAndWait(w);
    std::this_thread::sleep_for(std::chrono::seconds(1)); //wait till the end
}

//////////////////////////////////////////////////////////////////
//main part of the code
int main(void){
    //////////////////////////////////////////////////////////////////
    //start of tool
    char x;
    std::cout << "Welcome to the Auto-conf tool for USB Armory \033[1;43m\033[1;30mMK II\033[0m"<<endl<<endl;
    std::cout << "\033[1;31m!\33[0mIf you're \033[1;33mRoot\33[0m, press \033[1;32m<ENTER>\33[0m, else \033[1;31m<Ctrl + C>\33[0m :"<<endl;
    getchar();
    std::cout << "\033[1;31m!\33[0mSet the \033[1;33mUSB switch\33[0m on \033[1;33muSd mode\33[0m, then, \033[1;32m<ENTER>\33[0m :"<<endl;
    getchar();

    //////////////////////////////////////////////////////////////////
    //install needed packages
    std::cout<<"\33[1;30m------------------------------------------------------------------\33[0m"<<endl;
    std::cout<<"\33[1;34mInstall of needed packages ...\33[0m"<<endl;
    neededPack();
    cout<<"\33[1;36mAll packages are installed.\33[0m"<<endl<<endl;

    //////////////////////////////////////////////////////////////////
    //as USB
    std::cout<<"\33[1;30m------------------------------------------------------------------\33[0m"<<endl;
    std::cout<<"\33[1;34mSet the Armory as USB...\33[0m"<<endl;
    std::string asUsb = "./.pkg/armory-boot/armory-boot-usb -i ./.pkg/armory-boot/armory-ums.imx";
    executeCommandAndWait(asUsb); //command for as USB
    std::this_thread::sleep_for(std::chrono::seconds(5)); //wait till the end
    string sdx = searchPeriph();
    cout<<"\33[1;36mThe Armory is set as USB.\33[0m"<<endl<<endl;

    //////////////////////////////////////////////////////////////////
    //load the image
    std::cout<<"\33[1;30m------------------------------------------------------------------\33[0m"<<endl;
    std::cout<<"\33[1;34mLoading of the image, please wait...\33[0m"<<endl;
    std::string start = "pv -tpreb ./.pkg/armory-2023-05-24.raw | dd of=";
    std::string midle = sdx;
    std::string end = " bs=1M conv=fsync";
    std::string lImage = start+midle+end;
    executeCommandAndWait(lImage); //command to load image
    std::this_thread::sleep_for(std::chrono::seconds(5));
    cout<<"\33[1;36mImage loaded.\33[0m"<<endl<<endl;

    //////////////////////////////////////////////////////////////////
    //enable internet access
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

    //////////////////////////////////////////////////////////////////
    //access the key
    cout<<"\33[1;30m------------------------------------------------------------------\33[0m"<<endl;
    cout<<"\33[1;34mEnter the Armory code : \33[0m"<<endl;
    system("/bin/sleep 10");
    system("ssh usbarmory@10.0.0.1");

}

//////////////////////////////////////////////////////////////////
//made by P4ti3nn3
