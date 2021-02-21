#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

#include "encoder.h"
#include "hamming.h"
#include "xor_bytes.h"
#include "character_frequencies.h"

using namespace std;

void PrintHeader();

int get_key_size(const vector<uint8_t>& bytes) {
    Encoder e;

    auto bestKeyLength = 2;
    auto bestScore = 10000.0f;
    for(int keySize = 6; keySize <=40; keySize++) {
        auto bytes1 = vector<uint8_t>(&bytes[0],&bytes[keySize]);
        auto bytes2 = vector<uint8_t>(&bytes[keySize],&bytes[2*keySize]);
        auto bytes3 = vector<uint8_t>(&bytes[2*keySize],&bytes[3*keySize]);
        auto bytes4 = vector<uint8_t>(&bytes[3*keySize],&bytes[4*keySize]);

       auto d = (1.0f * hamming(bytes1, bytes2) / keySize) +
                (1.0f * hamming(bytes2, bytes3) / keySize) +
                (1.0f * hamming(bytes3, bytes4) / keySize);
       d /= 3.0;

       if(d<bestScore) {
        //    cout << "Found new best key length: " << keySize << " score: " << d << endl;
           bestKeyLength = keySize;
           bestScore = d;
       }
       else {
        //    cout << keySize << " rejected with score: " << d << endl;
       }
    }

    return bestKeyLength;
}

int main(int argc, char *argv[])
{
    Encoder e;
    // e.SetInputFromString("this is a test");
    // auto bytes1 = e.GetBytes();
    // e.SetInputFromString("wokka wokka!!!");
    // auto bytes2 = e.GetBytes();
    // cout << hamming(bytes1, bytes2);

    std::ifstream infile("../data/set1_challenge6_inputs.txt");

    // std::stringstream strStream;
    // strStream << infile.rdbuf(); //read the file
    // std::string input = strStream.str(); //str holds the content of the file
    string input = "";
    string line;
    while (getline(infile, line)) {
        input += line;
    }

    e.SetInputFromBase64String(input);
    auto bytes = e.GetBytes();
    auto key_size = get_key_size(bytes);

    string key = "";

    vector<vector<uint8_t>> byte_groups;
    byte_groups.resize(key_size, vector<uint8_t>());
    for(int i = 0; i < bytes.size(); i++) {
        byte_groups[i%key_size].emplace_back(bytes[i]);
    }

    for(auto & bytes : byte_groups) {

    float best = 10000000000.0f;
    string best_string = "banana";
    uint8_t best_char = '\0';

        for(uint8_t i = 0; i < 256; i++) {
            Encoder e2;
            e2.SetInputFromBytes(XorBytes(bytes,i));

            auto r = e2.GetOutputAsASCII();
            auto f = compute_frequencies(r);
            auto s = compare_frequencies(english_frequencies, f);

            if(s < best && (i >16 && i < 127)) {
                best_string = r;
                best = s;
                best_char = i;
                // cout << "best " << int(key.size()) << "th char candidate: " << i << " with score: " << s << endl; 
            }

            if(i==255)
                break;
        }
        
        key.push_back(best_char);
    }

    e.SetInputFromString(key);
    auto bytes2 = e.GetBytes();

    auto result_bytes = XorBytes(bytes, bytes2);

    e.SetInputFromBytes(result_bytes);
    cout << e.GetOutputAsASCII() << endl;
}

void PrintHeader()
{
    cout << "--- Set 1 Challenge 2 ---" << endl << endl;
    cout << "Description: Fixed XOR " << endl;
}
