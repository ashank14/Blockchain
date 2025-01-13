// util.h
#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <vector>
#include <openssl/ecdsa.h>
#include <openssl/obj_mac.h>
#include <openssl/evp.h>
#include <openssl/pem.h>

using namespace std;

namespace util {
    
    // Utility function for getting pkh from address
    string addressToSPK(const string &address);

    //Utility function for verifying Digital Signature against Public Key Script
    bool verify(string digitalSig,string scriptPubKey);

    //generate digital signature for a message
    string sign(const std::string& txHash, const std::string& privateKey);

    string sha256(const string& data);

    string sha256Binary(const string& data);


} 

#endif
