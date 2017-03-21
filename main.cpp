#include <iostream>
#include <string>
#include "Communicator.h"

using namespace std;

bool isArgumentCorrect(int argc, string arg){
    return (argc == 2 && (arg == "-c" || arg == "-s") );
}
bool isArgClient(string arg){
    return arg == "-c";
}

//TODO: skusit odoslat a prijat spravu

int main(int argc, char* argv[])
{
    string argument(argv[1]);

    if(!isArgumentCorrect(argc,argument)){
        std::cerr << "Help: run either with -s or -c parameter." << std::endl;
        return 1;
    }
    std::cout << argument << std::endl;

    string clientPipeName = "fromClient";
    string serverPipeName = "fromServer";

    if(isArgClient(argument)){
        std::cout << "HUraa klient" << std::endl;
        Communicator client;
        client.createIO(clientPipeName, serverPipeName, true);
        client.readMsg();
    }
    else{
        std::cout << "HUraa server" << std::endl;
        Communicator server;
        server.createIO(serverPipeName, clientPipeName, false);
        server.sendMsg("Helloooooo Woooorld!");
    }

    printf("KONIEC PROGRAMU");
    return 0;
}