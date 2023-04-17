#include "encoder.h"

#include <fstream>
#include <assert.h>

#include "constants.h"
#include "huffman_coding.h"
#include "text_exception.h"

Encoder::Encoder(std::string archive_name, std::vector<std::string> files)
    : archive_name_(archive_name), files_(files) {
}

void Encoder::EncodeFile(std::string file_name, Writer& writer, bool is_last) {
    HuffmanCoding huffman_tree(file_name);
    std::vector<std::pair<size_t, Symbol>> canonical_code = huffman_tree.GetCanonicalHuffmanCode();
    writer.Write(Symbol(canonical_code.size()));
    for (auto [_, symbol] : canonical_code) {
        writer.Write(symbol);
    }
    size_t ind = 0;
    for (size_t length = 1; ind < canonical_code.size(); ++length) {
        size_t length_count = 0;
        while (ind < canonical_code.size() && canonical_code[ind].first == length) {
            ++ind;
            ++length_count;
        }
        writer.Write(Symbol(length_count));
    }
    huffman_tree = HuffmanCoding(canonical_code);
    for (char symbol : file_name) {
        writer.Write(huffman_tree.GetCode(Symbol(static_cast<unsigned char>(symbol))));
    }
    writer.Write(huffman_tree.GetCode(FILENAME_END));
    std::ifstream file(file_name, std::ios::binary);
    if (!file.is_open()) {
        throw TextException("Encoder::EncodeFile file openning failed");
    }
    char symbol = 0;
    file.read(&symbol, 1);
    while (!file.eof()) {
        Symbol symbol_9bit = Symbol(static_cast<unsigned char>(symbol));
        writer.Write(huffman_tree.GetCode(symbol_9bit));
        file.read(&symbol, 1);
    }
    if (is_last) {
        writer.Write(huffman_tree.GetCode(ARCHIVE_END));
    } else {
        writer.Write(huffman_tree.GetCode(ONE_MORE_FILE));
    }
}

void Encoder::Encode() {
    Writer writer(archive_name_);
    assert(!files_.empty());
    for (size_t i = 0; i < files_.size(); ++i) {
        EncodeFile(files_[i], writer, (i + 1 == files_.size()));
    }
}
