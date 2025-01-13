#include "utxoSet.h"
#include "transaction.h"
#include "util.h"
#include <iostream>

using namespace std;
using namespace util;

vector<Outpoint> Utxoset::getUtxos(string scriptPubKey){
    
    //Check input scriptpubkey across scriptpubkey of all UTXOs to get the UTXOs associated to it
    vector<Outpoint>utxos;
    for(auto i=utxoset.begin();i!=utxoset.end();i++){
        if(scriptPubKey==i->second.txout.scriptPubKey){
            cout<<"Transaction id: "<<i->first.txid<<" Output index: "<<i->first.index<<" Amount: "<<i->second.txout.amount<<endl;         
            utxos.push_back(i->first);   
        }

    }
    return utxos;

}


void Utxoset::
removeUTXO(const Outpoint& outpoint){
    utxoset.erase(outpoint);
}

Coin* Utxoset::findCoin(const Outpoint &outpoint) {
        auto it = utxoset.find(outpoint);
        if (it != utxoset.end()) {
            return &it->second; // Coin found, return pointer to it
        }
        return nullptr; // Coin not found
    }

void Utxoset::addUTXO(const Outpoint& outpoint, const Coin& coin){
    utxoset[outpoint]=coin;
}