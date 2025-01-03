#ifndef UTXOSET_H
#define UTXOSET_H

#include "transaction.h"
#include <unordered_map>
using namespace std;



class Coin{
    public:
    Output txout;
    string height;
    bool isCoinbaase;
};

class Utxoset{
    public:
    unordered_map<Outpoint,Coin>utxoset;

    void addUTXO(const Outpoint& outpoint, const Coin& coin);
    void removeUTXO(const Outpoint& outpoint);
    vector<Outpoint> getUtxos(string scriptPubKey);
    Coin* findCoin(const Outpoint &outpoint);
};

#endif