#ifndef BLOCKHEADER_H
#define BLOCKHEADER_H

#include <string>
using namespace std;

class blockHeader{
    public:
        string version;
        string hashPrev;
        string hashMerkleRoot;
        int timestamp;
        int difficulty;
        int nonce;
        blockHeader(){}
        blockHeader(string version,string hashPrev,string hashMerkleRoot,int timestamp,int difficulty, int nonce){
            this->version=version;
            this->hashPrev=hashPrev;
            this->hashMerkleRoot=hashMerkleRoot;
            this->timestamp=timestamp;
            this->difficulty=difficulty;
            this->nonce=nonce;
        }
};

#endif