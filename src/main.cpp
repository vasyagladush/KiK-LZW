#include <iostream>
// #include <fstream>
#include "lzw_compressor.h"

int main() {
    // std::string inputFile = "input.txt";
    // std::string compressedFile = "compressed.lzw";
    // std::string decompressedFile = "output.txt";

    // Compress the file
    LZWCompressor::compress();
    // std::cout << "File compressed to: " << compressedFile << std::endl;

    // Decompress the file
    LZWCompressor::decompress();
    // std::cout << "File decompressed to: " << decompressedFile << std::endl;

    return 0;
}
