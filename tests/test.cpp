#include "test.hpp"

#include <stdexcept>
#include <string>
#include <iostream>

void husky::_AssertTrue(
    bool statement, const std::string& message, const char* file, int line
) {
    if (!statement)
        throw std::logic_error(
            message + " " + file + ":" + std::to_string(line));
}

void husky::Log(const std::string &message) {
    std::cout << message << std::endl;
}
