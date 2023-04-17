#include <iostream>

#include "argparser.h"
#include "encoder.h"
#include "decoder.h"
#include "constants.h"
#include "text_exception.h"

int main(int argc, char** argv) {
    try {
        ArgParser parser(argc, argv);
        if (parser.GetMode() == ArgParser::Mode::Encode) {
            Encoder encoder(parser.GetArchiveName(), parser.GetFiles());
            encoder.Encode();
        } else if (parser.GetMode() == ArgParser::Mode::Decode) {
            Decoder decoder(parser.GetArchiveName());
            decoder.Decode();
        } else if (parser.GetMode() == ArgParser::Mode::Help) {
            std::cout << HELP_TEXT << std::endl;
        }
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
        return ERROR_CODE;
    }
    return 0;
}
