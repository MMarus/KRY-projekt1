//
// Created by archie on 3/18/17.
//

#include "IO.h"

IO::IO() {
    inFileName = "";
    outFilename = "";
}

void IO::createPipes(string write, string read, bool writeFirst) {
    inFileName = read;
    outFilename = write;

    createOutput(outFilename);
    openPipes(writeFirst);
}

void IO::createOutput(string out){
    mknod(out.c_str(), S_IFIFO | 0666, 0);
};

void IO::openPipes(bool writeFirst){
    if(writeFirst){
        openForWrite();
        openForRead();
    }
    else {
        openForRead();
        openForWrite();
    }
}

void IO::openForRead() {
    cout << "log.debug: " <<"waiting for writers..." << endl;
    inputStream.open(inFileName, ifstream::in);
    cout << "log.debug: " << "got a writer" << endl;
}

void IO::openForWrite() {
    cout << "log.debug: " << "waiting for readers..." << endl;
    outputStream.open(outFilename, ifstream::out);
    cout << "log.debug: " << "got a reader" << endl;
}

void IO::sendMessage(string msg) {
    outputStream << msg << endl;
    cout << "log.debug: " << "Sent message" << msg << endl;
}

string IO::readMessage() {
    string msg("");
    cout << "log.debug: " << "Waiting for message" << endl;
    while (msg.length() == 0)
    {
        getline(inputStream, msg);
    }
    cout << "log.debug: " << "Got message:" << msg << endl;
    return msg;
}





