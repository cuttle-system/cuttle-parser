#pragma once

#include <string>

#include "test.hpp"
#include "../src/token.hpp"

using namespace husky;

class TokenTest : public Test
{
    struct Token_ : public Token {
        template <typename ... T>
        Token_(T ... args) : Token(args...) {}
        int GetType() { return 0; }
    };

public:
    static void Run() {
        TestConstructorAndGetters();
    }

protected:
    static void TestConstructorAndGetters() {
        Token_ tok("1", 2, 10);

        AssertTrue(tok.GetValue() == "1",
                   "Value getter", __FILE__, __LINE__);
        AssertTrue(tok.GetLine() == 2,
                   "Line getter", __FILE__, __LINE__);
        AssertTrue(tok.GetCol() == 10,
                   "Col getter", __FILE__, __LINE__);
    }
};
