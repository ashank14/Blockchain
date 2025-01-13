#ifndef UTXOSET_H
#define UTXOSET_H

#include <unordered_map>
#include <string>
using namespace std;


class Outpoint{
    public:
    string txid;
    int index;
    bool operator==(const Outpoint &other) const {
        return txid == other.txid && index == other.index;
    }
};
namespace std {
    template <>
    struct hash<Outpoint> {
        std::size_t operator()(const Outpoint &outpoint) const {
            return hash<string>()(outpoint.txid) ^ hash<int>()(outpoint.index);
        }
    };
}

class Output{
    public:
    double amount;
    string scriptPubKey;
};


class Input{
    public:
    Outpoint prevOut;
    string scriptSig;
};



class Coin{
    public:
    Output txout;
    string height;
    bool isCoinbase;
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