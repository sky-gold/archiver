#include "writer.h"

#include <assert.h>
#include <iostream>

#include "text_exception.h"
#include "constants.h"

Writer::Writer(std::string file_name) : out_(file_name, std::ios::binary) {
    if (!out_.is_open()) {
        throw TextException("Writer file opening failed");
    }
}
Writer::~Writer() {
    if (buffer_count_ != 0) {
        size_t cnt = BIT_IN_BYTE - buffer_count_;
        for (size_t i = 0; i < cnt; ++i) {
            WriteBit(0);
        }
    }
    out_.close();
}

void Writer::WriteBit(uint8_t x) {
    assert(x <= 1);
    buffer_ <<= 1;
    buffer_ += x;
    ++buffer_count_;
    if (buffer_count_ == BIT_IN_BYTE) {
        out_ << static_cast<char>(buffer_);
        buffer_ = 0;
        buffer_count_ = 0;
    }
}

void Writer::Write(const Symbol &symbol) {
    for (size_t i = BIT_IN_BYTE; i > 0; --i) {
        WriteBit((symbol.GetValue() >> i) & 1);
    }
    WriteBit(symbol.GetValue() & 1);
}

void Writer::Write(const std::vector<bool> &value) {
    for (auto bit : value) {
        WriteBit(bit);
    }
}
