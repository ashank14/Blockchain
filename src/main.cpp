#include <thread>
#include "blockchain.h"
#include "block.h"
#include "blockHeader.h"
#include "transaction.h"
#include "mempool.h"
#include "mempool.cpp"
#include "mining.h"
#include "blockchain.h"

#include <string>
#include <iostream>

using namespace std;

int main(){
    string from;
    string to;
    int amount;
    int enter=1;

    // Initialize the blockchain
    Blockchain blockchain;

    // Initializing a memory pool
    Mempool m; 

    // Initialize the mining class (send mempool and blockchain to Mining)
    Mining mine(&m,&blockchain); 

    // Run the mining in a SEPARATE THREAD, to listen for new txns concurrently
    std::thread miningThread(&Mining::mine, &mine);
    
    // Mining thread runs independently
    miningThread.detach();

    // Input transactions
    while(enter){
        cout << "Enter sender's wallet address: ";
        cin >> from;
        cout << endl;
        cout << "Enter recipient's wallet address: ";
        cin >> to;
        cout << endl;
        cout << "Enter amount to be sent: ";
        cin >> amount;
        cout << endl;
        Transaction txn(from, to, amount); // Creating a transaction
        m.addTxn(txn); // Adding the transaction to the mempool
        cout << "Transaction added to mempool" << endl;
        cout << "Enter 0 to quit/1 to continue: ";
        cin >> enter;
        cout << endl;
    }
}
