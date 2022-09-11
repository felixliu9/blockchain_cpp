#ifndef BLOCKCHAIN_H_
#define BLOCKCHAIN_H_

#include <string>
#include <vector>
#include "block.h"
#include "signer.h"

namespace block_chain
{
    using namespace std;

    class BlockChain
    {
    public:
        void create_block(string data);
        bool verify_block(Block & block);
        bool validate_blocks();
        Block get_block(int index);
        void init_signer(const string private_key_file, const string public_key_file);
        BlockChain() {}
        ~BlockChain() {}

    private:
        vector<Block> blocks;
        Signer signer;
    };
};
#endif //BLOCKCHAIN_H_