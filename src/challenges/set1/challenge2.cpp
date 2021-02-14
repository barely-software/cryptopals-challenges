#include <iostream>
#include <string>

#include "encoder.h"
#include "xor_bytes.h"

using namespace std;

const string input1 = "1c0111001f010100061a024b53535009181c";
const string input2 = "686974207468652062756c6c277320657965";
const string output = "746865206b696420646f6e277420706c6179";

void PrintHeader();
vector<uint8_t> XorBytes(vector<uint8_t> bytes1, vector<uint8_t> bytes2) {
    vector<uint8_t> result;

    for(int i=0; i<bytes1.size(); i++) {
        auto b1 = bytes1.at(i);
        auto b2 = bytes2.at(i);
        result.emplace_back(b1 ^ b2);
    }

    return result;
}

int main(int argc, char* argv[]) {
    PrintHeader();
    
    Encoder enc1;
    enc1.SetInputFromHexString(input1);
    auto bytes1 = enc1.GetBytes();

    Encoder enc2;
    enc2.SetInputFromHexString(input2);
    auto bytes2 = enc2.GetBytes();

    auto resultBytes = XorBytes(bytes1, bytes2);
    Encoder enc3;
    enc3.SetInputFromBytes(resultBytes);
    auto result = enc3.GetOutputAsHexString();

    cout << "\tactual output:   " << result << endl;
    
    if(output.compare(result) == 0 )
        cout << "SUCCESS!" << endl;
    else 
        cout << "failure..." << endl;

    return 0;
}

void PrintHeader() {
    cout << "--- Set 1 Challenge 2 ---" << endl << endl;
    cout << "Description: Fixed XOR " << endl;
    cout << "\tinput1:  " << input1 << endl;
    cout << "\tinput2:  " << input2 << endl;
    cout << "\texpected output: " << output << endl;
}