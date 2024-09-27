#ifndef MINING_H
#define MINING_H

#include "mempool.h"
#include "blockchain.h"


class Mining{
    public:
        Mempool* m;
        Blockchain *blockchain;
        bool mineFlag;
        //Mining class has access to the mempool and blockchain
        Mining(Mempool* pool,Blockchain*chain){
            m=pool;
            blockchain=chain;
            mineFlag=true;
        }
        void mine();
};
#endif