//
// Created by archie on 3/18/17.
//

#ifndef KRY_PROJEKT1_PIPE_H
#define KRY_PROJEKT1_PIPE_H

#import <string>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fstream>

using namespace std;

class IO {
public:
    IO();
    void createPipes(string to, string from, bool write);
    void sendMessage(string msg);
    string readMessage();


private:
    string inFileName;
    string outFilename;

    ifstream inputStream;
    ofstream outputStream;

    string msgHeader;
    string msgFooterT;

    void createOutput(string out);
    void openPipes(bool);
    void openForRead();
    void openForWrite();
};


#endif //KRY_PROJEKT1_PIPE_H
