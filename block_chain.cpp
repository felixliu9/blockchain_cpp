#include <string>
#include <iostream>
#include <chrono>
#include "block_chain.h"

namespace block_chain
{
    using namespace std;
    using chrono::system_clock;

    void BlockChain::create_block(std::string data)
    {
        Block block(data);
        if (!blocks.empty())
        {
            block.set_prev_hash(blocks.back().get_hash());
        }
        block.mining();
        block.sign(signer);
        if (verify_block(block))
        {
            blocks.push_back(block);
        }
    }

    bool BlockChain::verify_block(Block &block)
    {
        return (block.is_valid(signer));
    }

    bool BlockChain::validate_blocks()
    {
        int size = static_cast<int>(blocks.size());
        for (int i = 0; i < size; ++i)
        {
            if (!blocks[i].is_valid(signer))
            {
                return false;
            }
            if (i != 0)
            {
                if (blocks[i].get_prev_hash() != blocks[i - 1].get_hash())
                {
                    return false;
                }
            }
        }
        return true;
    }

    Block BlockChain::get_block(int index)
    {
        return blocks[index];
    }

    void BlockChain::init_signer(const string private_key_file, const string public_key_file)
    {
        signer.init_rsa(private_key_file, public_key_file);
    }
}

int main(int argc, char *argv[])
{
    block_chain::BlockChain block_chain;
    block_chain.init_signer("privkey.pem", "pubkey.pem");

    block_chain.create_block("transaction 1");
    block_chain.create_block("transaction 2");
    block_chain.create_block("transaction 3");

    for (int i = 0; i < 3; i++)
    {
        block_chain::Block b = block_chain.get_block(i);
        std::cout << b.get_data() << ": " << b.get_hash() << ":" << b.get_signature() << " -> " << b.get_prev_hash() << "\n";
    }

    block_chain::Block b = block_chain.get_block(2);
    b.set_data("transaction 1");
    assert(!block_chain.verify_block(b));
    assert(block_chain.validate_blocks());
}
