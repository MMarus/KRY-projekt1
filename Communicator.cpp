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
    cout << "log.debug: " << "Exponent to send: " << diffieHellman.getExponentToSend().get_str(base) << endl;
    sendMsg(diffieHellman.getExponentToSend().get_str(base));
    string message(readMsg());
    cout << "log.debug: " << "Recieved exponent = " << message << endl;
    mpz_class recievedExponent(message, base);
    diffieHellman.setRecievedExponent(recievedExponent);
    diffieHellman.calculateKey();

//TODO: prekonvertovat do unsigned char pred asignovanim do str
    cout << "log.debug: " << "DH key: " << diffieHellman.keyRaw.get_str(base) << endl;

    aes.setInitVector(diffieHellman.trimKeyTo(256));
    aes.setKey(diffieHellman.trimKeyTo(128));

//    mpz_class key("571265377419729461734767680290181434030375586089350011581905576", base);
//    mpz_class initVector("1271078490719233717764", base);
//    aes.setInitVector(initVector.get_str(base));
//    aes.setKey(key.get_str(base));
    setTunnelCreated(true);
}

void Communicator::sendEncryptedMsg(string msg) {
    string encryptedMsg(msg);
    if(isTunnelCreated())
        encryptedMsg = aes.encrypt(msg);
    else
        throw std::runtime_error("Communicator: Sending encrypted msg before tunnel created");
    cout << "log.debug: sent msg: '" << msg <<"' msg encrypted:  '" << encryptedMsg << "'" <<  endl;
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

    cout << "log.debug: recieved msg: '" << decryptedMessage <<"' msg encrypted:  '" << encryptedMsg << "'" <<  endl;
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






