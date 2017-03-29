//
// Created by archie on 3/29/17.
//

#ifndef KRY_PROJEKT1_AES_H
#define KRY_PROJEKT1_AES_H

#include <iostream>
using namespace std;

static const unsigned int KEY_SIZE = 256;
static const unsigned int BLOCK_SIZE = 128;

class AES {
public:
    AES();
    string encrypt(string msg);
    string decrypt(string msg);

private:
    string key;
public:
    void setKey(const string &key);

    void setInitVector(const string &initVector);

private:
    string initVector;
};


#endif //KRY_PROJEKT1_AES_H
