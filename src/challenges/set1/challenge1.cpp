#include <iostream>
#include <string>

#include "encoder.h"

using namespace std;

const string input = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
const string output = "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t";

void PrintHeader();

int main(int argc, char* argv[]) {
    PrintHeader();
    
    Encoder enc;
    enc.SetInputFromHexString(input);

    auto result = enc.GetOutputAsBase64();    
    cout << "\tactual output:   " << result << endl;
    
    if(output.compare(result) == 0 )
        cout << "SUCCESS!" << endl;
    else 
        cout << "failure..." << endl;

    return 0;
}

void PrintHeader() {
    cout << "--- Set 1 Challenge 1 ---" << endl << endl;
    cout << "Description: Convert Hex to Base64: " << endl;
    cout << "\tinput:  " << input << endl;
    cout << "\texpected output: " << output << endl;
}