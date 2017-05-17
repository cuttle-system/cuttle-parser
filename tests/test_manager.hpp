#pragma once

#include "function_test.hpp"
#include "token_test.hpp"
#include "tokenizer_test.hpp"

class TestManager
{
public:
    static void RunTests() {
        FunctionTest::Run();
        TokenTest::Run();
        TokenizerTest::Run();
    }
};
