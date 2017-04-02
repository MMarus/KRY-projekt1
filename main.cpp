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

//
//    FFS ffs1;
//    mpz_class commonModulus("553913", base);
//    ffs1.setNCommonModulus(commonModulus);
//    vector<mpz_class> secretVector(kSecurityParameter);
//    secretVector[0].set_str("157", base);
//    secretVector[1].set_str("43215", base);
//    secretVector[2].set_str("4646", base);
////    secretVector[3].set_str("1", base);
////    secretVector[4].set_str("1", base);
//    ffs1.setSecretVector(secretVector);
//    //ffs1.calculatePublicVector();
//
//    vector<mpz_class> publicVector(kSecurityParameter);
//    publicVector[0].set_str("441845",base);
//    publicVector[1].set_str("338402",base);
//    publicVector[2].set_str("124423",base);
////    publicVector[3].set_str("1",base);
////    publicVector[4].set_str("1",base);
//
//    //Client generuje random bit - challenge vector kt, posle serveru
//    FFS ffs2;
//    ffs2.setNCommonModulus(commonModulus);
//    vector<unsigned long> randBitsVect = ffs2.generateRandomBitsVector();
//
//    //komunikacia
//    ffs2.setPublicVector(publicVector);
//    ffs2.setRandomBitsVector(randBitsVect);
//    ffs1.setRandomBitsVector(randBitsVect);
////    ffs1.calculateXForB();
////    ffs1.calculateResponse();
//    ffs2.setXForB(ffs1.calculateXForB());
//    bool isResponseOk = ffs2.verifyResponse(ffs1.calculateResponse());
//
//    cout << "log debug: isResponseOk = " << isResponseOk << endl;


//    string hash(Hash::createSHA256(message));
//    string testHash("Hello world");
//    Hash::createSHA256(testHash);
//    bool hashCorretness = Hash::isHashCorrect(hash, message);
//    cout << "HASH = = " << hashCorretness << endl;


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