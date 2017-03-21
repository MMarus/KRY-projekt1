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

void Communicator::createTunnel() {
    diffieHellman.generateExponentToSend();
    cout << "log.debug: " << "Exponent to send: " << diffieHellman.getExponentToSend().get_str(base) << endl;
    sendMsg(diffieHellman.getExponentToSend().get_str(base));
    string message = readMsg();
    cout << "log.debug: " << "Recieved exponent = " << message << endl;
    mpz_class recievedExponent(message, base);
    diffieHellman.setRecievedExponent(recievedExponent);
    diffieHellman.calculateKey();
    cout << "log.debug: " << "DH key: " << diffieHellman.keyRaw.get_str(base) << endl;
}

string Communicator::readMsg() {
    string message;
    message = io.readMessage();
    return message;
}

void Communicator::sendMsg(string msg) {
    io.sendMessage(msg);
}


