#pragma once

#include <cstdint>
#include <fstream>

#include "symbol.h"
#include "constants.h"

class Reader {
public:
    explicit Reader(std::string file_name);
    ~Reader();
    uint8_t ReadBit();
    Symbol Read();

private:
    uint8_t buffer_;
    size_t buffer_count_ = BIT_IN_BYTE;
    std::ifstream in_;
};
