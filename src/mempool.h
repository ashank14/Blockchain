#ifndef MEMPOOL_H
#define MEMPOOL_H
#include <string>
#include "transaction.h"
#include <queue>
#include "utxoSet.h"
#include <unordered_set>

class Mempool{
    public:
        queue<Transaction>txns; //Queue for now, will change to a something similar to a priority queue
        unordered_set<Outpoint> mapNextTx; //Tracks inputs of the transactions in the mempool
        bool validateTxn(Transaction &tx,Utxoset&utxoset);
        void addTxn(Transaction tx);
};

#endif