//
// Created by archie on 4/1/17.
//

#ifndef KRY_PROJEKT1_FFS_H
#define KRY_PROJEKT1_FFS_H

#include <cstddef>
#include <gmp.h>
#include <gmpxx.h>
#include <iostream>
#include <vector>

using namespace std;

#define kSecurityParameter 5
#define tSecurityParameter 4

class FFS {
public:
    FFS();
    void calculatePublicVector();
    vector<unsigned long> generateRandomBitsVector();
    unsigned long generateRandomBit();
    mpz_class generateRandomInteger(mpz_class max);
    mpz_class calculateXForB();
    mpz_class calculateResponse();
    bool verifyResponse(mpz_class response);

    void setSecretVector(const vector<mpz_class> &secretVector);
    void setNCommonModulus(const mpz_class &nCommonModulus);
    void setPublicVector(const vector<mpz_class> &publicVector);
    void setRandomInteger(const mpz_class &randomInteger);
    void setRandomBitsVector(const vector<unsigned long int> &randomBitsVector);
    void setXForB(const mpz_class &XForB);
    void setRandomBitsVectorStr(string bits);
    void setResponse(const mpz_class &response);

    string getRandomBitsVectorStr();
    const vector<mpz_class> &getPublicVector() const;
    const mpz_class &getResponse() const;


private:
    mpz_class nCommonModulus;
    vector<mpz_class> publicVector;
    vector<mpz_class> secretVector;
    vector<unsigned long int> randomBitsVector;
    mpz_class randomInteger;
    mpz_class XForB;
    mpz_class response;

};


#endif //KRY_PROJEKT1_FFS_H
