#pragma once

#include <cstdint>
#include <compare>

class Symbol {
public:
    Symbol();
    explicit Symbol(uint16_t value);
    char GetChar() const;
    uint16_t GetValue() const;
    bool operator==(const Symbol& other) const;
    std::strong_ordering operator<=>(const Symbol& other) const;

private:
    uint16_t value_;
};
