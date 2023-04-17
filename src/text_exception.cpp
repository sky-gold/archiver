#include "text_exception.h"

TextException::TextException(const char* exception_text) : exception_text_(exception_text) {
}

const char* TextException::what() const throw() {
    return exception_text_;
}
