//
// Created by archie on 3/18/17.
//

#ifndef KRY_PROJEKT1_COMMUNICATOR_H
#define KRY_PROJEKT1_COMMUNICATOR_H
#import <string>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include "IO.h"
#include "DiffieHellman.h"
#include "AES.h"

using namespace std;


class Communicator {
public:
    Communicator();
    void createIO(string to, string from, bool writeFirst);
    void createTunnel();

    string readMsg();
    void sendMsg(string msg);
    void sendEncryptedMsg(string msg);
    string readEncryptedMsg();
    bool isTunnelCreated();

    void listen();


private:
    IO io;
    int key;
    bool tunnelCreated;
public:
    void setTunnelCreated(bool tunnelCreated);

private:
    AES aes;
    DiffieHellman diffieHellman;

};


#endif //KRY_PROJEKT1_COMMUNICATOR_H
