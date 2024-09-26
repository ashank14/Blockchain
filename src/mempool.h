#ifndef MEMPOOL_H
#define MEMPOOL_H
#include <string>
#include "transaction.h"
#include <vector>
class mempool{
    public:
        vector<Transaction>txns;
        void addTxn(Transaction txn);
};

#endif