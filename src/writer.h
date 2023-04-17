#pragma once

#include <fstream>
#include <string>
#include <vector>

#include "symbol.h"

class Writer {
public:
    explicit Writer(std::string file_name);
    ~Writer();
    void WriteBit(uint8_t x);
    void Write(const Symbol& symbol);
    void Write(const std::vector<bool>& value);

private:
    uint8_t buffer_;
    size_t buffer_count_ = 0;
    std::ofstream out_;
};
