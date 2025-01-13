#ifndef TRANSACTION_H
#define TRANSACTION_H

#include "utxoSet.h"
#include <string>
#include <vector>

using namespace std;



class Transaction{
    public:
    string version;
    int inputCount;
    vector<Input>inputs;
    int outputCount;
    vector<Output>outputs;
    int locktime;

    void createTxn(Utxoset& utxoset,vector<Outpoint>avlUtxos,const string&from,const string&recipient,double amount);
    string serializeTxn();
};


#endif 