#include "argparser.h"

#include <cstring>

#include "text_exception.h"

ArgParser::ArgParser(int argc, char **argv) {
    if (argc < 2) {
        throw TextException("argument count < 2");
    }
    if (strcmp(argv[1], "-c") == 0) {
        mode_ = ArgParser::Mode::Encode;
        if (argc < 4) {
            throw TextException("mode -c but argument count < 4");
        }
        archive_name_ = std::string(argv[2]);
        files_.resize(argc - 3);
        for (size_t i = 3; i < static_cast<size_t>(argc); ++i) {
            files_[i - 3] = argv[i];
        }
    } else if (strcmp(argv[1], "-d") == 0) {
        mode_ = ArgParser::Mode::Decode;
        if (argc != 3) {
            throw TextException("mode -d but argument count != 3");
        }
        archive_name_ = std::string(argv[2]);
    } else if (strcmp(argv[1], "-h") == 0) {
        mode_ = ArgParser::Mode::Help;
    } else {
        throw TextException("unknown mode");
    }
}

ArgParser::Mode ArgParser::GetMode() const {
    return mode_;
}

std::string ArgParser::GetArchiveName() const {
    return archive_name_;
}

std::vector<std::string> ArgParser::GetFiles() const {
    return files_;
}
