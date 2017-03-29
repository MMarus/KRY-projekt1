//
// Created by archie on 3/21/17.
//

#include "DiffieHellman.h"
#include <openssl/evp.h>
#include <openssl/rand.h>

const int base = 10;

DiffieHellman::DiffieHellman() {
    nPublicPrimeModulus.set_str("FFFFFFFF FFFFFFFF C90FDAA2 2168C234 C4C6628B 80DC1CD1 29024E08 8A67CC74 020BBEA6 3B139B22 514A0879 8E3404DD EF9519B3 CD3A431B 302B0A6D F25F1437 4FE1356D 6D51C245 E485B576 625E7EC6 F44C42E9 A637ED6B 0BFF5CB6 F406B7ED EE386BFB 5A899FA5 AE9F2411 7C4B1FE6 49286651 ECE45B3D C2007CB8 A163BF05 98DA4836 1C55D39A 69163FA8 FD24CF5F 83655D23 DCA3AD96 1C62F356 208552BB 9ED52907 7096966D 670C354E 4ABC9804 F1746C08 CA18217C 32905E46 2E36CE3B E39E772C 180E8603 9B2783A2 EC07A28F B5C55DF0 6F4C52C9 DE2BCBF6 95581718 3995497C EA956AE5 15D22618 98FA0510 15728E5A 8AAAC42D AD33170D 04507A33 A85521AB DF1CBA64 ECFB8504 58DBEF0A 8AEA7157 5D060C7D B3970F85 A6E1E4C7 ABF5AE8C DB0933D7 1E8C94E0 4A25619D CEE3D226 1AD2EE6B F12FFA06 D98A0864 D8760273 3EC86A64 521F2B18 177B200C BBE11757 7A615D6C 770988C0 BAD946E2 08E24FA0 74E5AB31 43DB5BFC E0FD108E 4B82D120 A9210801 1A723C12 A787E6D7 88719A10 BDBA5B26 99C32718 6AF4E23C 1A946834 B6150BDA 2583E9CA 2AD44CE8 DBBBC2DB 04DE8EF9 2E8EFC14 1FBECAA6 287C5947 4E6BC05D 99B2964F A090C3A2 233BA186 515BE7ED 1F612970 CEE2D7AF B81BDD76 2170481C D0069127 D5B05AA9 93B4EA98 8D8FDDC1 86FFB7DC 90A6C08F 4DF435C9 34063199 FFFFFFFF FFFFFFFF",
                                16); // 4096bitov prime z http://www.ietf.org/rfc/rfc3526.txt
    gPublicPrimeBase.set_str("FFFFFFFF FFFFFFFF C90FDAA2 2168C234 C4C6628B 80DC1CD1 29024E08 8A67CC74 020BBEA6 3B139B22 514A0879 8E3404DD EF9519B3 CD3A431B 302B0A6D F25F1437 4FE1356D 6D51C245 E485B576 625E7EC6 F44C42E9 A637ED6B 0BFF5CB6 F406B7ED EE386BFB 5A899FA5 AE9F2411 7C4B1FE6 49286651 ECE45B3D C2007CB8 A163BF05 98DA4836 1C55D39A 69163FA8 FD24CF5F 83655D23 DCA3AD96 1C62F356 208552BB 9ED52907 7096966D 670C354E 4ABC9804 F1746C08 CA237327 FFFFFFFF FFFFFFFF",
                             16); //1536bitov z http://www.ietf.org/rfc/rfc3526.txt
    exponentToSend.set_str("0", base);
    generateMyExponent();
}

void DiffieHellman::generateMyExponent() {
    unsigned long randomNumber; //TODO: NOT SURE ABOUT MEMORY LEAKS
    if (!RAND_bytes((unsigned char *)&randomNumber, sizeof randomNumber)) {
        /* OpenSSL reports a failure, act accordingly */
        cerr << "Error: nepodarilo sa vygenerovat random exponent!" << endl;
    }

    gmp_randclass  r(gmp_randinit_default);
    r.seed(randomNumber);
    myExponent = r.get_z_bits(256);
    cout << "log.debug: " << "Generated exponent: " << myExponent.get_str(base) << endl;
}

void DiffieHellman::generateExponentToSend() {
    //expToSend = g^myExp mod n
    cout << gPublicPrimeBase.get_str(base);
    cout << "^ " << myExponent.get_str(base);
    cout << " mod " << nPublicPrimeModulus.get_str(base);
    cout << endl;
    mpz_powm(exponentToSend.get_mpz_t(),
             gPublicPrimeBase.get_mpz_t(),
             myExponent.get_mpz_t(),
             nPublicPrimeModulus.get_mpz_t());
}

mpz_class DiffieHellman::getExponentToSend() {
    return exponentToSend;
}

void DiffieHellman::setRecievedExponent(mpz_class exp) {
    recievedExponent = exp;
}

void DiffieHellman::calculateKey() {
    //expToSend = g^myExp mod n
    cout << recievedExponent.get_str(base);
    cout << "^ " << myExponent.get_str(base);
    cout << " mod " << nPublicPrimeModulus.get_str(base);
    cout << endl;
    mpz_powm(keyRaw.get_mpz_t(),
             recievedExponent.get_mpz_t(),
             myExponent.get_mpz_t(),
             nPublicPrimeModulus.get_mpz_t());
}

mpz_class DiffieHellman::trimKeyTo(int bits) {
    mpz_class result("0", base);
    string maxNumberStr(bits, '1');
    mpz_class maxNumber(maxNumberStr, 2);
    mpz_mod(result.get_mpz_t(), keyRaw.get_mpz_t(), maxNumber.get_mpz_t() );
    cout << "log.debug: " << "DH key: trimed to " << bits << " = " << result.get_str(base) << endl;
    return result;
}
