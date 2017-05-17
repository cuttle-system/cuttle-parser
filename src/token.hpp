#pragma once

#include <string>

enum {
    NumberTokenType,
    StringTokenType,
    AtomTokenType
};

namespace husky {
    class Token {
    public:
        Token(const std::string& value, unsigned line, unsigned col)
            : value(value), line(line), col(col) {}

        virtual int GetType() = 0;

        virtual const std::string& GetValue() { return value; }
        virtual int GetLine() { return line; }
        virtual int GetCol() { return col; }
    protected:
        const std::string value;
        const unsigned line;
        const unsigned col;
    };
}
