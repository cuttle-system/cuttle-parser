#include <string>
#include <iostream>

#include "test.hpp"
#include "function.hpp"

using namespace husky;

inline void test_contstructor() {
    function_t func {"func", INFIX_FUNCTION, 2};

    AssertTrue(func.name == "func", "Name constructor");
    AssertTrue(func.type == INFIX_FUNCTION, "Type constructor");
    AssertTrue(func.args_number == 2, "Args number constructor");
}

void run_function_tests() {
    std::cout << __func__ << std::endl;
    test_contstructor();
}