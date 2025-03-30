#include <iostream>
// #include <fstream>
#include "lzw_compressor.h"

int main()
{
    LZWCompressor compressor;
    std::string input = "ABABCAB"; // Example input
    auto compressedOutput = compressor.compress(input);

    // Print the compressed output as a binary string
    std::cout << "Compressed Output: " << compressor.getCompressedBinaryString(compressedOutput) << std::endl;

    return 0;
}
