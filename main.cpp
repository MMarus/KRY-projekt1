#include <iostream>
#include "Communicator.h"
#include <gmp.h>
#include <gmpxx.h>
#include "Hash.h"
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

    string clientPipeName("fromClient");
    string serverPipeName("fromServer");

    string message("Mega tajna sprava!");
    string cipherTxt("");
    string recoveredTxt("");

//    AES aes;
//    aes.setInitVector("1263897930360445");
//    aes.setKey("10426667945622412389331687349788");
//    cipherTxt = aes.encrypt(message);
//    cout << "Encrypted msg " << cipherTxt << endl;
//    recoveredTxt = aes.decrypt(cipherTxt);
//    cout << "decrypted msg " << recoveredTxt << endl;


    if(isArgClient(argument)){
        std::cout << "HUraa klient" << std::endl;
        Client client;
        client.run();
    }
    else{
        std::cout << "HUraa server" << std::endl;
        Server server;
        server.run();
    }

    printf("KONIEC PROGRAMU");
    return 0;
}