#include "lzw_compressor.h"
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>

// void LZWCompressor::compress(const std::string &inputFile, const std::string &outputFile) {
//     std::ifstream in(inputFile, std::ios::binary);
//     std::ofstream out(outputFile, std::ios::binary);

//     if (!in || !out) {
//         std::cerr << "Error opening files!" << std::endl;
//         return;
//     }

//     std::unordered_map<std::string, int> dictionary;
//     for (int i = 0; i < 256; ++i)
//         dictionary[std::string(1, i)] = i;

//     std::string current;
//     char ch;
//     int code = 256;

//     while (in.get(ch)) {
//         std::string newStr = current + ch;
//         if (dictionary.count(newStr)) {
//             current = newStr;
//         } else {
//             out.write(reinterpret_cast<const char*>(&dictionary[current]), sizeof(int));
//             dictionary[newStr] = code++;
//             current = std::string(1, ch);
//         }
//     }

//     if (!current.empty())
//         out.write(reinterpret_cast<const char*>(&dictionary[current]), sizeof(int));

//     in.close();
//     out.close();
// }

// void LZWCompressor::decompress(const std::string &inputFile, const std::string &outputFile) {
//     std::ifstream in(inputFile, std::ios::binary);
//     std::ofstream out(outputFile, std::ios::binary);

//     if (!in || !out) {
//         std::cerr << "Error opening files!" << std::endl;
//         return;
//     }

//     std::unordered_map<int, std::string> dictionary;
//     for (int i = 0; i < 256; ++i)
//         dictionary[i] = std::string(1, i);

//     int oldCode, newCode;
//     in.read(reinterpret_cast<char*>(&oldCode), sizeof(int));
//     std::string current = dictionary[oldCode];
//     out << current;

//     int code = 256;

//     while (in.read(reinterpret_cast<char*>(&newCode), sizeof(int))) {
//         std::string newStr;
//         if (dictionary.count(newCode)) {
//             newStr = dictionary[newCode];
//         } else {
//             newStr = current + current[0];
//         }
//         out << newStr;
//         dictionary[code++] = current + newStr[0];
//         current = newStr;
//     }

//     in.close();
//     out.close();
// }

void LZWCompressor::compress()
{
    std::cout << "Compressed\n";
}

void LZWCompressor::decompress()
{
    std::cout << "Decompressed\n";
}