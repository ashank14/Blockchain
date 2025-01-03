#include "blockchain.h"
#include <vector>
void Blockchain::displayBlockchain() {
    cout<<"Current Blockchain:";
    for (auto i:blockchain) {
        cout<<i.header.hashPrev<<" ";
    }
}
