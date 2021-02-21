#pragma once

#include <string>
#include <vector>
#include <map>

class Encoder {
public:
    void SetInputFromString(std::string input);
    void SetInputFromHexString(std::string input);
    void SetInputFromBase64String(std::string input);
    void SetInputFromBytes(std::vector<uint8_t> input);
    std::string GetOutputAsHexString();
    std::string GetOutputAsASCII();
    std::string GetOutputAsBase64();
    std::vector<uint8_t> GetBytes();

private: 
    std::vector<uint8_t> _bytes;
};

