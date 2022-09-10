#ifndef BLOCKCHAIN_H_
#define BLOCKCHAIN_H_

#include <string>
#include <vector>
#include "block.h"

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
        BlockChain() {}
        ~BlockChain() {}

    private:
        vector<Block> blocks;
    };
};
#endif //BLOCKCHAIN_H_