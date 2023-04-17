#include <climits>

#include "symbol.h"
#include "text_exception.h"

Symbol::Symbol() {
}

std::strong_ordering Symbol::operator<=>(const Symbol &other) const {
    return value_ <=> other.value_;
}

Symbol::Symbol(uint16_t value) : value_(value) {
}

char Symbol::GetChar() const {
    if (value_ > UCHAR_MAX) {
        throw TextException("symbol value more than UCHAR_MAX");
    }
    return static_cast<char>(value_);
}
uint16_t Symbol::GetValue() const {
    return value_;
}

bool Symbol::operator==(const Symbol &other) const {
    return (value_ == other.value_);
}
