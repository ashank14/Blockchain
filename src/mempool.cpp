#include "mempool.h"

void mempool::addTxn(Transaction txn){
    txns.push_back(txn);
}