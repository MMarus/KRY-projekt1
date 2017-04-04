//
// Created by archie on 4/1/17.
//

#ifndef KRY_PROJEKT1_CLIENT_H
#define KRY_PROJEKT1_CLIENT_H


#include "Communicator.h"
#include "FFS.h"

class Client {
public:
    Client();
    void run();
    void verifyClient();
    void sendUserInput();
    void setupFFSParameters();
    void sendX();
    void readRandomBitsVector();
    void sendFFSResponse();


private:
    Communicator communicator;
    string clientPipeName;
    string serverPipeName;
    FFS ffs;

};


#endif //KRY_PROJEKT1_CLIENT_H
