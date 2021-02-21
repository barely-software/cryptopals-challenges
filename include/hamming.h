#pragma once

#include <vector>
#include <bit>

int hamming(std::vector<uint8_t> bytes1, std::vector<uint8_t> bytes2) {
    auto dist = 0;
    for(int i = 0; i< bytes1.size(); i++) {
        auto& b1 = bytes1[i];
        auto& b2 = bytes2[i];

        const uint8_t d = b1^b2;

        dist += std::__popcount(d);
    }

    return dist;
}
