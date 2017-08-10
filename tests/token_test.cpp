#include <iostream>
#include "test.hpp"
#include "token.hpp"

using namespace husky;

inline void test_constructor() {
    token_t tok {NUMBER_TOKEN, "1", 2, 10};

    AssertTrue(tok.type == NUMBER_TOKEN, "Type constructor");
    AssertTrue(tok.value == "1", "Value constructor");
    AssertTrue(tok.line == 2, "Line constructor");
    AssertTrue(tok.col == 10, "Col constructor");
}

inline void test_right_after() {
    token_t tok1 {NUMBER_TOKEN, "1", 1, 10};
    token_t tok2 {NUMBER_TOKEN, "2", 1, 11};
    token_t tok3 {NUMBER_TOKEN, "3", 2, 1};
    token_t tok4 {NUMBER_TOKEN, "4", 2, 3};
    token_t tok5 {NUMBER_TOKEN, "5", 2, 10};
    token_t tok6 {NUMBER_TOKEN, "6", 3, 11};

    AssertTrue(tok1 >= tok2, "Token 1 RightAfter Token 2");
    AssertTrue(!(tok2 >= tok1), "Token 2 RightAfter Token 1");
    AssertTrue(!(tok2 >= tok2), "Token 2 RightAfter Token 2");

    AssertTrue(!(tok3 >= tok4), "Token 3 RightAfter Token 4");
    AssertTrue(!(tok4 >= tok3), "Token 4 RightAfter Token 3");
    AssertTrue(!(tok4 >= tok4), "Token 4 RightAfter Token 4");

    AssertTrue(!(tok5 >= tok6), "Token 5 RightAfter Token 6");
    AssertTrue(!(tok6 >= tok5), "Token 6 RightAfter Token 5");
    AssertTrue(!(tok6 >= tok6), "Token 6 RightAfter Token 6");

    AssertTrue(!(tok1 >= tok5), "Token 1 RightAfter Token 5");
    AssertTrue(!(tok5 >= tok1), "Token 5 RightAfter Token 1");
    AssertTrue(!(tok5 >= tok5), "Token 5 RightAfter Token 5");
}

void run_token_tests() {
    std::cout << __func__ << std::endl;
    test_constructor();
    test_right_after();
}