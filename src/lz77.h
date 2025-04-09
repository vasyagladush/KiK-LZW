#include <cstdint>
#include <string>
#include <vector>

struct EncodedData{
    uint8_t position;
    uint8_t length;
    char symbol;
}

class LZ77Encoder{
    char* dictionary;
    std::string in_buffer;

    LZ77Encoder(){}
    LZ77Encoder(int dict_len);
    std::vector<EncodedData> encode(std::string input);

};
