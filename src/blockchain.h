#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include <iostream>
#include "block.h"
#include <vector>
using namespace std;

class Blockchain {
    public:
        vector<Block>blockchain;
        void displayBlockchain();
};

#endif
