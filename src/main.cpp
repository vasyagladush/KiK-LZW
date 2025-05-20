#include <iostream>
#include "lzw.h"
#include "lz77.h"

#define LZW_COMPRESSION_BIT_SIZE 12

// Helper: Calculate compression rate for LZW
double calculate_lzw_compression_rate(const std::string &original, const std::vector<int> &compressedCodes, int bitSize)
{
    if (original.empty())
        return 0.0;

    size_t originalBits = original.size() * 8;
    size_t compressedBits = compressedCodes.size() * bitSize;

    return (1.0 - static_cast<double>(compressedBits) / originalBits) * 100.0;
}

// Helper: Calculate compression rate for LZ77
double calculate_lz77_compression_rate(const std::string &original, const std::vector<EncodedData> &compressed)
{
    if (original.empty())
        return 0.0;

    size_t originalSize = original.size();
    size_t compressedSize = compressed.size() * sizeof(EncodedData);
    return (1.0 - static_cast<double>(compressedSize) / originalSize) * 100.0;
}

// Helper: Print result of decompression check
void verify_decompression(const std::string &original, const std::string &decompressed)
{
    if (original == decompressed)
        std::cout << "Decompression successful!" << std::endl;
    else
        std::cout << "Decompression failed!" << std::endl;
}

int main()
{
    std::string input = "ABABCABDCABABABCABDCABABABCABDCABABABCABDCABABABCABDCABABABCABDCABABABCABDCABABABCABDCABABABCABDCABABABCABDCAB";

    std::cout << "\n=== LZW Compression ===\n";

    // LZW Compression
    LZW::Compressor lzwCompressor(LZW_COMPRESSION_BIT_SIZE);
    auto lzwCompressedCodes = lzwCompressor.compress(input);
    std::string lzwCompressedBinary = lzwCompressor.getCompressedBinaryString(lzwCompressedCodes);

    std::cout << "Original String:\n"
              << input << "\n";
    std::cout << "Compressed Output (Binary):\n"
              << lzwCompressedBinary << "\n";

    // LZW Decompression
    LZW::Decompressor lzwDecompressor(LZW_COMPRESSION_BIT_SIZE);
    std::string lzwDecompressed = lzwDecompressor.decompress(lzwCompressedCodes);

    verify_decompression(input, lzwDecompressed);

    double lzwCompressionRate = calculate_lzw_compression_rate(input, lzwCompressedCodes, LZW_COMPRESSION_BIT_SIZE);

    std::cout << "Compression Savings: " << lzwCompressionRate << "%\n";

    std::cout << "\n---------------------------------------------------\n";

    std::cout << "\n=== LZ77 Compression ===\n";

    // LZ77 Compression
    LZ77Encoder lz77Encoder(255);
    auto lz77Compressed = lz77Encoder.encode(input);

    // LZ77 Decompression
    LZ77Decoder lz77Decoder;
    std::string lz77Decompressed = lz77Decoder.decode(lz77Compressed);

    verify_decompression(input, lz77Decompressed);

    double lz77CompressionRate = calculate_lz77_compression_rate(input, lz77Compressed);

    std::cout << "Original String:\n"
              << input << "\n";
    // std::cout << "Decompressed String:\n"
    //           << lz77Decompressed << "\n";
    std::cout << "Compression Savings: " << lz77CompressionRate << "%\n";

    return 0;
}
