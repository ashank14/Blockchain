#include "mempool.h"
#include "mining.h"
#include "transaction.h"
#include "blockHeader.h"
#include "block.h"
#include "blockchain.h"
#include "util.h"
#include <chrono>
#include <thread>
#include <string>

using namespace std;
using namespace util;

void Mining::mine(){
    //Infinite loop for checking new transactions in mempool
    while(true){
        //get the hash for the previous block
        string prevhash=blockchain->blockchain.back().header.hashPrev;
        //Create a header for the candidate block
        blockHeader BH("version",prevhash,"hashMerkleRoot",10,10,2);
        //Initialize the Candidate block with the header
        Block newBlock(BH);
        //Include 2 transactions in a block
        vector<Transaction>memTxns;
        int i=0;
	    bool f=false;
        while(i<2&&!m->txns.empty()){
	        f=true;
            //Get txn from mempool
            Transaction tx=m->txns.front();
            //add to memTxns
            memTxns.push_back(tx);
            i++;
            m->txns.pop();
        }
        //If transactions available in mempool
        if(f){
            //Add transactions to candidate block
            newBlock.transactions=memTxns;

            cout<<"Mining started"<<endl;
            //set 15 second timer to simulate mining (Pause), replace later with actual mining logic
            this_thread::sleep_for(chrono::seconds(15));	

            //Remove the UTXOs which were sent as inputs and create new UTXOs sent as outputs

            for(Transaction&t:memTxns){
                //Remove each Input of every transaction
                for(const Input&i:t.inputs){
                    utxoset->removeUTXO(i.prevOut);
                }
                
                
                //serialize the transaction for the transaction id
                string txid=sha256(sha256Binary(t.serializeTxn()));
                newBlock.txHash.push_back(txid);
                
                //Create new UTXOs which were sent as outputs
                int index=1;
                for(const Output&o:t.outputs){
                    Coin c;
                    c.txout=o;
                    Outpoint op;
                    op.index=index;
                    op.txid=txid;
                    utxoset->addUTXO(op,c);
                    index++;

                }
            }

            //Add the block to the blockchain
            blockchain->blockchain.push_back(newBlock);
            cout<<"Block added to the Blockchain"<<endl;
            blockchain->displayBlockchain();
            cout<<endl;


        }

        //If no new inputs and mempool empty, stop mining
        if(m->txns.empty()&&!mineFlag){
            cout<<"Mempool empty...Stop mining"<<endl;
            break;
        }

    }
}
