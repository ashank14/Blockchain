#include <thread>
#include "blockchain.h"
#include "block.h"
#include "blockHeader.h"
#include "transaction.h"
#include "mempool.h"
#include "mining.h"
#include "blockchain.h"
#include "generateKeypair.h"
#include <string>
#include <iostream>

using namespace std;

int main(){

    bool i;
    cout<<"Enter 1 to generate a public-private key pair(Wallet address)/0 to start a transaction: ";
    cin>>i;
    cout<<endl;
    if(i){
        cout<<"Key Pair :"<<endl;
        generateRSAKeyPair(2048);
        
        return 0;
    }
    string from;
    string to;
    int amount;
    bool enter=1;

    // Initialize the blockchain
    Blockchain blockchain;

    // Initializing a memory pool
    Mempool m; 

    // Initialize the mining class (send mempool and blockchain to Mining)
    Mining mine(&m,&blockchain); 

    // Run the mining in a SEPARATE THREAD, to listen for new txns concurrently
    std::thread miningThread(&Mining::mine, &mine);
    
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
        cout << "Enter 0 to quit/1 to continue: "<<endl;
        cin >> enter;
        cout << endl;
    }
    //Stop input
    //Signal to stop mining if mempool empty
    mine.mineFlag=false;
    //Wait for mining to complete for remaining transactions in the mempool
    miningThread.join();
}
