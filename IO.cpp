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
    outputStream << "$XMARUS05MSGSTARTSIZE: ";
    outputStream << msg.size();
    outputStream << " ";
    outputStream << msg;
    outputStream << "XMARUS05MSGEND$";
    outputStream << endl;

    cout << "log.debug: " << "Sent message size:'" << msg.size() <<"' content: " << msg << endl;
}

string IO::readMessage() {
    string head("$XMARUS05MSGSTARTSIZE:");
    string footer("XMARUS05MSGEND$");
    string msg("");

    cout << "log.debug: " << "Waiting for message" << endl;
    int msgSize = 0;

    char c;
    while (msg.length() == 0)
    {
        string msgStart("");
        inputStream >> msgStart;
        cout << msgStart << endl;
        if(msgStart == head){
            inputStream >> msgSize;
            cout << "message size = " << msgSize << endl;
            inputStream.get(c); //odstran medzeru zo zaciatku
            for(int i = 0; i <= (msgSize + footer.length()); i++) {
                inputStream.get(c);
                msg += c;
            }
        }
    }
    //TODO: remove footer
    cout << "log.debug: " << "Got message:" << msg << endl;
    msg = msg.substr(0, msg.size()-16);
    cout << "log.debug: " << "Got message:" << msg << endl;
    return msg;
}





