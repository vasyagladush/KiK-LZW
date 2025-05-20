#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <cstdint>
#include <bitset>

namespace LZW
{
    class Compressor
    {
    public:
        Compressor(std::uint8_t bitSize);
        std::vector<int> compress(const std::string &input);
        const int bitSize() const { return bitSize_; }
        std::string getCompressedBinaryString(const std::vector<int> &compressedCodes);

    private:
        const std::uint8_t bitSize_;
        unsigned int nextCode_;
        static std::unordered_map<std::string, int> initialDictionary_;
        std::unordered_map<std::string, int> dictionary_;
    };

    class Decompressor
    {
    public:
        Decompressor(std::uint8_t bitSize);
        std::string decompress(const std::vector<int> &compressedCodes);
        const int bitSize() const { return bitSize_; }

    private:
        const std::uint8_t bitSize_;
        int nextCode_;
        static std::unordered_map<int, std::string> initialReverseDictionary_;
        std::unordered_map<int, std::string> reverseDictionary_;
    };
}