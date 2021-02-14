#include "xor_bytes.h"

vector<uint8_t> XorBytes(vector<uint8_t> bytes1, vector<uint8_t> bytes2) {
    vector<uint8_t> result;

    for(int i=0; i<bytes1.size(); i++) {
        auto b1 = bytes1.at(i);
        auto b2 = bytes2.at(i);
        result.emplace_back(b1 ^ b2);
    }

    return result;
}