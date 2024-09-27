#include "mempool.h"
#include "mining.h"
#include "transaction.h"
#include "blockHeader.h"
#include "block.h"
#include "blockchain.h"
#include <chrono>
#include <thread>

using namespace std;

void Mining::mine(){
    //Infinite loop for checking new transactions in mempool
    while(true){
        //Create a header for the candidate block
        blockHeader BH("version","hashPrev","hashMerkleRoot",10,10,2);
        //Initialize the Candidate block with the header
        Block newBlock(BH);
        //Include 2 transactions in a block
        vector<Transaction>memTxns;
        int i=0;
        while(i<2&&!m->txns.empty()){
            //Get txn from mempool
            Transaction tx=m->txns.front();
            //add to memTxns
            memTxns.push_back(tx);
            i++;
            m->txns.pop();
        }

        //Add transactions to candidate block
        newBlock.transactions=memTxns;

        cout<<"Mining started"<<endl;
        //set 2 minute timer to simulate mining (Pause), replace later with actual mining logic
	this_thread::sleep_for(chrono::minutes(1));	        

        //Add the block to the blockchain
        blockchain->blockchain.push_back(newBlock);
	cout<<"Block added to the Blockchain"<<endl;

    }
}
