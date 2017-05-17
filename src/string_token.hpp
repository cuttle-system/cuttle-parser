#pragma once

#include "token.hpp"

namespace husky {
    class StringToken : public Token {
    public:
        template <typename ... T>
        StringToken(T ... args) : Token(args...) {}
        virtual int GetType() { return StringTokenType; }
    };
}
