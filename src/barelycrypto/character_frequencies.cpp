#include <map>
#include <string>
#include <cmath>
#include "character_frequencies.h"

using namespace std;

char asciitolower(char in) {
    if (in <= 'Z' && in >= 'A')
        return in - ('Z' - 'z');
    return in;
}

map<uint8_t,float> compute_frequencies(const string& input) {
    map<uint8_t, float> result;

    for(char c='a'; c<='z'; c++) {
        result[c] = 0;
    }

    int count = 0;
    for (const auto& c : input) {
        auto lc = asciitolower(c);

        if(lc >= 'a' && lc <= 'z') {
            result[lc] += 1;
            count++;
        }
        else {
            result[c] += 1;
            count++;
        }
    }

    for(uint8_t i = 0 ; i < 256; i++) {
        result[i] /= count;
        if(i==255) break;
    }

    return result;
}


float compare_frequencies(map<uint8_t, float> m1, map<uint8_t, float> m2) {
    auto diff = 0.0f;

    for(uint8_t i=0; i<256; i++) {
        diff += fabs(m1[i]-m2[i]);
        if(i==255) break;
    }

    return diff;
}
