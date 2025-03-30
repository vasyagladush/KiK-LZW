#include "lzw_compressor.h"
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>

std::unordered_map<std::string, int> LZWCompressor::initialDictionary;

LZWCompressor::LZWCompressor() : LZWCompressor(9) {}

LZWCompressor::LZWCompressor(std::uint8_t bitSize) : bitSize(bitSize), nextCode(256)
{
    // Initialize the dictionary with ASCII characters (codes 0-255)
    for (int i = 0; i < 256; ++i)
    {
        dictionary[std::string(1, char(i))] = i;
    }
}

std::string LZWCompressor::getCompressedBinaryString(const std::vector<int> &compressedCodes)
{
    std::string compressedBinary;

    for (int code : compressedCodes)
    {
        // Convert the code to a binary string with the fixed bit size
        std::string binCode = std::bitset<32>(code).to_string(); // Get 32-bit binary representation
        binCode = binCode.substr(32 - bitSize);                  // Use only the required number of bits

        compressedBinary += binCode;
        compressedBinary += ' ';
    }

    return compressedBinary;
}

std::vector<int> LZWCompressor::compress(const std::string &input)
{
    std::string currentStr = "";
    std::vector<int> compressedCodes; // This will store the final compressed output

    // Process the input string
    for (char ch : input)
    {
        currentStr += ch;

        // If currentStr is in the dictionary, continue building the sequence
        if (dictionary.find(currentStr) != dictionary.end())
        {
            continue;
        }

        // Otherwise, output the code for the longest matching string
        compressedCodes.push_back(dictionary[currentStr.substr(0, currentStr.length() - 1)]);

        // Add currentStr to the dictionary if within limit
        if (nextCode < (1 << bitSize))
        {
            dictionary[currentStr] = nextCode++;
        }

        // Start a new sequence with the current character
        currentStr = std::string(1, ch);
    }

    // Output the last sequence
    if (!currentStr.empty())
    {
        compressedCodes.push_back(dictionary[currentStr]);
    }

    return compressedCodes;
}

std::string LZWCompressor::decompress(const std::vector<int> &compressedCodes)
{
    std::unordered_map<int, std::string> reverseDictionary;
    for (int i = 0; i < 256; ++i)
    {
        reverseDictionary[i] = std::string(1, char(i));
    }

    int currentCode = compressedCodes[0];
    std::string decompressed = reverseDictionary[currentCode];
    std::string previousStr = decompressed;
    int nextCode = 256;

    for (size_t i = 1; i < compressedCodes.size(); ++i)
    {
        currentCode = compressedCodes[i];
        std::string entry;

        if (reverseDictionary.find(currentCode) != reverseDictionary.end())
        {
            entry = reverseDictionary[currentCode];
        }
        else
        {
            entry = previousStr + previousStr[0];
        }

        decompressed += entry;

        if (nextCode < (1 << bitSize))
        {
            reverseDictionary[nextCode++] = previousStr + entry[0];
        }

        previousStr = entry;
    }

    return decompressed;
}