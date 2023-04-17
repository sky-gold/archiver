#include "reader.h"

#include "text_exception.h"

Reader::Reader(std::string file_name) : in_(file_name, std::ios::binary) {
    if (!in_.is_open()) {
        throw TextException("Reader file opening failed");
    }
}

Reader::~Reader() {
    in_.close();
}

uint8_t Reader::ReadBit() {
    if (buffer_count_ == BIT_IN_BYTE) {
        buffer_count_ = 0;
        char char_buffer = 0;
        in_.read(&char_buffer, 1);
        if (in_.eof()) {
            throw TextException("Reader::ReadBit file is over");
        }
        buffer_ = char_buffer;
    }
    uint8_t result = ((buffer_ >> (BIT_IN_BYTE - (buffer_count_++) - 1)) & 1);
    return result;
}

Symbol Reader::Read() {
    uint16_t value = 0;
    for (size_t i = 0; i < SYMBOL_LENGTH; ++i) {
        value = (value << 1) + ReadBit();
    }
    return Symbol(value);
}
