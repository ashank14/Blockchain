#include "transaction.h"
#include "utxoSet.h"
#include <iostream>
#include <vector>

using namespace std;

void testTransactionSerialization() {
    // Create UTXO set for testing
    Utxoset utxoset;

    // Prepare some sample UTXOs (coin outputs)
    Outpoint outpoint1 = {"txid1", 0};
    Coin coin1;
    coin1.txout.amount = 10.0;
    coin1.txout.scriptPubKey = "scriptPubKey1";
    coin1.isCoinbase = false;

    Outpoint outpoint2 = {"txid2", 1};
    Coin coin2;
    coin2.txout.amount = 5.0;
    coin2.txout.scriptPubKey = "scriptPubKey2";
    coin2.isCoinbase = false;

    // Add UTXOs to the set
    utxoset.addUTXO(outpoint1, coin1);
    utxoset.addUTXO(outpoint2, coin2);

    // Create a transaction
    Transaction tx;
    string from = "senderAddress";
    string to = "recipientAddress";
    double amount = 7.0;

    // Call createTxn to set up the transaction
    tx.createTxn(utxoset, {outpoint1, outpoint2}, from, to, amount);

    // Print details about the created transaction
    cout << "Serialized Transaction: " << endl;
    cout << tx.serializeTxn() << endl;

    // Test if the transaction serialization works as expected
    string serializedTxn = tx.serializeTxn();
    cout << "Serialized Transaction (Raw): " << serializedTxn << endl;

    // Verify that the serialized output is not empty
    if (!serializedTxn.empty()) {
        cout << "Serialization Test Passed!" << endl;
    } else {
        cout << "Serialization Test Failed!" << endl;
    }
}