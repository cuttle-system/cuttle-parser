#pragma once

#include <string>

#define AssertTrue(statement, message)                  \
    _AssertTrue(statement, message, __FILE__, __LINE__)

namespace husky {
    void _AssertTrue(
        bool statement, const std::string& message, const char* file, int line
    );
    void Log(const std::string &message);
}
