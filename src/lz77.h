#include <cstdint>
#include <string>
#include <vector>

struct EncodedData{
    uint8_t position;
    uint8_t length;
    char symbol;
};

class LZ77Encoder{
    char* dictionary;
    int dict_len;
    std::string in_buffer;
    public:
    LZ77Encoder(){}
    LZ77Encoder(int dict_len);
    std::vector<EncodedData> encode(std::string &input);

};

class LZ77Decoder{
    public:
    LZ77Decoder(){}
    LZ77Decoder(int dict_len);
    std::string decode(std::vector<EncodedData> &input);
};
