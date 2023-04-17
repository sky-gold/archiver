#include "decoder.h"

#include <fstream>

#include "constants.h"
#include "huffman_coding.h"

Decoder::Decoder(std::string archive_name) : archive_name_(archive_name) {
}

bool Decoder::DecodeFile(Reader& reader) {
    size_t symbols_count = reader.Read().GetValue();
    Symbol symbol;
    std::vector<std::pair<size_t, Symbol>> canonical_code;
    for (size_t i = 0; i < symbols_count; ++i) {
        canonical_code.push_back(std::make_pair(0, reader.Read()));
    }
    size_t cnt = 0;
    size_t length = 1;
    size_t ind = 0;
    while (cnt < symbols_count) {
        size_t length_count = reader.Read().GetValue();
        for (size_t i = 0; i < length_count; ++i) {
            canonical_code[ind++].first = length;
        }
        ++length;
        cnt += length_count;
    }
    HuffmanCoding huffman_tree(canonical_code);
    while (!huffman_tree.IsReadable()) {
        huffman_tree.MoveBit(reader.ReadBit());
    }
    std::string file_name;
    symbol = huffman_tree.Read();
    while (symbol != FILENAME_END) {
        file_name.push_back(symbol.GetChar());
        while (!huffman_tree.IsReadable()) {
            huffman_tree.MoveBit(reader.ReadBit());
        }
        symbol = huffman_tree.Read();
    }
    std::ofstream file(file_name, std::ios::binary);
    if (!file.is_open()) {
        throw "Decoder::DecodeFile file openning failed";
    }
    while (!huffman_tree.IsReadable()) {
        huffman_tree.MoveBit(reader.ReadBit());
    }
    symbol = huffman_tree.Read();
    while (symbol != ONE_MORE_FILE && symbol != ARCHIVE_END) {
        file << symbol.GetChar();
        while (!huffman_tree.IsReadable()) {
            huffman_tree.MoveBit(reader.ReadBit());
        }
        symbol = huffman_tree.Read();
    }
    file.close();
    return (symbol != ARCHIVE_END);
}

void Decoder::Decode() {
    Reader reader(archive_name_);
    while (DecodeFile(reader)) {
    };
}
