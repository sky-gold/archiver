#include "huffman_coding.h"

#include <set>
#include <queue>
#include <tuple>

#include "constants.h"
#include "text_exception.h"

using NodeIndex = size_t;

using FrequencyPriorityQueue =
    std::priority_queue<std::tuple<size_t, Symbol, NodeIndex>, std::vector<std::tuple<size_t, Symbol, NodeIndex>>,
                        std::greater<std::tuple<size_t, Symbol, NodeIndex>>>;

HuffmanCoding::HuffmanCoding(std::string file) {
    std::vector<size_t> frequency = HuffmanCoding::FrequencyCount(file);
    FrequencyPriorityQueue symbol_frequency;
    for (size_t i = 0; i < frequency.size(); ++i) {
        if (frequency[i] > 0) {
            symbol_frequency.push(std::make_tuple(frequency[i], Symbol(i), trie_.MakeNode(Symbol(i))));
        }
    }
    symbol_frequency.push(std::make_tuple(1, FILENAME_END, trie_.MakeNode(FILENAME_END)));
    symbol_frequency.push(std::make_tuple(1, ONE_MORE_FILE, trie_.MakeNode(ONE_MORE_FILE)));
    symbol_frequency.push(std::make_tuple(1, ARCHIVE_END, trie_.MakeNode(ARCHIVE_END)));
    while (symbol_frequency.size() > 1) {
        auto first = symbol_frequency.top();
        symbol_frequency.pop();
        auto second = symbol_frequency.top();
        symbol_frequency.pop();
        size_t new_frequency = std::get<0>(first) + std::get<0>(second);
        Symbol new_symbol = std::get<1>(first);
        if (new_symbol > std::get<1>(second)) {
            new_symbol = std::get<1>(second);
        }
        NodeIndex new_node = trie_.Unite(std::get<2>(first), std::get<2>(second));
        symbol_frequency.push(std::make_tuple(new_frequency, new_symbol, new_node));
    }
    trie_.SetHead(std::get<2>(symbol_frequency.top()));
}

std::vector<std::pair<size_t, Symbol>> HuffmanCoding::GetCanonicalHuffmanCode() const {
    std::vector<std::pair<size_t, Symbol>> result;
    trie_.LengthCount(trie_.GetHead(), result);
    std::sort(result.begin(), result.end());
    return result;
}

HuffmanCoding::HuffmanCoding(const std::vector<std::pair<size_t, Symbol>>& canonical_code) {
    LongBitNumber code;
    std::vector<std::pair<Symbol, LongBitNumber>> symbols_code;
    for (size_t i = 0; i < canonical_code.size(); ++i) {
        auto [code_length, symbol] = canonical_code[i];
        code <<= (code_length - code.Size());
        trie_.Add(symbol, code.GetValue());
        symbols_code.push_back(std::make_pair(symbol, code));
        if (i != canonical_code.size() - 1) {
            ++code;
        }
    }
}

std::vector<size_t> HuffmanCoding::FrequencyCount(std::string file_name) {
    std::vector<size_t> result(256, 0);
    for (char symbol : file_name) {
        ++result[static_cast<unsigned char>(symbol)];
    }
    std::ifstream file(file_name, std::ios::binary);
    char symbol = 0;
    file.read(&symbol, 1);
    while (!file.eof()) {
        ++result[static_cast<unsigned char>(symbol)];
        file.read(&symbol, 1);
    }
    return result;
}

std::vector<bool> HuffmanCoding::GetCode(Symbol symbol) {
    return trie_.GetCode(symbol);
}

bool HuffmanCoding::IsReadable() const {
    return (trie_.GetLeft(read_node_) == 0 && trie_.GetLeft(read_node_) == 0);
}

Symbol HuffmanCoding::Read() {
    if (!IsReadable()) {
        throw std::exception();
    }
    Symbol result = trie_.GetSymbol(read_node_);
    read_node_ = trie_.GetHead();
    return result;
}

void HuffmanCoding::MoveBit(bool value) {
    if (value) {
        if (trie_.GetRight(read_node_) == 0) {
            throw TextException("HuffmanCoding::MoveBit no such code in trie");
        }
        read_node_ = trie_.GetRight(read_node_);
    } else {
        if (trie_.GetLeft(read_node_) == 0) {
            throw TextException("HuffmanCoding::MoveBit no such code in trie");
        }
        read_node_ = trie_.GetLeft(read_node_);
    }
}
