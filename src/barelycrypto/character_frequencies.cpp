#include <map>
#include <string>
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
            result[asciitolower(c)] += 1;
            count++;
        }
    }


    for(char c='a'; c<='z'; c++) {
        result[c] /= count;
    }


    return result;
}


float compare_frequencies(map<uint8_t, float> m1, map<uint8_t, float> m2) {
    auto diff = 0.0f;
    for(char c ='a'; c<='z'; c++) {
        diff += fabs(m1[c]-m2[c]);
    }

    return diff;
}
