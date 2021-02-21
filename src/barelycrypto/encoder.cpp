#include <string>
#include <vector>
#include <iostream>

#include "encoder.h"

#include "hex_to_bytes.h"
#include "bytes_to_hex.h"
#include "bytes_to_base64.h"

using namespace std;

void Encoder::SetInputFromString(string input) {
    _bytes.clear();
    for(auto c : input) {
        _bytes.emplace_back(c);
    }
}

void Encoder::SetInputFromBase64String(string input) {
    _bytes.clear();

    for(int i = 0; i < input.size()/4; i++) {
        const auto& c1 = base64_to_bytes[input.at(4*i)];
        const auto& c2 = base64_to_bytes[input.at(4*i+1)];
        const auto& c3 = base64_to_bytes[input.at(4*i+2)];
        const auto& c4 = base64_to_bytes[input.at(4*i+3)];
        
        uint8_t b1 = ((c1 << 2) & 0b11111100 );
        
        // if c2 is padding... add b1 as is, and break
        if(c2 == 0x40) {
            _bytes.emplace_back(b1);
            break;
        }
        b1 |= ((c2 >> 4) & 0b00000011 );
        _bytes.emplace_back(b1);


        uint8_t b2 = ((c2 << 4) & 0b11110000 ); 
        if(c3 == 0x40) {
            _bytes.emplace_back(b2);
            break;
        }
        
        b2 |= ((c3 >> 2) & 0b00001111 );
        _bytes.emplace_back(b2);


        uint8_t b3 = ((c3 << 6) & 0b11000000 );
        if(c4 == 0x40) {
            _bytes.emplace_back(b3);
            break;
        }

         b3 |= ( c4 & 0b00111111 );
         _bytes.emplace_back(b3);

    }
}

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
