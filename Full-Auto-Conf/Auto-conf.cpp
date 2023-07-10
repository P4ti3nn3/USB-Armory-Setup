//////////////////////////////////////////////////////////////////
//all includes
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
#include <sstream>
#include <unistd.h>
#include <csignal>
#include <cstdlib>

/////////////////////////////////////
//          tab of collor          //
/////////////////////////////////////
//           letter   background   //
//black        30         40       //
//red          31         41       //
//green        32         42       //
//yellow       33         43       //
//blue         34         44       //
//magenta      35         45       //
//cyan         36         46       //
//white        37         47       //
/////////////////////////////////////


using namespace std;

string clear = "clear";

//////////////////////////////////////////////////////////////////
//CTRL+C gestion
volatile sig_atomic_t signalReceived = 0;
void handleSignal(int signal){
    if (signal== SIGINT){ //if ctrl+c
        cout<<endl<<"\33[1;31mProgram was aborted.\33[0m" <<endl;
        exit(EXIT_SUCCESS);
    }
}

//////////////////////////////////////////////////////////////////
//this work with executeCommandAndWait function
bool commandErrorContainsFileError(const std::string& commandError) {
    std::string errorMessage = "No such file or directory";
    return commandError.find(errorMessage) != std::string::npos;
}

//////////////////////////////////////////////////////////////////
//clean command execution
string executeCommandAndWait(const std::string& command, string search = "n", string ready = "no") {
    std::string sudoCommand = "sudo " + command;
    char buffer[128];
    //////////////////////////////////////////////////////////////////
    //With verification    
    if(search=="y"){
        FILE* pipe = popen(sudoCommand.c_str(), "r"); //command executed
        if (!pipe) { //if error in execution
            std::cerr << "Error when command is executed : " << command << std::endl;
            return "error";
        }
        char buffer[128];
        string result = "";
        while (!feof(pipe)){ //loop to store the command output
            if(fgets(buffer, 128, pipe) != NULL){
                result += buffer;
            }
        }
        pclose(pipe);
        std::regex regex("no device found"); //use to make sure the device is ready
        std::smatch match;
        if (std::regex_search(result, match, regex) && ready!="ok") { //is there a match with the regex ?
            std::cout << "\33[1;31mThe Armory is missing or not set as uSd.\33[0m" <<std::endl;
            return "error";
        }        
        //////////////////////////////////////////////////////////////////
        //aestetic
        if(command!="clear"){ //use to not display ok when the screen is cleaned
            std::cout<<"\033[1;42m\033[1;37mOk!\33[0m"<<endl;
            return "";    
        }
    }
    //////////////////////////////////////////////////////////////////
    //Without verification
    else{
        FILE* pipe = popen(sudoCommand.c_str(), "r"); //command executed
        if (!pipe) {//if error in executon
            std::cerr << "Error when command is executed : " << command << std::endl;
            return "error";
        }
        char buffer[128];
        while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
            std::cout << buffer;  // display command output in realtime
        }
        pclose(pipe);
        //////////////////////////////////////////////////////////////////
        //aestetic
        if(command!="clear"){//use to not display ok when the screen is cleaned
            std::cout<<"\033[1;42m\033[1;37mOk!\33[0m"<<endl;
        }
        return "";
    }
    return "";
}

//////////////////////////////////////////////////////////////////
//root ?
string ruRoot(){
    if (getuid() != 0){ //if user isn't root
        return "no";
    }
    return "yes";
}

//////////////////////////////////////////////////////////////////
//search for USB Armory
array<string, 4> searchPeriph(string display = "yes") {
    std::string command = "sudo fdisk -l"; //store the main command
    std::string result;
    array<string,4> storedResult;
    //////////////////////////////////////////////////////////////////
    // Command and storage
    FILE* pipe = popen(command.c_str(), "r"); //execute command
    if (!pipe) {//if there is an error in execution
        std::cerr << "Error when command is executed : " << std::endl;
        storedResult[2]="error";//use to store error message
        return storedResult;
    }
    const int buffer_size = 128;
    char buffer[buffer_size];
    while(fgets(buffer, buffer_size, pipe) != nullptr){ //store the result of the execution
        result += buffer;
    }
    pclose(pipe);
    regex deviceRegex("/dev/sd[b-z]"); //regex for armory name
    regex modelRegex("USB armory Mk II"); //regex for armory type
    std::smatch deviceMatch;
    smatch modelMatch;
    string device;
    if(regex_search(result, deviceMatch, deviceRegex)&&regex_search(result, modelMatch, modelRegex)){ //if there is a periph that match
        device = deviceMatch.str();
        string model = modelMatch.str();
        if(display != "no"){ //use to not display the result in specific case
            std::cout << "\33[1;32mDevice found : \33[0m" << device << std::endl;
        }        
        string storedDevice = device;
        string storedModel = model;
        storedResult[0] = device;
        storedResult[1] = model;
        storedResult[3] = "ok";
        return storedResult;
    }
    else{
        if(display!="no"){ //use to not display the result in specific case
            std::cerr << "\33[1;31mDevice not found.\33[0m" << std::endl;
        }        
        storedResult[2]="error"; //store the error code 
        return storedResult;
    }
    return storedResult;
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
    std::string w = "apt install bc -y";
    std::string x = "apt update -y";
    std::string y = "apt upgrade -y";   
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
    executeCommandAndWait(x);
    std::this_thread::sleep_for(std::chrono::seconds(1)); //wait till the end
    executeCommandAndWait(y);
    std::this_thread::sleep_for(std::chrono::seconds(1)); //wait till the end   
}

//////////////////////////////////////////////////////////////////
//as USB
string funcUsb(string ready){
    std::string asUsb = "./.pkg/armory-boot/armory-boot-usb -i ./.pkg/armory-boot/armory-ums.imx"; //store the command to execute
    if(executeCommandAndWait(asUsb,"y",ready)=="error"){
        return "error"; //in case of probleme
    } //command for as USB
    std::this_thread::sleep_for(std::chrono::seconds(5)); //wait till the end
    return "";
}

//////////////////////////////////////////////////////////////////
//load the image
void funcImage(string sdx){
    std::string start = "pv -tpreb ./.pkg/armory-2023-05-24.raw | dd of="; //////
    std::string midle = sdx;                                             ////creation of the command
    std::string end = " bs=1M conv=fsync";                                 //////
    std::string lImage = start+midle+end;
    executeCommandAndWait(lImage); //command to load image
    std::this_thread::sleep_for(std::chrono::seconds(5));
}

//////////////////////////////////////////////////////////////////
//enable internet access
void funcNetwork(){
    std::string a = "/bin/sleep 30";
    std::string b = "/sbin/ip link set enx1a5589a26942 up";
    std::string c = "/sbin/ip addr add 10.0.0.2/24 dev enx1a5589a26942";
    std::string d = "/sbin/iptables -t nat -A POSTROUTING -s 10.0.0.1/32 -o wlp2s0 -j MASQUERADE";
    std::string e = "/bin/echo 1 > /proc/sys/net/ipv4/ip_forward";
    executeCommandAndWait(a);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    executeCommandAndWait(b);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    executeCommandAndWait(c);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    executeCommandAndWait(d);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    executeCommandAndWait(e);
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

//////////////////////////////////////////////////////////////////
//access the key
void funcSsh(){
    system("/bin/sleep 10");
    system("ssh usbarmory@10.0.0.1"); //connection to the armory
}

//////////////////////////////////////////////////////////////////
//ensure the access to all needed file
bool locate(const string& filename){
    ifstream file(filename); //make sure that user is in the goog folder
    return file.good();
}

//////////////////////////////////////////////////////////////////
//whomadethis
void source(){
    string from = "made by \33[0;30mP\33[0;31m4\33[0;30mt\33[0;31mi\33[0;30m3\33[0;31mn\33[0;30mn\33[0;31m3\33[0m";
    cout<<from<<endl;
}

//////////////////////////////////////////////////////////////////
//process for installation
void installPack(){
    std::cout<<"\33[1;30m------------------------------------------------------------------\33[0m"<<endl;
    std::cout << "\33[0mAre the \033[1;33mneeded packages\33[0m allready installed ? [\033[1;32mYES(y)\33[0m/\33[1;31mNO(n)\33[0m] : ";
    string response = "n";
    cin>>response; //ask if all needed packages are installed
    //infinite loop waiting for correct answer
    while(response!="y" && response !="YES" && response !="yes" && response !="Y" && response !="Yes" && response !="" && response !="NO" && response !="no" && response !="N" && response !="No" && response !="n"){
        if (response=="whomadethis"){
            source(); //display the source
        }
        std::cout << "\33[0mAre the \033[1;33mneeded packages\33[0m allready installed ? [\033[1;32mYES(y)\33[0m/\33[1;31mNO(n)\33[0m] : ";
        cin>>response;
    }
    //install needed packages if it's wanted
    if (response!="y" && response !="YES" && response !="yes" && response !="Y" && response !="Yes" && response !="whomadethis"){
        std::cout<<"\33[1;34mInstall of needed packages ...\33[0m"<<endl;
        neededPack(); //install packages
        cout<<"\33[1;36mAll packages are installed.\33[0m"<<endl<<endl;
        std::this_thread::sleep_for(std::chrono::seconds(3)); //wait till the end
        executeCommandAndWait(clear);
    }
}

//////////////////////////////////////////////////////////////////
//complete configuration of the Armory
int complete(){
    //////////////////////////////////////////////////////////////////
    //as USB
    array<string, 4> periph = searchPeriph("no"); //use to make sure the "as usb" isn't done yet
    std::cout<<"\33[1;30m------------------------------------------------------------------\33[0m"<<endl;
    std::cout<<"\33[1;34mSet the Armory as USB...\33[0m"<<endl;
    //use to make sure the user is in the good folder
    if (!locate("./.pkg/armory-boot/armory-boot-usb")){
        cout<<"\33[1;31mPlease move to Auto conf folder.\33[0m"<<endl;
        return 1; //1 if not in the folder
    }
    //use to make sure the "as usb" isn't done yet before the execution
    if(periph[3]!="ok"){
        if(funcUsb(periph[3])=="error"){ //remake an as usb if it's not done
            return 3; //3 if there is a problem with the periph
        }            
    }        
    periph = searchPeriph(); //use to find the armory (if it's ready)
    if (periph[2]=="error"){
        return 3; //3 if there is a problem with the periph
    }
    string sdx = periph[0]; //name of the armory
    cout<<"\33[1;36mThe Armory is set as USB.\33[0m"<<endl<<endl;
    //////////////////////////////////////////////////////////////////
    //load the image
    std::cout<<"\33[1;30m------------------------------------------------------------------\33[0m"<<endl;
    std::cout<<"\33[1;34mLoading of the image, please wait...\33[0m"<<endl;
    funcImage(sdx); //load the image on the armory
    cout<<"\33[1;36mImage loaded.\33[0m"<<endl<<endl;
    //////////////////////////////////////////////////////////////////
    //enable internet access
    cout<<"\33[1;30m------------------------------------------------------------------\33[0m"<<endl;
    cout << "\033[1;31m!\33[0mSet back the \033[1;33mUSB switch\33[0m, then, \033[1;32m<ENTER>\33[0m :"<<endl;
    getchar();//
              //use to wait until the switch is correctly set
    getchar();//
    cout<<"\33[1;34mLoading of the network configuration, please wait...\33[0m"<<endl;
    funcNetwork(); //load the network parameters
    cout<<"\33[1;36mNetwork configuration set.\33[0m"<<endl<<endl;
    std::this_thread::sleep_for(std::chrono::seconds(5)); //wait till the end
    return 0;
}

//////////////////////////////////////////////////////////////////
//main menu and following
int menu(){
    cout<<endl;
    cout<<"\33[1;30m------------------------------------------------------------------\33[0m"<<endl;
    cout << "\033[1;40m\033[1;33m[ Complete installation ]\33[0m";
    cout<<" \033[1;30m<\033[1;37ma\033[1;30m>\033[0m        ";
    cout << "\033[1;40m\033[1;33m[ Image installation ]\33[0m";
    cout<<" \033[1;30m<\033[1;37mb\033[1;30m>\033[0m        ";
    cout << "\033[1;40m\033[1;33m[ Network coniguration ]\33[0m";
    cout<<" \033[1;30m<\033[1;37mc\033[1;30m>\033[0m        ";
    cout << "\033[1;41m\033[1;37m[ EXIT ]\33[0m";
    cout<<" \033[1;30m<\033[1;37md\033[1;30m>\033[0m";
    cout<<endl<<endl;
    cout<<"\033[1;34mChoice : \033[0m";
    string s = "a";
    cin>>s;
    while(s != "a" && s != "b" && s != "c" && s != "d"){
        std::cout << "\33[1;31mPlease choose a correct option.\33[0m"<<endl;
        cout<<"\033[1;34mChoice : \033[0m";
        cin>>s;
    }    
    //////////////////////////////////////////////////////////////////
    //complete instalation
    if (s == "a"){
        int problem = complete();
        if (problem == 1){
            return 1;
        }
        if (problem == 3){
            return 1;
        }
        return 31;
    }
    //////////////////////////////////////////////////////////////////
    //only load image
    if (s == "b"){
        array<string, 4> periph = searchPeriph("no");
        periph = searchPeriph(); //use to find the armory (if it's ready)
        if (periph[2]=="error"){
            return 1;
        }
        string sdx = periph[0]; //name of the armory
        //////////////////////////////////////////////////////////////////
        //load the image
        std::cout<<"\33[1;30m------------------------------------------------------------------\33[0m"<<endl;
        std::cout<<"\33[1;34mLoading of the image, please wait...\33[0m"<<endl;
        funcImage(sdx); //load the image on the armory
        cout<<"\33[1;36mImage loaded.\33[0m"<<endl<<endl;
        std::this_thread::sleep_for(std::chrono::seconds(10)); //wait till the end
        return 0;
    }
    //////////////////////////////////////////////////////////////////
    //only network configuration
    if (s == "c"){
        funcNetwork();
        return 8;
    }
    //////////////////////////////////////////////////////////////////
    //exit
    if (s == "d"){
        cout<<endl<<"\33[1;31mProgram was aborted.\33[0m" <<endl;
        return 1;
    }
    return 0;         
}

//////////////////////////////////////////////////////////////////
//access menu
int menuAccess(){
    executeCommandAndWait(clear); //clean the screen
    cout<<"\33[1;30m------------------------------------------------------------------\33[0m"<<endl;
    cout<<"Your \033[1;33mUSB Armory MKII \33[0m is now configured, you can access it and continue the \033[1;33mconfiguration\33[0m."<<endl;
    cout << "\033[1;40m\033[1;33m[ Access key ]\33[0m";
    cout<<" \033[1;30m<\033[1;37ma\033[1;30m>\033[0m        ";
    cout << "\033[1;41m\033[1;37m[ EXIT ]\33[0m";
    cout<<" \033[1;30m<\033[1;37mb\033[1;30m>\033[0m";
    cout<<endl<<endl;
   cout<<"\033[1;34mChoice : \033[0m";
    string r = "a";
    cin>>r;
    while(r != "a" && r != "b"){
        std::cout << "\33[1;31mPlease choose a correct option.\33[0m"<<endl;
        cout<<"\033[1;34mChoice : \033[0m";
        cin>>r;
    }
    if (r=="a"){
        cout<<"\33[1;34mEnter the Armory code : \33[0m"<<endl;
        funcSsh(); //connect in SSH to the armory
        return 0;
    }
    if (r=="b"){
        cout<<endl<<"\33[1;31mProgram was aborted.\33[0m" <<endl;
        return 1;
    }
    return 0;
}

//////////////////////////////////////////////////////////////////
//main part of the code
int main(void){
    //////////////////////////////////////////////////////////////////
    //start of tool
    signal(SIGINT, handleSignal); //manage the ctrl+c
    while (true){
        executeCommandAndWait(clear); //clean the screen
        char x;
        //make sure you're root
        if (ruRoot()=="no"){ 
            cout<<"\33[1;31mYou must be Root to run this tool.\33[0m"<<endl;
            return 1;
        }
        std::cout<<"\33[1;35m##################################################################\33[0m"<<endl;
        std::cout << "Welcome to the Auto-conf tool for USB Armory \033[1;43m\033[1;30mMK II\033[0m"<<endl<<endl;
        std::cout << "\033[1;31m!\33[0mSet the \033[1;33mUSB switch\33[0m on \033[1;33muSd mode\33[0m, then, \033[1;32m<ENTER>\33[0m :"<<endl;
        getchar(); //wait until the user <ENTER>
        //////////////////////////////////////////////////////////////////
        //install needed packages
        installPack();
        //////////////////////////////////////////////////////////////////
        //choice menu and following
        int result = menu();
        if (result == 1){
            return 1;
        }
        //display the message if it wasn't done
        if(result != 31 && result != 8){
            cout<<"\33[1;30m------------------------------------------------------------------\33[0m"<<endl;
            cout << "\033[1;31m!\33[0mSet back the \033[1;33mUSB switch\33[0m, then, \033[1;32m<ENTER>\33[0m :"<<endl;
            getchar();//
                    //use to wait until the switch is correctly set
            getchar();//
        }
        //////////////////////////////////////////////////////////////////
        //access the key
        result = menuAccess();
        if (result == 1){
            return 1;
        }                 
    }
    return 0;
}
