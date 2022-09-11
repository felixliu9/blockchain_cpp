# Blockchain Basic Implementation in C++
This is a quick and simple implementation of blockchain basic functions using C++, including data block structure, creation, hashing, digital 
signing and verification. This project is to help understand the basic concepts and coputational components in Blockchain technology.
## Block Structure
The data block contains minimum required members, including:
- **data**: a text member to hold the transaction message content.
- **timestamp**: a timestamp to represent the time when the block is created
- **prev_hash**: the hash value of previous block
- **salt**: the salt value for calculating hash value, to add some variation in hash calculation
- **hash**: the hash value of the block
- **signature**: the digital signature of the hash value, calculated using the sender's private key and can be verified using the sender's public key by all receivers

## Major Functions
### Create Block
Given transaction data and current data block in the block chain, create a new block and add it to the end of the chain. This includes process to retrieve 
current block from the chain, create new block object, calculating/mining data hash, digital signing the hash and insert the verified block to the end 
of the chain. 
### Mining Block
### Verify Individual Block
Verify individual block to make sure the hash matches with the block contents and the signature is correct.
### Verify Block Chain

## OpenSSL API
[OpenSSL API](https://github.com/openssl/openssl) is used in this project for data hashing and digital signing functions. 
### Build & Installation
Here is a quick howto to build and install OpenSSL in Unix/Linux/macOS. For more details, please read 
[OpenSSL build and installation](https://github.com/openssl/openssl/blob/master/INSTALL.md).

```
$ cd ~
$ git clone https://github.com/openssl/openssl.git
$ cd openssl
$ ./Configure
$ make
$ make install
```
Once done, OpenSSL includes and libs should be installed into the system include and lib folder.
### Usage
To use OpenSSL API, add the /usr/local/include folder into the project configuration. Also to add -lcrypto option in C++ compilation/link command line, 
for example: 
```
g++ -std=c++11 block.cpp block_chain.cpp -lcrypto
```
