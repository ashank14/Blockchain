#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
using namespace std;

class Transaction{
    public:
        string from;
        string to;
        int amount;
        Transaction(string from,string to, int amount){
            this->from=from;
            this->to=to;
            this->amount=amount;
        }
};


#endif

