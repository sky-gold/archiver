#pragma once

#include <string>
#include <vector>

class ArgParser {
public:
    enum Mode { Encode, Decode, Help };
    ArgParser(int argc, char** argv);
    Mode GetMode() const;
    std::string GetArchiveName() const;
    std::vector<std::string> GetFiles() const;

private:
    Mode mode_;
    std::string archive_name_;
    std::vector<std::string> files_;
};
