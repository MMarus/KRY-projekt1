//
// Created by archie on 3/18/17.
//

#include "Communicator.h"

Communicator::Communicator() {
    key = 0;
    tunnelCreated = false;
}

void Communicator::createIO(string to, string from, bool writeFirst) {
    io.createPipes(to, from, writeFirst);
}

void Communicator::createTunnel() {
    diffieHellman.generateExponentToSend();
    cerr << "log.debug: " << "Exponent to send: " << diffieHellman.getExponentToSend().get_str(base) << endl;
    sendMsg(diffieHellman.getExponentToSend().get_str(base));
    string message(readMsg());
    cerr << "log.debug: " << "Recieved exponent = " << message << endl;
    mpz_class recievedExponent(message, base);
    diffieHellman.setRecievedExponent(recievedExponent);
    diffieHellman.calculateKey();

    cerr << "log.debug: " << "DH key: " << diffieHellman.keyRaw.get_str(base) << endl;

    aes.setInitVector(diffieHellman.trimKeyTo(256));
    aes.setKey(diffieHellman.trimKeyTo(128));

    setTunnelCreated(true);
}

void Communicator::sendEncryptedMsg(string msg) {
    string encryptedMsg(msg);
    if(isTunnelCreated())
        encryptedMsg = aes.encrypt(msg);
    else
        throw std::runtime_error("Communicator: Sending encrypted msg before tunnel created");
    cerr << "log.debug: sent msg: '" << msg <<"' msg encrypted:  '" << encryptedMsg << "'" <<  endl;
    sendMsg(encryptedMsg);
}

void Communicator::sendMsg(string msg) {
    io.sendMessage(msg);
}

string Communicator::readEncryptedMsg() {
    string encryptedMsg(readMsg());
    string decryptedMessage(encryptedMsg);
    if(isTunnelCreated())
        decryptedMessage = aes.decrypt(encryptedMsg);
    else
        throw std::runtime_error("Communicator: Sending encrypted msg before tunnel created");

    if(decryptedMessage.empty())
        throw std::runtime_error("Communicator: Error during message decryption");

    cout << "Recieved message = '" << decryptedMessage << "'" << endl;

    cerr << "log.debug: recieved msg: '" << decryptedMessage <<"' msg encrypted:  '" << encryptedMsg << "'" <<  endl;
    return decryptedMessage;
}

string Communicator::readMsg() {
    string message;
    message = io.readMessage();
    return message;
}

bool Communicator::isTunnelCreated() {
    return tunnelCreated;
}

void Communicator::setTunnelCreated(bool tunnelCreated) {
    Communicator::tunnelCreated = tunnelCreated;
}






