#include <iostream>
#include "lzw.h"
#include "lz77.h"

#define LZW_COMPRESSION_BIT_SIZE 12

double calculate_compression_rate(const std::string &original, const std::vector<EncodedData> &compressed)
{
    size_t original_size = original.size();

    // Each DataSet contains 2 bytes (uint8_t, uint8_t) and 1 char = 3 bytes
    size_t compressed_size = compressed.size() * sizeof(EncodedData);

    if (original_size == 0)
        return 0.0;

    double rate = (1.0 - static_cast<double>(compressed_size) / original_size) * 100.0;
    return rate;
}

int main()
{
    std::string input = "ABABCABDCABABABCABDCABABABCABDCABABABCABDCABABABCABDCABABABCABDCABABABCABDCABABABCABDCABABABCABDCABABABCABDCAB"; // Example input

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

    std::cout << "\n---------------------------------------------------\n\n";

    LZ77Encoder encoder(255);
    auto compressed = encoder.encode(input);
    LZ77Decoder decoder;
    std::string decompressed = decoder.decode(compressed);

    std::cout << "LZW77:\n";
    if (input == decompressed)
    {
        std::cout << "Decompression successful!" << std::endl;
    }
    else
    {
        std::cout << "Decompression failed!" << std::endl;
    }
    std::cout << "Original:" << input << "\nDecompressed:" << decompressed << "\nCompression rate:" << calculate_compression_rate(input, compressed) << "%";

    return 0;
}