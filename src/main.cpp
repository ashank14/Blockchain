#include "blockchain.h"
#include "block.h"
#include "blockHeader.h"
#include "transaction.h"
#include "mempool.h"
#include "mempool.cpp"
#include <string>
#include <iostream>

using namespace std;

int main(){
    string from;
    string to;
    int amount;
    int enter=1;
    mempool m;
    while(enter){
        cout<<"Enter sender's wallet address: ";
        cin>>from;
        cout<<endl;
        cout<<"Enter recepient's wallet address: ";
        cin>>to;
        cout<<endl;
        cout<<"Enter amount to be sent: ";
        cin>>amount;
        cout<<endl;
        Transaction txn(from,to,amount);
        m.addTxn(txn);
        cout<<"transaction added to mempool";
        cout<<"Enter 0 to quit/1 to continue: ";
        cin>>enter;
        cout<<endl;
    }
    cout<<"Memory pool: "<<endl;
    for(int i=0;i<m.txns.size();i++){
        cout<<m.txns[i].from<<" "<<m.txns[i].to<<" "<<m.txns[i].amount<<endl;
    }
}
