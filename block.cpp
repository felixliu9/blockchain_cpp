#include "block.h"
#include <chrono>
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>

#include "openssl/md5.h"
#include "openssl/sha.h"

namespace block_chain
{
    using namespace std;
    using chrono::system_clock;
    static const string HASH_PREFIX = "00";
    void Block::mining()
    {
        hash = calculate_hash_sha256();
        while (hash.substr(0, HASH_PREFIX.length()) != HASH_PREFIX)
        {
            salt++;
            hash = calculate_hash_sha256();
        }
    }
    string Block::calculate_hash_md5()
    {
        string toHash = data + ctime(&timestamp) + prev_hash + to_string(salt);
        unsigned char digest[MD5_DIGEST_LENGTH];

        MD5((unsigned char *)&toHash, toHash.length(), (unsigned char *)&digest);

        char mdString[33];

        for (int i = 0; i < 16; i++)
            sprintf(&mdString[i * 2], "%02x", (unsigned int)digest[i]);

        return mdString;
    }

    string Block::calculate_hash_sha256()
    {
        string toHash = data + ctime(&timestamp) + prev_hash + to_string(salt);
        unsigned char digest[SHA256_DIGEST_LENGTH];
        SHA256_CTX sha256;
        SHA256_Init(&sha256);
        SHA256_Update(&sha256, toHash.c_str(), toHash.size());
        SHA256_Final(digest, &sha256);
        stringstream ss;
        for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
        {
            ss << hex << setw(2) << setfill('0') << (int)digest[i];
        }
        return ss.str();
    }

    bool Block::is_valid()
    {
        return this->hash == this->calculate_hash_sha256();
    }

};
