#include "mempool.h"

void Mempool::addTxn(Transaction txn){
    txns.push(txn);
}