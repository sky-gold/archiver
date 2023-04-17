#pragma once

#include <vector>
#include <string>

#include "writer.h"

class Encoder {
public:
    Encoder(std::string archive_name, std::vector<std::string> files);
    void EncodeFile(std::string file_name, Writer& writer, bool is_last);
    void Encode();

private:
    std::string archive_name_;
    std::vector<std::string> files_;
};
