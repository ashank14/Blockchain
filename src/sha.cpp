#include <openssl/sha.h>
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

// Function to calculate SHA256 and return raw binary
std::string sha256(const std::string& data) {
    unsigned char hash[SHA256_DIGEST_LENGTH]; // Buffer to hold the hash
    SHA256(reinterpret_cast<const unsigned char*>(data.c_str()), data.size(), hash);
    
    // Convert the hash to a hexadecimal string
    std::ostringstream hexStream;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        hexStream << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
    }
    return hexStream.str();
}
int main(){
    string s="hello";
    cout<<sha256(s);
    return 0;
}