#ifndef BLOCKCHAIN_SIGNER_H_
#define BLOCKCHAIN_SIGNER_H_

#include <string>
#include <iostream>
#include <openssl/aes.h>
#include <openssl/evp.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/ssl.h>
#include <openssl/bio.h>
#include <openssl/err.h>

namespace block_chain
{
    using namespace std;

    class Signer
    {
    private:
        RSA *private_rsa = NULL;
        RSA *public_rsa = NULL;

    public:
        string sign(const string message);
        bool verify(const string encrypted_message, const string message);
        void init_rsa(const string private_key_file, const string public_key_file);
        Signer(){}
        ~Signer(){}
    };
};
#endif