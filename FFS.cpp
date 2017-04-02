//
// Created by archie on 4/1/17.
//

#include <openssl/rand.h>
#include "FFS.h"
#include "DiffieHellman.h"

FFS::FFS() : randomBitsVector(kSecurityParameter), publicVector(kSecurityParameter){

}

void FFS::calculatePublicVector() {
    mpz_class minus1("-1", base);
    mpz_class result;
    vector<unsigned long> randomBits = generateRandomBitsVector();

    for(int i =0; i < kSecurityParameter; i++) {
        mpz_pow_ui(result.get_mpz_t(), minus1.get_mpz_t(), randomBits[i]);   //(-1)^bi
        mpz_mul(result.get_mpz_t(), result.get_mpz_t(), secretVector[i].get_mpz_t()); // result = (-1)^bi * si
        mpz_mul(result.get_mpz_t(), result.get_mpz_t(), secretVector[i].get_mpz_t()); // result = (-1)^bi * si * si
        mpz_powm(result.get_mpz_t(), result.get_mpz_t(), minus1.get_mpz_t(), nCommonModulus.get_mpz_t());
        cerr << "log.debug: calculatePublicVector i: " << i << " = " << result.get_str(base) << endl;
        publicVector[i] = result;
    }
}

vector<unsigned long> FFS::generateRandomBitsVector() {
    vector<unsigned long> randomBits(kSecurityParameter);

    cerr << "log.debug: randomBitsVector = " << endl;

    for(int i = 0; i < kSecurityParameter; i++) {
        randomBits[i] = generateRandomBit();
        cout << "randomBitsVector["<<i<<"] = " << randomBits[i] << endl;

    }
    return randomBits;
}

unsigned long FFS::generateRandomBit() {
    //TODO: randomize
    unsigned long randomNumber;
    if (!RAND_bytes((unsigned char *)&randomNumber, sizeof randomNumber)) {
        /* OpenSSL reports a failure, act accordingly */
        cerr << "Error: nepodarilo sa vygenerovat random Bit" << endl;
    }
    unsigned long randomBool = randomNumber % 2;
    return randomBool;
}

mpz_class FFS::calculateXForB() {
    mpz_class result("0", base);
    mpz_class two("2", base);
    mpz_class minus1("-1", base);
    unsigned long randomBit = generateRandomBit(); // b
    mpz_class randB(randomBit);
    mpz_class randomInt = generateRandomInteger(nCommonModulus); //r
    setRandomInteger(randomInt);

    mpz_powm(result.get_mpz_t(), minus1.get_mpz_t(), randB.get_mpz_t(), nCommonModulus.get_mpz_t()); //(-1)^b
    mpz_mul(result.get_mpz_t(), result.get_mpz_t(), randomInt.get_mpz_t()); //result = (-1)^b * r
    mpz_mul(result.get_mpz_t(), result.get_mpz_t(), randomInt.get_mpz_t()); //result = (-1)^b * r * r
    mpz_mod(result.get_mpz_t(), result.get_mpz_t(), nCommonModulus.get_mpz_t());

    cerr << "log.debug: calculateX (-1)^b * r * r mod n = " << result.get_str(base) << endl;
    return result;
}

mpz_class FFS::calculateResponse() {
    mpz_class response(randomInteger.get_mpz_t()); //copy random integer
    mpz_class secretExpBit("0", base);
    if(randomBitsVector.size() < kSecurityParameter )
        throw runtime_error("Vector is smaller than security parameter k");
    else {
        for(int i = 0; i < kSecurityParameter; i++) {
            mpz_pow_ui(secretExpBit.get_mpz_t(), secretVector[i].get_mpz_t(), randomBitsVector[i]); // si^ei
            mpz_mul(response.get_mpz_t(), response.get_mpz_t(), secretExpBit.get_mpz_t());
        }
        mpz_mod(response.get_mpz_t(), response.get_mpz_t(), nCommonModulus.get_mpz_t());
    }

    cerr << "log.debug: calculated response = " << response.get_str(base) << endl;
    return response;
}

bool FFS::verifyResponse(mpz_class response) {
    bool result = false;
    mpz_class z("1", base);
    mpz_class publicVectExpBit("0", base);

    mpz_pow_ui(z.get_mpz_t(), response.get_mpz_t(), 2); // y^2

    if(randomBitsVector.size() < kSecurityParameter )
        throw runtime_error("Vector is smaller than security parameter k");
    else {
        for(int i = 0; i < kSecurityParameter; i++) {
            mpz_pow_ui(publicVectExpBit.get_mpz_t(), publicVector[i].get_mpz_t(), randomBitsVector[i]); // vi^ei
            mpz_mul(z.get_mpz_t(), z.get_mpz_t(), publicVectExpBit.get_mpz_t());
        }
        mpz_mod(z.get_mpz_t(), z.get_mpz_t(), nCommonModulus.get_mpz_t());
    }
    mpz_class minusX;
    mpz_neg(minusX.get_mpz_t(), XForB.get_mpz_t());
    mpz_mod(minusX.get_mpz_t(), minusX.get_mpz_t(), nCommonModulus.get_mpz_t());
    if ( mpz_cmp_si(z.get_mpz_t(), 0) != 0 &&
            ( mpz_cmp(z.get_mpz_t(), XForB.get_mpz_t()) == 0 || mpz_cmp(z.get_mpz_t(), minusX.get_mpz_t()) == 0) )
        result = true;

    cerr << "log.debug: compare XForB = " << endl << XForB.get_str(base) << endl << "and z = " << endl << z.get_str(base) << endl;
    cerr << "log.debug: " << "response is OK ?" << result << endl;
    return result;
}

mpz_class FFS::generateRandomInteger(mpz_class max) {
    mpz_class randomInt("1279", base);

    unsigned long randomNumber; //TODO: NOT SURE ABOUT MEMORY LEAKS
    if (!RAND_bytes((unsigned char *)&randomNumber, sizeof randomNumber)) {
        /* OpenSSL reports a failure, act accordingly */
        cerr << "Error: nepodarilo sa vygenerovat random exponent!" << endl;
    }

    gmp_randclass  r(gmp_randinit_default);
    r.seed(randomNumber);
    randomInt = r.get_z_bits(4096);
    mpz_mod(randomInt.get_mpz_t(), randomInt.get_mpz_t(), max.get_mpz_t());
    cerr << "log.debug: " << "Generated random int: " << randomInt.get_str(base) << endl;

    return randomInt;
}

void FFS::setRandomInteger(const mpz_class &randomInteger) {
    FFS::randomInteger = randomInteger;
}

void FFS::setXForB(const mpz_class &XForB) {
    FFS::XForB = XForB;
}

const vector<mpz_class> &FFS::getPublicVector() const {
    return publicVector;
}

void FFS::setNCommonModulus(const mpz_class &nCommonModulus) {
    FFS::nCommonModulus = nCommonModulus;
}

void FFS::setSecretVector(const vector<mpz_class> &secretVector) {
    FFS::secretVector = secretVector;
}

void FFS::setPublicVector(const vector<mpz_class> &publicVector) {
    FFS::publicVector = publicVector;
}

void FFS::setRandomBitsVector(const vector<unsigned long int> &randomBitsVector) {
    FFS::randomBitsVector = randomBitsVector;
}

string FFS::getRandomBitsVectorStr() {
    string str("");
    for(int i = 0; i < kSecurityParameter; i++) {
        randomBitsVector[i] == 1 ? str.append("1") : str.append("0");
    }
    cerr << "log.debug: vector = " << str << endl;
    return str;
}

void FFS::setRandomBitsVectorStr(string bits) {
    for(int i = 0; i < kSecurityParameter; i++) {
        randomBitsVector[i] = bits[i] == '1' ? 1 : 0;
    }
}

void FFS::setResponse(const mpz_class &response) {
    FFS::response = response;
}

const mpz_class &FFS::getResponse() const {
    return response;
}
