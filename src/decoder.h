#pragma once

#include <vector>
#include <string>

#include "reader.h"

class Decoder {
public:
    explicit Decoder(std::string archive_name);
    bool DecodeFile(Reader& reader);
    void Decode();

private:
    std::string archive_name_;
};
