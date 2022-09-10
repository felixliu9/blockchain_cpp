#ifndef BLOCKCHAIN_BLOCK_H_
#define BLOCKCHAIN_BLOCK_H_

#include <chrono>
#include <string>

namespace block_chain
{
    using namespace std;
    using chrono::system_clock;

    static const int PREFIX_ZERO_COUNT = 3;

    class Block
    {
    private:
        string data;
        time_t timestamp;
        string hash;
        string prev_hash;
        int salt = 0;

    public:
        Block()
        {
            timestamp = system_clock::to_time_t(system_clock::now());
            hash = "";
            prev_hash = "";
        }
        Block(string data) : data(data)
        {
            timestamp = system_clock::to_time_t(system_clock::now());
            hash = "";
            prev_hash = "";
        }
        ~Block() {}

        string get_data() { return data; }
        string get_hash() { return hash; }
        string get_prev_hash() { return prev_hash; }
        time_t get_timestamp() { return timestamp; }
        void set_data(string data) { this->data = data; }
        void set_hash(string hash) { this->hash = hash; }
        void set_prev_hash(string hash) { this->prev_hash = hash; }
        void mining();
        string calculate_hash_md5();
        string calculate_hash_sha256();
        bool is_valid();
    };
};
#endif