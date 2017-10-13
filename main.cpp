#include <iostream>
#include "Communicator.h"
#include "FFS.h"
#include "Client.h"
#include "Server.h"

using namespace std;

bool isArgumentCorrect(char* argument){
    string arg(argument);
    return (arg == "-c" || arg == "-s");
}
bool isArgClient(string arg){
    return arg == "-c";
}

int main(int argc, char* argv[])
{
    if(argc <2 || !isArgumentCorrect(argv[1])){
        std::cerr << "Help: run either with -s or -c parameter." << std::endl;
        return 1;
    }
    string argument(argv[1]);
    std::cout << argument << std::endl;

    if(isArgClient(argument)){
        std::cout << "Klient" << std::endl;
        Client client;
        client.run();
    }
    else{
        std::cout << "Server" << std::endl;
        Server server;
        server.run();
    }

    std::cout << "KONIEC PROGRAMU" << std::endl;
    return 0;
}