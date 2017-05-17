#pragma once

#include "token.hpp"

namespace husky {
    class AtomToken : public Token {
    public:
        template <typename ... T>
        AtomToken(T ... args) : Token(args...) {}
        virtual int GetType() { return AtomTokenType; }
    };
}
