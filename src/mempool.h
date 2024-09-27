#ifndef MEMPOOL_H
#define MEMPOOL_H
#include <string>
#include "transaction.h"
#include <queue>
class Mempool{
    public:
        queue<Transaction>txns; //Queue for now, will change to a something similar to a priority queue
        void addTxn(Transaction txn);
};

#endif