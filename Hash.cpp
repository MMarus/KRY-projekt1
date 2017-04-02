//
// Created by archie on 3/29/17.
//

#include <openssl/ossl_typ.h>
#include <openssl/evp.h>
#include "Hash.h"
#include <openssl/sha.h>
#include <iomanip>
#include <sstream>

string Hash::createSHA256(string msg) {
    unsigned int digest_length = SHA256_DIGEST_LENGTH;
    unsigned char *digest;

    //Kod z https://wiki.openssl.org/index.php/EVP_Message_Digests
    EVP_MD_CTX *mdctx;

    if((mdctx = EVP_MD_CTX_create()) == NULL)
        handleErrors();

    if(1 != EVP_DigestInit_ex(mdctx, EVP_sha256(), NULL))
        handleErrors();

    if(1 != EVP_DigestUpdate(mdctx, msg.c_str(), msg.length()))
        handleErrors();

    if((digest = (unsigned char *)OPENSSL_malloc(EVP_MD_size(EVP_sha256()))) == NULL)
        handleErrors();

    if(1 != EVP_DigestFinal_ex(mdctx, digest, &digest_length))
        handleErrors();

    EVP_MD_CTX_destroy(mdctx);

    string hash((char *)digest);

    cout << "log.debug: " << "Hash: msg = " << msg << " hash: " << digest << endl;




    stringstream ss;
    ss << std::hex << setfill('0');
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i)
    {
        cout << std::setw(2) << static_cast<unsigned>(hash[i]);
        ss << std::setw(2) << static_cast<unsigned>(hash[i]);
    }
    cout << endl;

    cout << "log.debug: " << "Hash: msg = " << msg << " hash HEX: " << ss.str() << endl;


    return ss.str();
}



bool Hash::isHashCorrect(string hash, string msg) {
    string msgHash(createSHA256(msg));
    bool hashCorrect = hash == msgHash;
    cout << "log.debug: " << "Hash correctd: " << hashCorrect << endl;
    return hashCorrect;
}

void Hash::handleErrors() {
    throw std::runtime_error("Hash: Could not create hash");
}
