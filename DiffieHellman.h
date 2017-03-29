//
// Created by archie on 3/21/17.
//

#ifndef KRY_PROJEKT1_DIFFIEHELLMAN_H
#define KRY_PROJEKT1_DIFFIEHELLMAN_H

extern const int base;

#include <gmp.h>
#include <gmpxx.h>
#include <iostream>
using namespace std;

class DiffieHellman {

public:
    DiffieHellman();
    void generateExponentToSend();
    mpz_class getExponentToSend();
    void setRecievedExponent(mpz_class exp);
    void calculateKey();
    mpz_class trimKeyTo(int bits);
    mpz_class keyRaw;
    mpz_class keyTrimmed;
    mpz_class initVector;

private:
    mpz_class nPublicPrimeModulus;
    mpz_class gPublicPrimeBase;
    mpz_class myExponent;
    mpz_class exponentToSend;
    mpz_class recievedExponent;

    void generateMyExponent();
};


#endif //KRY_PROJEKT1_DIFFIEHELLMAN_H
