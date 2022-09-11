#include "signer.h"

#include <fstream>
#include <sstream>

namespace block_chain
{
    void Base64Encode(unsigned char *buffer, size_t length, char **base64Text)
    {
        BIO *bio, *b64;
        BUF_MEM *bufferPtr;

        b64 = BIO_new(BIO_f_base64());
        bio = BIO_new(BIO_s_mem());
        bio = BIO_push(b64, bio);

        BIO_write(bio, buffer, length);
        BIO_flush(bio);
        BIO_get_mem_ptr(bio, &bufferPtr);
        BIO_set_close(bio, BIO_NOCLOSE);
        BIO_free_all(bio);

        *base64Text = (*bufferPtr).data;
    }

    size_t CalcDecodeLength(const char *b64input)
    {
        size_t len = strlen(b64input), padding = 0;

        if (b64input[len - 1] == '=' && b64input[len - 2] == '=')
            padding = 2;
        else if (b64input[len - 1] == '=')
            padding = 1;
        return (len * 3) / 4 - padding;
    }

    void Base64Decode(const char *b64message, unsigned char **buffer, size_t *length)
    {
        BIO *bio, *b64;

        int decodeLen = CalcDecodeLength(b64message);
        *buffer = (unsigned char *)malloc(decodeLen + 1);
        (*buffer)[decodeLen] = '\0';

        bio = BIO_new_mem_buf(b64message, -1);
        b64 = BIO_new(BIO_f_base64());
        bio = BIO_push(b64, bio);

        *length = BIO_read(bio, *buffer, strlen(b64message));
        BIO_free_all(bio);
    }

    string read_file(const string file_name)
    {
        std::ifstream file(file_name);
        std::stringstream buffer;
        buffer << file.rdbuf();
        return buffer.str();
    }

    string Signer::sign(const string message)
    {
        unsigned char *encrypted_message_ptr;
        size_t encrypted_message_length;
        EVP_MD_CTX *m_RSASignCtx = EVP_MD_CTX_create();
        EVP_PKEY *priKey = EVP_PKEY_new();
        EVP_PKEY_assign_RSA(priKey, private_rsa);
        EVP_DigestSignInit(m_RSASignCtx, NULL, EVP_sha256(), NULL, priKey);
        EVP_DigestSignUpdate(m_RSASignCtx, message.c_str(), message.length());
        EVP_DigestSignFinal(m_RSASignCtx, NULL, &encrypted_message_length);
        encrypted_message_ptr = (unsigned char *)malloc(encrypted_message_length);
        EVP_DigestSignFinal(m_RSASignCtx, encrypted_message_ptr, &encrypted_message_length);
        char *base64Text;
        Base64Encode(encrypted_message_ptr, encrypted_message_length, &base64Text);
        free(m_RSASignCtx);
        free(encrypted_message_ptr);
        return base64Text;
    }
    bool Signer::verify(const string encrypted_message, const string message)
    {
        EVP_PKEY *pubKey = EVP_PKEY_new();
        EVP_PKEY_assign_RSA(pubKey, public_rsa);
        EVP_MD_CTX *m_RSAVerifyCtx = EVP_MD_CTX_create();

        EVP_DigestVerifyInit(m_RSAVerifyCtx, NULL, EVP_sha256(), NULL, pubKey);
        EVP_DigestVerifyUpdate(m_RSAVerifyCtx, message.c_str(), message.length());

        unsigned char *encMessage;
        size_t encMessageLength;

        Base64Decode(encrypted_message.c_str(), &encMessage, &encMessageLength);
        int authStatus = EVP_DigestVerifyFinal(m_RSAVerifyCtx, encMessage, encMessageLength);
        free(m_RSAVerifyCtx);
        return authStatus;
    }

    void Signer::init_rsa(const string private_key_file, const string public_key_file)
    {
        string private_key = read_file(private_key_file);
        BIO *private_keybio = BIO_new_mem_buf((void *)private_key.c_str(), -1);
        private_rsa = PEM_read_bio_RSAPrivateKey(private_keybio, &private_rsa, NULL, NULL);

        string public_key = read_file(public_key_file);
        BIO *public_keybio = BIO_new_mem_buf((void *)public_key.c_str(), -1);
        public_rsa = PEM_read_bio_RSA_PUBKEY(public_keybio, &public_rsa, NULL, NULL);
    }

}
