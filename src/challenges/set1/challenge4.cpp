#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "encoder.h"
#include "xor_bytes.h"
#include "character_frequencies.h"

using namespace std;

void PrintHeader();

int main(int argc, char *argv[])
{
    PrintHeader();
    std::ifstream infile("../data/set1_challenge4_inputs.txt");

    float best_of_best = 10000000000.0f;
    string best_of_best_string = "banana";

    string line;
    while (getline(infile, line))
    {
        cout << "processing: " << line << endl;
        auto best = best_of_best;
        string best_string = "pineapples";
        Encoder e;
        e.SetInputFromHexString(line);
        auto bytes = e.GetBytes();

        for(uint8_t i = 0; i < 256; i++) {
            Encoder e2;
            e2.SetInputFromBytes(XorBytes(bytes,i));

            auto r = e2.GetOutputAsASCII();
            auto f = compute_frequencies(r);
            auto s = compare_frequencies(english_frequencies, f);

            if(s<best) {
                best_string = r;
                best = s;
            }

            if(i==255)
                break;
        }
        
        if(best < best_of_best) {
            best_of_best = best;
            best_of_best_string = best_string;
        }
    }
    cout << "best of the best match: " << best_of_best_string << endl;

    return 0;
}

void PrintHeader()
{
    cout << "--- Set 1 Challenge 2 ---" << endl
         << endl;
    cout << "Description: Fixed XOR " << endl;
}
