#include <thread>
#include "blockchain.h"
#include "block.h"
#include "blockHeader.h"
#include "transaction.h"
#include "transaction.h"
#include "mempool.h"
#include "mining.h"
#include "generateKeypair.h"
#include "utxoSet.h"
#include <string>
#include "util.h"
#include <iostream>

using namespace util;
using namespace std;

int main(){

    // Initialize the blockchain
    Blockchain blockchain;
    //Create the genesis block
    blockHeader BH("version","#0","hashMerkleRoot",10,10,2);
    Block newBlock(BH);
    blockchain.blockchain.push_back(newBlock);

    cout<<"Genesis block created"<<endl;
    blockchain.displayBlockchain();
    //Initialize a UTXO set
    Utxoset u;
    //Put initial utxos in the set

    // Initializing a memory pool
    Mempool m; 

    // Initialize the mining class (send mempool and blockchain to Mining)
    Mining mine(&m,&blockchain,&u); 

    // Run the mining in a SEPARATE THREAD, so the main thread listens for new txns 
    std::thread miningThread(&Mining::mine, &mine);

    
    string from;
    string scriptSig;
    string to;
    string sig;
    string privateKey;
    string publicKey;
    double amount;
    bool enter=1;
    
    // Input transactions
    while(enter){
        cout << "Enter sender's wallet address: ";
        cin >> from;
        cout << endl;
        cout << "Enter sender's public Key: ";
        cin >> publicKey;
        cout << endl;
        cout<<"Enter private key: ";
        cin>>privateKey;
        cout<<endl;
        //Get scriptPubKey from sender's wallet address
        string scriptPubKey=addressToSPK(from);

        //Get UTXOs associated with the sender's wallet address
        cout<<"Your UTXOs are: "<<endl;
        vector<Outpoint>avlUtxos=u.getUtxos(scriptPubKey);

        cout << "Enter recipient's wallet address: ";
        cin >> to;
        cout << endl;
        cout << "Enter amount to be sent: ";
        cin >> amount;
        cout << endl;
        cout<<"Enter your scriptSig: ";
        cin>>scriptSig;
        cout<<endl;

        //Creating an unsigned transaction
        Transaction tx; 
        tx.createTxn(u,avlUtxos,from,to,amount); 
        
        //serialize and hash the transaction
        string serializedTxn=tx.serializeTxn();
        
        //sign the transaction
        string digitalSignature=sign(serializedTxn,privateKey);

        //add the scriptsig to the inputs of the  transaction
        for(Input input:tx.inputs){
            input.scriptSig=digitalSignature+" "+publicKey;
        }
        

        //Validate the transaction i.e check if the transaction uses any inputs that are still in an unconfirmed transaction or are not in the utxo set
        if(m.validateTxn(tx,u)){
            m.addTxn(tx); // Adding the transaction to the mempool
            cout << "Transaction added to mempool" << endl;
        }else{
            cout<<"Failed to validate the transaction"<<endl;
        };
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
