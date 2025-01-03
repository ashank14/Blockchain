#ifndef TRANSACTION_H
#define TRANSACTION_K

#include <string>
#include <vector>

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

class Transaction{
    public:
    string version;
    int inputCount;
    vector<Input>inputs;
    int outputCount;
    vector<Output>outputs;
    int locktime;

    void createTxn(Utxoset& utxoset,vector<Outpoint>avlUtxos,const string&from,const string&recipient,double amount,const string&scriptSig);

};


#endif 