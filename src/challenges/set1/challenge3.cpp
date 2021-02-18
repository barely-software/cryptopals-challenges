#include <iostream>
#include <string>

#include "encoder.h"
#include "xor_bytes.h"

#include "character_frequencies.h"

using namespace std;

const string input = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";

void PrintHeader();

int main(int argc, char* argv[]) {
    PrintHeader();
    
    Encoder enc1;
    enc1.SetInputFromHexString(input);
    auto bytes1 = enc1.GetBytes();

    float best = 10000000.0f;
    uint8_t bestChar = 0;

    for(uint8_t i = 0; i<255; i++) {
        enc1.SetInputFromBytes(XorBytes(bytes1, i));
        auto tmp = enc1.GetOutputAsASCII();
        auto tmpFreq = compute_frequencies(tmp);
        if(compare_frequencies(tmpFreq, english_frequencies) < best) {
            best = compare_frequencies(tmpFreq, english_frequencies);
            bestChar = i;
        }
    }


    enc1.SetInputFromBytes(XorBytes(bytes1, bestChar));
    cout << enc1.GetOutputAsASCII() <<endl;

   return 0;
}

void PrintHeader() {
    cout << "--- Set 1 Challenge 2 ---" << endl << endl;
    cout << "Description: Fixed XOR " << endl;
    cout << "\tinput:  " << input << endl;
}
