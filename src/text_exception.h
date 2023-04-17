#pragma once
#include <exception>

class TextException : public std::exception {
public:
    explicit TextException(const char* exception_text);
    const char* what() const throw() override;

private:
    const char* exception_text_;
};
