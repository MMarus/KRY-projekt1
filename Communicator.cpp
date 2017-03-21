//
// Created by archie on 3/18/17.
//

#include "Communicator.h"

Communicator::Communicator() {
    key = 0;
}

void Communicator::createIO(string to, string from, bool writeFirst) {
    io.createPipes(to, from, writeFirst);
}

void Communicator::readMsg() {
    string message;
    message = io.readMessage();
}

void Communicator::sendMsg(string msg) {
    io.sendMessage(msg);
}
