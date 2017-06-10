#pragma once

#include "token.hpp"

namespace husky {
    class NumberToken : public Token {
    public:
        template <typename ... T>
        NumberToken(T ... args) : Token(args...) {}
        virtual int GetType() { return NumberTokenType; }
    };
}
