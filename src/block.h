#ifndef BLOCK_H
#define BLOCK_H
#include <iostream>
#include "blockHeader.h"
#include "transaction.h"
#include <vector>

using namespace std;

class Block{
    public:
        blockHeader header;
        vector<Transaction>transactions;
        void displayblock();
        Block(blockHeader header){
            this->header=header;
        }
};

#endif