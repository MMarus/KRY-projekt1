//
// Created by archie on 3/29/17.
//

#include <openssl/ossl_typ.h>
#include <openssl/evp.h>
#include "Hash.h"
#include <openssl/sha.h>

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

    string my_std_string(digest, digest + digest_length);
    std::string my_std_string(reinterpret_cast<const char *>(digest), digest_length);
    cout << "log.debug: Hash: digest lenght " << digest_length << endl;
    cout << "log.debug: " << "Hash: msg = " << msg << " CONVERTED HASH: " << my_std_string << endl;

    cout << "log.debug: " << "Hash: msg = " << msg << " hash: " << digest << endl;
    return hash;
}

bool Hash::isHashCorrect(string hash, string msg) {
    string msgHash = createSHA256(msg);
    bool hashCorrect = hash == msgHash;
    cout << "log.debug: " << "Hash correctd: " << hashCorrect << endl;
    return hashCorrect;
}

void Hash::handleErrors() {
    throw std::runtime_error("Hash: Could not create hash");
}
