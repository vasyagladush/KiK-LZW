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
        std::vector<unsigned int> compress(const std::string &input);
        const unsigned int bitSize() const { return bitSize_; }
        std::string getCompressedBinaryString(const std::vector<unsigned int> &compressedCodes);

    private:
        const std::uint8_t bitSize_;
        unsigned int nextCode_;
        static std::unordered_map<std::string, unsigned int> initialDictionary_;
        std::unordered_map<std::string, unsigned int> dictionary_;
    };

    class Decompressor
    {
    public:
        Decompressor(std::uint8_t bitSize);
        std::string decompress(const std::vector<unsigned int> &compressedCodes);
        const unsigned int bitSize() const { return bitSize_; }

    private:
        const std::uint8_t bitSize_;
        unsigned int nextCode_;
        static std::unordered_map<unsigned int, std::string> initialReverseDictionary_;
        std::unordered_map<unsigned int, std::string> reverseDictionary_;
    };
}