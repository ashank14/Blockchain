#include "mempool.h"
#include "util.h"

using namespace std;
using namespace util;

void Mempool::addTxn(Transaction txn){
    //add the transaction to the mempool
    txns.push(txn);
    //add the inputs of the transaction to the map(To track unconfirmed txn inputs)
    for(const Input&input:txn.inputs){
        mapNextTx.insert(input.prevOut);
    }
}


//Validate the transaction i.e check if the transaction uses any inputs that are still in an unconfirmed transaction
bool Mempool::validateTxn(Transaction &tx, Utxoset &utxoset) {
    // Loop through each input to validate it
    for (const Input &input : tx.inputs) {
        // Check if the input is already in use in the mempool
        if (mapNextTx.count(input.prevOut) > 0) {
            // The input is already being used in another unconfirmed transaction in the mempool
            return false;
        }

        // Use findCoin to check if the input's Outpoint exists in the utxoset
        Coin* coin = utxoset.findCoin(input.prevOut);
        if (!coin) {
            // The input does not exist in the utxoset, meaning it has already been spent or is invalid
            return false;
        }

        // Optionally: Ensure that the input's scriptSig can unlock the scriptPubKey
        // validate the scriptSig and scriptPubKey using the verify function here.
        string scriptPubKey = coin->txout.scriptPubKey;
        if (!verify(scriptPubKey, input.scriptSig)) {
            // If the scriptSig doesn't match the scriptPubKey, the transaction is invalid
            return false;
        }
    }

    return true;
}