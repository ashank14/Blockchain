// util.h
#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <vector>
using namespace std;

namespace util {
    
    // Utility function for getting pkh from address
    string addressToSPK(const string &address);

    //Utility function for verifying Digital Signature against Public Key Script
    bool verify(string digitalSig,string scriptPubKey);


} 

#endif
