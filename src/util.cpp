// util.cpp
#include "util.h"
#include <iostream>
#include <string>
#include <sstream>
#include <openssl/sha.h>
#include <openssl/ripemd.h>
#include <iomanip>

using namespace std;

namespace util {

    
    //convert address to pkh
    string addressToSPK(string &address) {
        
        return "OP_DUP OP_HASH160 <pubKeyHash> OP_EQUALVERIFY OP_CHECKSIG";
    }

    string toHexString(const unsigned char* data, size_t length) {
        ostringstream oss;
        for (size_t i = 0; i < length; ++i) {
            oss << hex << std::setw(2) << std::setfill('0') << (int)data[i];
        }
        return oss.str();
    }

    string sha256Binary(string& data) {
        unsigned char hash[SHA256_DIGEST_LENGTH];
        SHA256(reinterpret_cast<const unsigned char*>(data.c_str()), data.size(), hash);
        return string(reinterpret_cast<char*>(hash), SHA256_DIGEST_LENGTH); // Binary
    }
    string sha256(const string& data) {
        unsigned char hash[SHA256_DIGEST_LENGTH]; // Buffer to hold the hash
        SHA256(reinterpret_cast<const unsigned char*>(data.c_str()), data.size(), hash);
        
        // Convert the hash to a hexadecimal string
        ostringstream hexStream;
        for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
            hexStream << hex << setw(2) << setfill('0') << static_cast<int>(hash[i]);
        }
        return hexStream.str();
    }

    string hash160(const std::string& input) {
        // SHA-256 hash of the input
        unsigned char sha256Hash[SHA256_DIGEST_LENGTH];
        SHA256_CTX sha256Context;
        SHA256_Init(&sha256Context);
        SHA256_Update(&sha256Context, input.c_str(), input.length());
        SHA256_Final(sha256Hash, &sha256Context);

        // RIPEMD-160 hash of the SHA-256 hash
        unsigned char ripemd160Hash[RIPEMD160_DIGEST_LENGTH];
        RIPEMD160(sha256Hash, SHA256_DIGEST_LENGTH, ripemd160Hash);

        // Convert the hash to a hexadecimal string
        return toHexString(ripemd160Hash, RIPEMD160_DIGEST_LENGTH);
    }

    string sign(const std::string& txHash, const std::string& privateKey) {
        // Step 1: Load the private key
        BIO* bio = BIO_new_mem_buf(privateKey.data(), -1);
        if (!bio) {
            throw std::runtime_error("Failed to create BIO");
        }
        EVP_PKEY* pkey = PEM_read_bio_PrivateKey(bio, nullptr, nullptr, nullptr);
        BIO_free(bio);
        if (!pkey) {
            throw std::runtime_error("Failed to load private key");
        }

        // Step 2: Convert txHash to binary
        if (txHash.size() != 64) {
            EVP_PKEY_free(pkey);
            throw std::runtime_error("Invalid transaction hash size");
        }
        unsigned char txHashBin[32];
        for (size_t i = 0; i < 32; i++) {
            txHashBin[i] = std::stoi(txHash.substr(2 * i, 2), nullptr, 16);
        }

        // Step 3: Create an ECDSA signature
        EVP_MD_CTX* ctx = EVP_MD_CTX_new();
        if (!ctx) {
            EVP_PKEY_free(pkey);
            throw std::runtime_error("Failed to create EVP_MD_CTX");
        }

        if (EVP_DigestSignInit(ctx, nullptr, nullptr, nullptr, pkey) <= 0) {
            EVP_MD_CTX_free(ctx);
            EVP_PKEY_free(pkey);
            throw std::runtime_error("Failed to initialize DigestSign");
        }

        size_t sigLen = 0;
        if (EVP_DigestSign(ctx, nullptr, &sigLen, txHashBin, sizeof(txHashBin)) <= 0) {
            EVP_MD_CTX_free(ctx);
            EVP_PKEY_free(pkey);
            throw std::runtime_error("Failed to calculate signature length");
        }

        std::vector<unsigned char> signature(sigLen);
        if (EVP_DigestSign(ctx, signature.data(), &sigLen, txHashBin, sizeof(txHashBin)) <= 0) {
            EVP_MD_CTX_free(ctx);
            EVP_PKEY_free(pkey);
            throw std::runtime_error("Failed to sign transaction hash");
        }

        signature.resize(sigLen);
        EVP_MD_CTX_free(ctx);
        EVP_PKEY_free(pkey);

        // Step 4: Convert the signature to a hexadecimal string
        return string(reinterpret_cast<const char*>(signature.data()), signature.size());
    }

    bool verifySignature(string signature,string publicKey,string message){
        
        return true;
    }

    //Verify scripts
    bool verify(string scriptSig,string scriptPubKey){
        //Scirptpubkey: OP_DUP OP_HASH160 <pubKeyHash> OP_EQUALVERIFY OP_CHECKSIG
        //ScriptSig: <sig> <pubKey>
       
        stack<string>st;
        stringstream scriptStream(scriptSig + " " + scriptPubKey);
        //<sig> <pubKey> OP_DUP OP_HASH160 <pubKeyHash> OP_EQUALVERIFY OP_CHECKSIG
        string token;

        while(scriptStream>>token){
            if(token=="OP_DUP"){
                if(st.empty())  return false;
                st.push(st.top());
            }else if(token=="OP_HASH160"){
                if(st.empty())  return false;
                string top=st.top();
                st.pop();
                st.push(hash160(top));
            }else if(token == "OP_EQUALVERIFY"){
                if (st.size() < 2) return false;
                string value1 = st.top(); 
                st.pop();
                string value2 = st.top();
                st.pop();
                if (value1 != value2) return false;
            }else if(token == "OP_CHECKSIG"){
                if (st.size() < 2) return false;
                string publicKey = st.top(); st.pop();
                string signature = st.top(); st.pop();
                if (!verifySignature(signature, publicKey, "message_to_sign")) return false;
                st.push("true");
            }else{
                st.push(token);
            }   
        }
        return (!st.empty()&&st.top()=="true");
    }

}

