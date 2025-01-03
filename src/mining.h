#ifndef MINING_H
#define MINING_H

#include "mempool.h"
#include "blockchain.h"
#include "utxoSet.h"


class Mining{
    public:
        Mempool* m;
        Blockchain *blockchain;
        Utxoset* utxoset;
        bool mineFlag;
        //Mining class has access to the mempool and blockchain
        Mining(Mempool* pool,Blockchain*chain,Utxoset*u){
            m=pool;
            blockchain=chain;
            utxoset=u;
            mineFlag=true;
        }
        void mine();
};
#endif