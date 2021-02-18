#include <string>
#include <vector>
#include <iostream>

#include "encoder.h"

#include "hex_to_bytes.h"
#include "bytes_to_hex.h"
#include "bytes_to_base64.h"

using namespace std;

void Encoder::SetInputFromHexString(string input) {
    if((input.size()%2) != 0 ) {
        input = '0' + input;
    }

    _bytes.clear();
    _bytes.resize(input.size()/2);

    for(int i = 0; i < _bytes.size(); i++) {
        auto key = input.substr(2*i, 2);
        _bytes.at(i) = hex_to_bytes[key];
    }
}

void Encoder::SetInputFromBytes(vector<uint8_t> input) {
    _bytes = input;
}

string Encoder::GetOutputAsHexString() {
    string result = "";
    for(auto &b : _bytes) 
    {
        result = result + bytes_to_hex[b];
    }
    return result;
}

string Encoder::GetOutputAsASCII() {
    string result = "";
    for(auto &b : _bytes) 
    {
        result = result + char(b);
    }
    return result;
}

string Encoder::GetOutputAsBase64() {
    string result = "";
    for(int i=0; i<_bytes.size()/3; i++) {
        auto& b1 = _bytes[3*i];
        auto& b2 = _bytes[3*i+1];
        auto& b3 = _bytes[3*i+2];

        auto key1 = (b1 & 0b11111100) >> 2;
        auto key2 = ((b1 & 0b00000011) << 4) | ((b2 & 0b11110000) >> 4);
        auto key3 = ((b2 & 0b00001111) << 2) | ((b3 & 0b11000000) >> 6);
        auto key4 = (b3 & 0b00111111);

        result += bytes_to_base64[key1];
        result += bytes_to_base64[key2];
        result += bytes_to_base64[key3];
        result += bytes_to_base64[key4];
    }

    return result;
}

vector<uint8_t> Encoder::GetBytes() {
    return _bytes;
}
