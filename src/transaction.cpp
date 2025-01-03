#include "transaction.h"
#include "util.h"
#include "utxoSet.h"

#include <iostream>

using namespace std;
using namespace util;

void Transaction::createTxn(Utxoset& utxoset,vector<Outpoint>avlUtxos,const string&from,const string&recipient,double amount,const string&scriptSig){

    //get the scriptPubKey from the senders and recipients address
    string scriptPubKey=addressToSPK(recipient);
    string scriptPubKeyChange=addressToSPK(from);

    
    //i have the available utxos from the main function
    //now, ask the user what utxos out of the ones he has and what he wants to use as inputs
    //set inputs
    int f=0;
    double amt=0;
    string txid;
    int index;

    while(f!=-1||amt>=amount){
        cout<<"Enter transaction id: ";
        cin>>txid;
        cout<<" Enter index: ";
        cin>>index;
        cout<<endl;

        //find amount associated with the utxo
        for(int i=0;i<avlUtxos.size();i++){
            if(txid==avlUtxos[i].txid&&index==avlUtxos[i].index){
                Outpoint prevOut=avlUtxos[i];
                Input input;
                input.prevOut=prevOut;
                input.scriptSig=scriptSig;

                Coin* c=utxoset.findCoin(prevOut);
                string scriptPubKey=c->txout.scriptPubKey;

                if(verify(scriptPubKey,scriptSig)){
                    inputs.push_back(input);
                    amt+=c->txout.amount;
                }
                break;
            }
        }

        
        cout<<"Sum of UTXOS: "<<amt<<endl;

        cout<<"Enter -1 to end/0 to continue: ";
        cin>>f;
        if(amt<amount){
            cout<<"Sum of inputs less than amount to be sent. Add more inputs";
            f=0;
        }
    }

    //set outptuts
    double change=amount-amt;

    Output out;
    out.amount=amount;
    out.scriptPubKey=scriptPubKey;
    outputs.push_back(out);
    if(change>0){
        Output outChange;
        outChange.amount=change;
        outChange.scriptPubKey=scriptPubKeyChange; 
        outputs.push_back(outChange);
    }

}