#pragma once

#include <string>

#include "test.hpp"
#include "../src/function.hpp"

using namespace husky;

class FunctionTest : public Test
{
    struct Function_ : public Function {
        template <typename ... T>
        Function_(T ... args) : Function(args...) {}
        int GetType() { return 0; }
    };

public:
    static void Run() {
        TestConstructorAndGetters();
    }

protected:
    static void TestConstructorAndGetters() {
        Function_ func("func", 2);

        AssertTrue(func.GetName() == "func",
                   "Name getter", __FILE__, __LINE__);
        AssertTrue(func.GetNumberOfArgs() == 2,
                   "NumberOfArgs getter", __FILE__, __LINE__);
    }
};
