#include <iostream>
#include "function_test.hpp"
#include "token_test.hpp"
#include "tokenizer_test.hpp"
#include "test_file_access.hpp"
#include "test_parser.hpp"

void run_tests() {
    run_function_tests();
    run_token_tests();
    run_tokenizer_tests();
    run_file_access_tests();
	run_parser_tests();
}