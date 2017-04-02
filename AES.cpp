//
// Created by archie on 3/29/17.
//

#include <openssl/crypto.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <memory>
#include <limits>
#include "AES.h"

//From https://wiki.openssl.org/index.php/EVP_Symmetric_Encryption_and_Decryption
template <typename T>
struct zallocator
{
public:
    typedef T value_type;
    typedef value_type* pointer;
    typedef const value_type* const_pointer;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;

    pointer address (reference v) const {return &v;}
    const_pointer address (const_reference v) const {return &v;}

    pointer allocate (size_type n, const void* hint = 0) {
        if (n > std::numeric_limits<size_type>::max() / sizeof(T))
            throw std::bad_alloc();
        return static_cast<pointer> (::operator new (n * sizeof (value_type)));
    }

    void deallocate(pointer p, size_type n) {
        OPENSSL_cleanse(p, n*sizeof(T));
        ::operator delete(p);
    }

    size_type max_size() const {
        return std::numeric_limits<size_type>::max() / sizeof (T);
    }

    template<typename U>
    struct rebind
    {
        typedef zallocator<U> other;
    };

    void construct (pointer ptr, const T& val) {
        new (static_cast<T*>(ptr) ) T (val);
    }

    void destroy(pointer ptr) {
        static_cast<T*>(ptr)->~T();
    }

#if __cpluplus >= 201103L
    template<typename U, typename... Args>
    void construct (U* ptr, Args&&  ... args) {
        ::new (static_cast<void*> (ptr) ) U (std::forward<Args> (args)...);
    }

    template<typename U>
    void destroy(U* ptr) {
        ptr->~U();
    }
#endif
};
//End From https://wiki.openssl.org/index.php/EVP_Symmetric_Encryption_and_Decryption

typedef unsigned char byte;
typedef std::basic_string<char, std::char_traits<char>, zallocator<char> > secure_string;
using EVP_CIPHER_CTX_free_ptr = std::unique_ptr<EVP_CIPHER_CTX, decltype(&::EVP_CIPHER_CTX_free)>;

AES::AES() {
    EVP_add_cipher(EVP_aes_256_cbc());
}

//Kod z https://wiki.openssl.org/index.php/EVP_Symmetric_Encryption_and_Decryption
string AES::encrypt(string msg) {
    secure_string ptext(msg.c_str());
    secure_string ctext;

    secure_string msgSecureStr(msg.c_str());
    EVP_CIPHER_CTX_free_ptr ctx(EVP_CIPHER_CTX_new(), ::EVP_CIPHER_CTX_free);
    int rc = EVP_EncryptInit_ex(ctx.get(), EVP_aes_256_cbc(), NULL, (const unsigned char *) key.c_str(),
                                (const unsigned char *) initVector.c_str());
    if (rc != 1)
        throw std::runtime_error("EVP_EncryptInit_ex failed");

    // Recovered text expands upto BLOCK_SIZE
    ctext.resize(ptext.size()+BLOCK_SIZE);
    int out_len1 = (int)ctext.size();

    rc = EVP_EncryptUpdate(ctx.get(), (byte*)&ctext[0], &out_len1, (const byte*)&ptext[0], (int)ptext.size());
    if (rc != 1)
        throw std::runtime_error("EVP_EncryptUpdate failed");

    int out_len2 = (int)ctext.size() - out_len1;
    rc = EVP_EncryptFinal_ex(ctx.get(), (byte*)&ctext[0]+out_len1, &out_len2);
    if (rc != 1)
        throw std::runtime_error("EVP_EncryptFinal_ex failed");

    // Set cipher text size now that we know it
    ctext.resize(out_len1 + out_len2);

    //TODO: funguje to spravne???
    string result(ctext.c_str());

    return result;
}

//Kod z https://wiki.openssl.org/index.php/EVP_Symmetric_Encryption_and_Decryption
string AES::decrypt(string msg) {
    secure_string ctext(msg.c_str());
    secure_string rtext;

    EVP_CIPHER_CTX_free_ptr ctx(EVP_CIPHER_CTX_new(), ::EVP_CIPHER_CTX_free);
    int rc = EVP_DecryptInit_ex(ctx.get(), EVP_aes_256_cbc(), NULL, (const unsigned char *) key.c_str(),
                                (const unsigned char *) initVector.c_str());
    if (rc != 1)
        throw std::runtime_error("EVP_DecryptInit_ex failed");

    // Recovered text contracts upto BLOCK_SIZE
    rtext.resize(ctext.size());
    int out_len1 = (int)rtext.size();

    rc = EVP_DecryptUpdate(ctx.get(), (byte*)&rtext[0], &out_len1, (const byte*)&ctext[0], (int)ctext.size());
    if (rc != 1)
        throw std::runtime_error("EVP_DecryptUpdate failed");

    int out_len2 = (int)rtext.size() - out_len1;
    rc = EVP_DecryptFinal_ex(ctx.get(), (byte*)&rtext[0]+out_len1, &out_len2);
    if (rc != 1){
        ERR_print_errors_fp(stderr);
        throw std::runtime_error("EVP_DecryptFinal_ex failed");
    }

    // Set recovered text size now that we know it
    rtext.resize(out_len1 + out_len2);

    //TODO: funguje to spravne???
    string result(rtext.c_str());

    return result;
}

void AES::setKey(const string &key) {
    AES::key = key;
}

void AES::setInitVector(const string &initVector) {
    AES::initVector = initVector;
}

string AES::converBytesToStr(unsigned char *bytes, int length) {
    return std::__cxx11::string();
}

unsigned char *AES::convertStrToBytes(string str) {
    return nullptr;
}
