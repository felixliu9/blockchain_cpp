#ifndef BLOCKCHAIN_H_
#define BLOCKCHAIN_H_

#include <string>
#include <vector>
#include "block.h"

namespace block_chain
{
    using namespace std;

    // BlockChain class represents chain of blocks. Major functions to create, verify, and validate blocks
    class BlockChain
    {
    public:
        // creates new block with specified data at the end of the chain
        void create_block(string data);

        // verifies a specific block on the chain
        bool verify_block(Block & block);

        // verifies all blocks in the whole chain
        bool validate_blocks();
        Block get_block(int index);
        BlockChain() {}
        ~BlockChain() {}

    private:
        vector<Block> blocks;
    };
};
#endif //BLOCKCHAIN_H_