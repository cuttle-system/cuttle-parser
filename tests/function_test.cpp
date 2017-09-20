#include <string>
#include <iostream>

#include "test.hpp"
#include "function.hpp"

using namespace cuttle;

inline void test_contstructor() {
    function_t func {INFIX_FUNCTION, 2};

    AssertTrue(func.type == INFIX_FUNCTION, "Type constructor");
    AssertTrue(func.args_number == 2, "Args number constructor");
}

void run_function_tests() {
    TESTCASE
    test_contstructor();
}