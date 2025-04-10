#include <cstring>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "lz77.h"

LZ77Encoder::LZ77Encoder(int dict_size){
    this->dictionary = new char[dict_size];
    this->dict_len = dict_size;
}

std::vector<EncodedData> LZ77Encoder::encode(std::string &input){
    std::vector<EncodedData> compressed;
    size_t pos = 0;

    while (pos < input.length()) {
        size_t best_length = 0;
        size_t best_offset = 0;

        size_t window_start = (pos < this->dict_len) ? 0 : pos - this->dict_len;

        for (size_t search_pos = window_start; search_pos < pos; ++search_pos) {
            size_t match_len = 0;

            while (match_len < this->dict_len &&
                   pos + match_len < input.length() &&
                   input[search_pos + match_len] == input[pos + match_len]) {
                ++match_len;
            }

            if (match_len > best_length) {
                best_length = match_len;
                best_offset = pos - search_pos;
            }
        }

        char next_char = (pos + best_length < input.length()) ? input[pos + best_length] : '\0';

        EncodedData token;
        token.position = static_cast<uint8_t>(best_offset);
        token.length = static_cast<uint8_t>(best_length);
        token.symbol = next_char;

        compressed.push_back(token);

        pos += best_length + 1;
    }
    return compressed;
}

std::string LZ77Decoder::decode(std::vector<EncodedData>& compressed) {
    std::string output;

    for (const auto& token : compressed) {
        if (token.position == 0 || token.length == 0) {
            // No match, just append the next character
            if (token.symbol != '\0') {
                output += token.symbol;
            }
        } else {
            size_t start = output.size() - token.position;
            for (size_t i = 0; i < token.length; ++i) {
                output += output[start + i];
            }
            if (token.symbol != '\0') {
                output += token.symbol;
            }
        }
    }

    return output;
}

double calculate_compression_rate(const std::string& original, const std::vector<EncodedData>& compressed) {
    size_t original_size = original.size();

    // Each DataSet contains 2 bytes (uint8_t, uint8_t) and 1 char = 3 bytes
    size_t compressed_size = compressed.size() * sizeof(EncodedData);

    if (original_size == 0) return 0.0;

    double rate = (1.0 - static_cast<double>(compressed_size) / original_size) * 100.0;
    return rate;
}


int main(){
    std::string text = "asdfsdfasdgasasdasdasdasdasdasffsafsdsadasdasdasdsasddsadsadasfsadsdsadasadsadsaffagsagsagsadsadadsadsadsadsadasdsadsadsadasdsadasdasdsafafssafsa";
    LZ77Encoder encoder(255);
    auto compressed = encoder.encode(text);
    LZ77Decoder decoder;
    std::string decompressed = decoder.decode(compressed);
    for (const auto& token : compressed) {
        std::cout << "Offset: " << (int)token.position
                  << ", Length: " << (int)token.length
                  << ", Next: '" << token.symbol << "'\n";
    }
    std::cout<<"Original:"<<text<<"\tDecompressed:"<<decompressed<<"\nCompression rate:"<<calculate_compression_rate(text, compressed);
}
