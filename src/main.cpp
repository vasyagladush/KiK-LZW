#include <iostream>
#include "corruptor.h"
#include "lzw.h"
#include "lz77.h"

#define LZW_COMPRESSION_BIT_SIZE 12

// Helper: Calculate compression rate for LZW
double calculate_lzw_compression_rate(const std::string &original, const std::vector<unsigned int> &compressedCodes, unsigned int bitSize)
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

// Helper: Calculate error rate (after using 'corruptor')
double calculate_error_rate(const std::string &original, const std::string &corrupted)
{
    size_t minLength = std::min(original.size(), corrupted.size());
    size_t diffCount = 0;

    for (size_t i = 0; i < minLength; ++i)
    {
        if (original[i] != corrupted[i])
            ++diffCount;
    }

    // Count extra chars as wrong if length differs
    diffCount += std::max(original.size(), corrupted.size()) - minLength;

    return static_cast<double>(diffCount) / original.size() * 100.0;
}

std::vector<unsigned int> encode_lz77_to_uints(const std::vector<EncodedData> &data)
{
    std::vector<unsigned int> result;
    result.reserve(data.size());

    for (const auto &token : data)
    {
        // Combine 2 uint8_t and 1 char into a 24-bit unsigned int
        unsigned int encoded = 0;
        encoded |= (static_cast<unsigned int>(token.position) & 0xFF) << 16;
        encoded |= (static_cast<unsigned int>(token.length) & 0xFF) << 8;
        encoded |= (static_cast<unsigned int>(token.symbol) & 0xFF);
        result.push_back(encoded);
    }
    return result;
}

std::vector<EncodedData> decode_uints_to_lz77(const std::vector<unsigned int> &data)
{
    std::vector<EncodedData> result;
    result.reserve(data.size());

    for (auto encoded : data)
    {
        EncodedData token;
        token.position = static_cast<uint8_t>((encoded >> 16) & 0xFF);
        token.length = static_cast<uint8_t>((encoded >> 8) & 0xFF);
        token.symbol = static_cast<char>(encoded & 0xFF);
        result.push_back(token);
    }
    return result;
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

    std::cout << "\n---------------------------------------------------\n";

    std::cout << "\n=== LZW Corruption Test (bit inversion) ===\n";

    corruptor::Range bitRange{0, 11};
    corruptor::Range inversionCountRange{1, 5};

    auto corruptedLZW = corruptor::inverter(LZW_COMPRESSION_BIT_SIZE, lzwCompressedCodes, bitRange, inversionCountRange);
    std::string lzwCorruptedDecompressed;

    try
    {
        lzwCorruptedDecompressed = lzwDecompressor.decompress(corruptedLZW);
        double errorRate = calculate_error_rate(input, lzwCorruptedDecompressed);
        std::cout << "Decompression completed.\n";
        std::cout << "Error rate: " << errorRate << "%\n";
    }
    catch (...)
    {
        std::cout << "Decompression failed due to corruption.\n";
    }

    std::cout << "\n---------------------------------------------------\n";

    std::cout << "\n=== LZ77 Corruption Test (swapper) ===\n";

    corruptor::Range swapRange{0, static_cast<int>(lz77Compressed.size() - 1)};
    auto lz77AsInts = encode_lz77_to_uints(lz77Compressed);
    auto corruptedInts = corruptor::swapper(lz77AsInts, swapRange);
    auto corruptedLZ77 = decode_uints_to_lz77(corruptedInts);

    std::string corruptedDecompressed;
    try
    {
        corruptedDecompressed = lz77Decoder.decode(corruptedLZ77);
        double errorRate = calculate_error_rate(input, corruptedDecompressed);
        std::cout << "Decompression completed.\n";
        std::cout << "Error rate: " << errorRate << "%\n";
    }
    catch (...)
    {
        std::cout << "Decompression failed due to corruption.\n";
    }

    return 0;
}
