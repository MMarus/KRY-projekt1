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

using namespace std;


class Communicator {
public:
    Communicator();
    void createIO(string to, string from, bool writeFirst);

    void readMsg();
    void sendMsg(string msg);
    void listen();


private:
    IO io;
    int key;
    void setupPipe();
};


#endif //KRY_PROJEKT1_COMMUNICATOR_H