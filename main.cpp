#include <iostream>
#include "Communicator.h"
#include "Hash.h"

using namespace std;

bool isArgumentCorrect(char* argument){
    string arg(argument);
    return (arg == "-c" || arg == "-s");
}
bool isArgClient(string arg){
    return arg == "-c";
}

//TODO: skusit odoslat a prijat spravu
/*TODO: typedef std::basic_string <unsigned char> ustring; pouzit mozno*/

int main(int argc, char* argv[])
{
    if(argc <2 || !isArgumentCorrect(argv[1])){
        std::cerr << "Help: run either with -s or -c parameter." << std::endl;
        return 1;
    }
    string argument(argv[1]);
    std::cout << argument << std::endl;

    string clientPipeName = "fromClient";
    string serverPipeName = "fromServer";

    string message = "Mega tajna sprava!";

//    string hash = Hash::createSHA256(message);
    string testHash("Hello world");
    Hash::createSHA256(testHash);
//    bool hashCorretness = Hash::isHashCorrect(hash, message);
//    cout << "HASH = = " << hashCorretness << endl;


//    if(isArgClient(argument)){
//        std::cout << "HUraa klient" << std::endl;
//        Communicator client;
//        client.createIO(clientPipeName, serverPipeName, true);
//        client.readMsg();
//        client.createTunnel();
//        client.sendEncryptedMsg(message);
//    }
//    else{
//        std::cout << "HUraa server" << std::endl;
//        Communicator server;
//        server.createIO(serverPipeName, clientPipeName, false);
//        server.sendMsg("Helloooooo Woooorld!");
//        server.createTunnel();
//        string encMsg = server.readEncryptedMsg();
//    }

    printf("KONIEC PROGRAMU");
    return 0;
}