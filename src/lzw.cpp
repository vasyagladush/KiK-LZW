#include "lzw.h"
#include <iostream>
#include <unordered_map>
#include <vector>
#include <bitset>

namespace LZW
{
    std::unordered_map<std::string, unsigned int> Compressor::initialDictionary_;

    Compressor::Compressor(std::uint8_t bitSize) : bitSize_(bitSize), nextCode_(256)
    {
        // Initialize the static initialDictionary_ if it hasn't been initialized
        if (initialDictionary_.empty())
        {
            // Initialize the dictionary_ with ASCII characters (codes 0-255)
            for (unsigned int i = 0; i < 256; ++i)
            {
                initialDictionary_[std::string(1, char(i))] = i;
            }
        }

        // Copy the static initialDictionary_ data into the instance dictionary_
        dictionary_ = initialDictionary_;
    }

    // Method to get the string representation of bits of compressed codes
    std::string Compressor::getCompressedBinaryString(const std::vector<unsigned int> &compressedCodes)
    {
        std::string compressedBinary;

        for (unsigned int code : compressedCodes)
        {
            // Convert the code to a binary string with the fixed bit size
            std::string binCode = std::bitset<32>(code).to_string(); // Get 32-bit binary representation
            binCode = binCode.substr(32 - bitSize_);                 // Use only the required number of bits

            compressedBinary += binCode;
            compressedBinary += ' ';
        }

        return compressedBinary;
    }

    std::vector<unsigned int> Compressor::compress(const std::string &input)
    {
        std::string currentStr = "";
        std::vector<unsigned int> compressedCodes; // Stores the final compressed output

        for (char ch : input)
        {
            currentStr += ch;

            // If currentStr is in the dictionary_, continue building the sequence
            if (dictionary_.find(currentStr) != dictionary_.end())
            {
                continue;
            }

            // Otherwise, output the code for the longest matching string
            compressedCodes.push_back(dictionary_[currentStr.substr(0, currentStr.length() - 1)]);

            // Add currentStr to the dictionary_ if within limit
            if (nextCode_ < (1 << bitSize_))
            {
                dictionary_[currentStr] = nextCode_++;
            }

            // Start a new sequence with the current character
            currentStr = std::string(1, ch);
        }

        // Output the last sequence
        if (!currentStr.empty())
        {
            compressedCodes.push_back(dictionary_[currentStr]);
        }

        return compressedCodes;
    }

    std::unordered_map<unsigned int, std::string> Decompressor::initialReverseDictionary_;

    Decompressor::Decompressor(std::uint8_t bitSize) : bitSize_(bitSize), nextCode_(256)
    {
        // Initialize the static initialReverseDictionary_ if it hasn't been initialized
        if (initialReverseDictionary_.empty())
        {
            // Initialize the reverse dictionary_ with ASCII characters (codes 0-255)
            for (unsigned int i = 0; i < 256; ++i)
            {
                initialReverseDictionary_[i] = std::string(1, char(i));
            }
        }

        // Copy the static initialReverseDictionary_ data into the instance reverseDictionary_
        reverseDictionary_ = initialReverseDictionary_;
    }

    std::string Decompressor::decompress(const std::vector<unsigned int> &compressedCodes)
    {
        unsigned int currentCode = compressedCodes[0];
        std::string decompressed = reverseDictionary_[currentCode];
        std::string previousStr = decompressed;

        // Iterate through the compressed codes to decompress
        for (size_t i = 1; i < compressedCodes.size(); ++i)
        {
            currentCode = compressedCodes[i];
            std::string entry;

            if (reverseDictionary_.find(currentCode) != reverseDictionary_.end())
            {
                entry = reverseDictionary_[currentCode];
            }
            else
            {
                entry = previousStr + previousStr[0];
            }

            decompressed += entry;

            // Add new entry to the reverse dictionary_ if within limit
            if (nextCode_ < (1 << bitSize_))
            {
                reverseDictionary_[nextCode_++] = previousStr + entry[0];
            }

            previousStr = entry;
        }

        return decompressed;
    }
}
