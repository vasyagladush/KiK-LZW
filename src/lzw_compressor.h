#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <cstdint>
#include <bitset>

class LZWCompressor
{
private:
    static std::unordered_map<std::string, int> initialDictionary; // Shared static dict
    std::unordered_map<std::string, int> dictionary;               // Per-instance dict
    std::uint8_t bitSize;                                          // Fixed bit size for encoding
    int nextCode;                                                  // Tracks the next available code

public:
    LZWCompressor();
    LZWCompressor(std::uint8_t bitSize);
    std::vector<int> compress(const std::string &input);
    static void decompress();
    std::string getCompressedBinaryString(const std::vector<int> &compressedCodes);
};