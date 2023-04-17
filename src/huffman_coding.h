#pragma once

#include <vector>
#include <string>
#include <fstream>

#include "symbol.h"
#include "trie.h"
#include "text_exception.h"

class HuffmanCoding {
public:
    explicit HuffmanCoding(std::string file);
    explicit HuffmanCoding(const std::vector<std::pair<size_t, Symbol>>& canonical_code);
    std::vector<std::pair<size_t, Symbol>> GetCanonicalHuffmanCode() const;
    static std::vector<size_t> FrequencyCount(std::string file_name);
    std::vector<bool> GetCode(Symbol symbol);
    void MoveBit(bool value);
    bool IsReadable() const;
    Symbol Read();

private:
    Trie trie_ = Trie();
    size_t read_node_ = trie_.GetHead();

    class LongBitNumber {
    public:
        LongBitNumber() : value_(1, false){};
        explicit LongBitNumber(std::vector<bool> value) : value_(value) {
            if (value.empty()) {
                throw TextException("LongBitNumber with empty value");
            }
        };
        LongBitNumber& operator++() {
            bool all_is_true = true;
            for (auto element : value_) {
                all_is_true = (all_is_true && element);
            }
            if (all_is_true) {
                throw TextException("LongBit increment with max value");
            }
            size_t i = value_.size() - 1;
            while (value_[i]) {
                value_[i] = false;
                --i;
            }
            value_[i] = true;
            return *this;
        }
        std::vector<bool> GetValue() const {
            return value_;
        }
        void operator<<=(size_t count) {
            while (count--) {
                value_.push_back(false);
            }
        }
        size_t Size() const {
            return value_.size();
        }

    private:
        std::vector<bool> value_;
    };
};
