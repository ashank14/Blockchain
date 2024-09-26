#include "block.h"

void Block::displayblock(){
    cout<<header.version<<endl;
    for(auto i:this->transactions){
        cout<<i.from<<" "<<i.to<<" "<<i.amount<<endl;
    }
}