#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "encoder.h"
#include "xor_bytes.h"
#include "character_frequencies.h"

using namespace std;

void PrintHeader();

const string input = 
    "Burning 'em, if you ain't quick and nimble"
    "I go crazy when I hear a cymbal";
const string key = "ICE";

int main(int argc, char *argv[])
{
    PrintHeader();
    Encoder e;
    e.SetInputFromString(input);
    auto inBytes = e.GetBytes();

    e.SetInputFromString(key);
    auto keyBytes = e.GetBytes();

    for(auto c: keyBytes) 
      cout << "." << c;

    cout << endl;
    
    auto raw_result = XorBytes(inBytes, keyBytes);
    e.SetInputFromBytes(raw_result);
    auto result = e.GetOutputAsHexString();
    
    cout << result << endl;

    return 0;
}

void PrintHeader()
{
    cout << "--- Set 1 Challenge 2 ---" << endl << endl;
    cout << "Description: Fixed XOR " << endl;
}
