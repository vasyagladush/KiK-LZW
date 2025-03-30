#include <iostream>
#include "lzw.h"

#define LZW_COMPRESSION_BIT_SIZE 9

int main()
{
    std::string input = "ABABCABDCAB"; // Example input

    LZW::Compressor compressor(LZW_COMPRESSION_BIT_SIZE);
    auto compressedCodes = compressor.compress(input);
    std::string compressedBinary = compressor.getCompressedBinaryString(compressedCodes);

    std::cout << "Original String: " << input << std::endl;
    std::cout << "Compressed Output (Binary): " << compressedBinary << std::endl;

    LZW::Decompressor decompressor(LZW_COMPRESSION_BIT_SIZE);
    std::string decompressedString = decompressor.decompress(compressedCodes);

    std::cout << "Decompressed String: " << decompressedString << std::endl;

    // Compare original and decompressed strings
    if (input == decompressedString)
    {
        std::cout << "Decompression successful!" << std::endl;
    }
    else
    {
        std::cout << "Decompression failed!" << std::endl;
    }

    // Calculate compression ratio
    size_t originalBits = input.size() * 8;
    size_t compressedBits = compressedCodes.size() * LZW_COMPRESSION_BIT_SIZE;
    double compressionRatio = (1.0 - (double)compressedBits / originalBits) * 100.0;

    std::cout << "Original Size: " << originalBits << " bits" << std::endl;
    std::cout << "Compressed Size: " << compressedBits << " bits" << std::endl;
    std::cout << "Compression Savings: " << compressionRatio << "%" << std::endl;

    return 0;
}