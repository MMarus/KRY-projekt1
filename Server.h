//
// Created by archie on 4/1/17.
//

#ifndef KRY_PROJEKT1_SERVER_H
#define KRY_PROJEKT1_SERVER_H


#include "Communicator.h"
#include "FFS.h"

class Server {
public:
    Server();
    void run();
    void verifyClient();
    void setupFFSParameters();
    void readX();
    void sendRandomBitsVector();
    void readResponse();
    bool isResponseOk();
    void listen();

private:
    Communicator communicator;
    string clientPipeName;
    string serverPipeName;
    FFS ffs;

};


#endif //KRY_PROJEKT1_SERVER_H
