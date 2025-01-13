#include "block.h"

void Block::displayblock(){
    cout<<header.version<<endl;
    for(auto i:this->txHash){
        cout<<i<<endl;
    }
}