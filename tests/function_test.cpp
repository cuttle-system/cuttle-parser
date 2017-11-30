#include <string>
#include <iostream>

#include "test.hpp"
#include "function.hpp"

using namespace cuttle;

inline void test_contstructor() {
    function_t func {function_type::infix, 2};

    AssertTrue(func.type == function_type::infix, "Type constructor");
    AssertTrue(func.args_number == 2, "Args number constructor");
}

void run_function_tests() {
    TESTCASE
    test_contstructor();
}