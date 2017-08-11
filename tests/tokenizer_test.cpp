#include <string>
#include <vector>
#include <iostream>

#include "test.hpp"
#include "tokenizer.hpp"
#include "token.hpp"
#include "utils.hpp"

using namespace husky;

inline void test_tokenize_basic_space_separated_atoms() {
    std::vector<token_t *> tokens;

    tokenize("foo bar baz", tokens);

    AssertTrue(tokens[0]->type == ATOM_TOKEN, "element 1 type");
    AssertTrue(tokens[0]->value == "foo", "element 1 value");
    AssertTrue(tokens[0]->line == 1, "element 1 line");
    AssertTrue(tokens[0]->col == 1, "element 1 col");

    AssertTrue(tokens[1]->type == ATOM_TOKEN, "element 2 type");
    AssertTrue(tokens[1]->value == "bar", "element 2 value");
    AssertTrue(tokens[1]->line == 1, "element 2 line");
    AssertTrue(tokens[1]->col == 5, "element 2 col");

    AssertTrue(tokens[2]->type == ATOM_TOKEN, "element 3 type");
    AssertTrue(tokens[2]->value == "baz", "element 3 value");
    AssertTrue(tokens[2]->line == 1, "element 3 line");
    AssertTrue(tokens[2]->col == 9, "element 3 col");

    clear(tokens);
}

inline void test_tokenize_space_and_new_line_separated_atoms() {
    std::vector<token_t *> tokens;

    tokenize("foo bar\n\n baz\nquxx", tokens);

    AssertTrue(tokens[0]->type == ATOM_TOKEN, "element 1 type");
    AssertTrue(tokens[0]->value == "foo", "element 1 value");
    AssertTrue(tokens[0]->line == 1, "element 1 line");
    AssertTrue(tokens[0]->col == 1, "element 1 col");

    AssertTrue(tokens[1]->type == ATOM_TOKEN, "element 2 type");
    AssertTrue(tokens[1]->value == "bar", "element 2 value");
    AssertTrue(tokens[1]->line == 1, "element 2 line");
    AssertTrue(tokens[1]->col == 5, "element 2 col");

    AssertTrue(tokens[2]->type == ATOM_TOKEN, "element 3 type");
    AssertTrue(tokens[2]->value == "baz", "element 3 value");
    AssertTrue(tokens[2]->line == 3, "element 3 line");
    AssertTrue(tokens[2]->col == 2, "element 3 col");

    AssertTrue(tokens[3]->type == ATOM_TOKEN, "element 4 type");
    AssertTrue(tokens[3]->value == "quxx", "element 4 value");
    AssertTrue(tokens[3]->line == 4, "element 4 line");
    AssertTrue(tokens[3]->col == 1, "element 4 col");

    clear(tokens);        
}

inline void test_tokenize_basic_space_separated_numbers() {
    std::vector<token_t *> tokens;

    tokenize("10 323 2", tokens);

    AssertTrue(tokens[0]->type == NUMBER_TOKEN, "element 1 type");
    AssertTrue(tokens[0]->value == "10", "element 1 value");
    AssertTrue(tokens[0]->line == 1, "element 1 line");
    AssertTrue(tokens[0]->col == 1, "element 1 col");

    AssertTrue(tokens[1]->type == NUMBER_TOKEN, "element 2 type");
    AssertTrue(tokens[1]->value == "323", "element 2 value");
    AssertTrue(tokens[1]->line == 1, "element 2 line");
    AssertTrue(tokens[1]->col == 4, "element 2 col");

    AssertTrue(tokens[2]->type == NUMBER_TOKEN, "element 3 type");
    AssertTrue(tokens[2]->value == "2", "element 3 value");
    AssertTrue(tokens[2]->line == 1, "element 3 line");
    AssertTrue(tokens[2]->col == 8, "element 3 col");
    
    clear(tokens);        
}

inline void test_tokenize_space_and_new_line_separated_numbers() {
    std::vector<token_t *> tokens;

    tokenize("1 002\n\n 20\n320", tokens);

    AssertTrue(tokens[0]->type == NUMBER_TOKEN, "element 1 type");
    AssertTrue(tokens[0]->value == "1", "element 1 value");
    AssertTrue(tokens[0]->line == 1, "element 1 line");
    AssertTrue(tokens[0]->col == 1, "element 1 col");

    AssertTrue(tokens[1]->type == NUMBER_TOKEN, "element 2 type");
    AssertTrue(tokens[1]->value == "002", "element 2 value");
    AssertTrue(tokens[1]->line == 1, "element 2 line");
    AssertTrue(tokens[1]->col == 3, "element 2 col");

    AssertTrue(tokens[2]->type == NUMBER_TOKEN, "element 3 type");
    AssertTrue(tokens[2]->value == "20", "element 3 value");
    AssertTrue(tokens[2]->line == 3, "element 3 line");
    AssertTrue(tokens[2]->col == 2, "element 3 col");

    AssertTrue(tokens[3]->type == NUMBER_TOKEN, "element 4 type");
    AssertTrue(tokens[3]->value == "320", "element 4 value");
    AssertTrue(tokens[3]->line == 4, "element 4 line");
    AssertTrue(tokens[3]->col == 1, "element 4 col");
    
    clear(tokens);        
}

inline void test_tokenize_space_separated_mixed_numbers_and_atoms() {
    std::vector<token_t *> tokens;

    tokenize("foo 002 20 bar", tokens);

    AssertTrue(tokens[0]->type == ATOM_TOKEN, "element 1 type");
    AssertTrue(tokens[0]->value == "foo", "element 1 value");
    AssertTrue(tokens[0]->line == 1, "element 1 line");
    AssertTrue(tokens[0]->col == 1, "element 1 col");

    AssertTrue(tokens[1]->type == NUMBER_TOKEN, "element 2 type");
    AssertTrue(tokens[1]->value == "002", "element 2 value");
    AssertTrue(tokens[1]->line == 1, "element 2 line");
    AssertTrue(tokens[1]->col == 5, "element 2 col");

    AssertTrue(tokens[2]->type == NUMBER_TOKEN, "element 3 type");
    AssertTrue(tokens[2]->value == "20", "element 3 value");
    AssertTrue(tokens[2]->line == 1, "element 3 line");
    AssertTrue(tokens[2]->col == 9, "element 3 col");

    AssertTrue(tokens[3]->type == ATOM_TOKEN, "element 4 type");
    AssertTrue(tokens[3]->value == "bar", "element 4 value");
    AssertTrue(tokens[3]->line == 1, "element 4 line");
    AssertTrue(tokens[3]->col == 12, "element 4 col");
    
    clear(tokens);        
}

inline void test_tokenize_not_separated_by_space_numbers_and_atoms() {
    std::vector<token_t *> tokens;

    tokenize("2+5*3>1foo12bar44", tokens);

    AssertTrue(tokens[0]->type == NUMBER_TOKEN, "element 1 type");
    AssertTrue(tokens[0]->value == "2", "element 1 value");
    AssertTrue(tokens[0]->line == 1, "element 1 line");
    AssertTrue(tokens[0]->col == 1, "element 1 col");

    AssertTrue(tokens[1]->type == ATOM_TOKEN, "element 2 type");
    AssertTrue(tokens[1]->value == "+", "element 2 value");
    AssertTrue(tokens[1]->line == 1, "element 2 line");
    AssertTrue(tokens[1]->col == 2, "element 2 col");

    AssertTrue(tokens[2]->type == NUMBER_TOKEN, "element 3 type");
    AssertTrue(tokens[2]->value == "5", "element 3 value");
    AssertTrue(tokens[2]->line == 1, "element 3 line");
    AssertTrue(tokens[2]->col == 3, "element 3 col");

    AssertTrue(tokens[3]->type == ATOM_TOKEN, "element 4 type");
    AssertTrue(tokens[3]->value == "*", "element 4 value");
    AssertTrue(tokens[3]->line == 1, "element 4 line");
    AssertTrue(tokens[3]->col == 4, "element 4 col");

    AssertTrue(tokens[4]->type == NUMBER_TOKEN, "element 5 type");
    AssertTrue(tokens[4]->value == "3", "element 5 value");
    AssertTrue(tokens[4]->line == 1, "element 5 line");
    AssertTrue(tokens[4]->col == 5, "element 5 col");

    AssertTrue(tokens[5]->type == ATOM_TOKEN, "element 6 type");
    AssertTrue(tokens[5]->value == ">", "element 6 value");
    AssertTrue(tokens[5]->line == 1, "element 6 line");
    AssertTrue(tokens[5]->col == 6, "element 6 col");

    AssertTrue(tokens[6]->type == NUMBER_TOKEN, "element 7 type");
    AssertTrue(tokens[6]->value == "1", "element 7 value");
    AssertTrue(tokens[6]->line == 1, "element 7 line");
    AssertTrue(tokens[6]->col == 7, "element 7 col");

    AssertTrue(tokens[7]->type == ATOM_TOKEN, "element 8 type");
    AssertTrue(tokens[7]->value == "foo", "element 8 value");
    AssertTrue(tokens[7]->line == 1, "element 8 line");
    AssertTrue(tokens[7]->col == 8, "element 8 col");

    AssertTrue(tokens[8]->type == NUMBER_TOKEN, "element 9 type");
    AssertTrue(tokens[8]->value == "12", "element 9 value");
    AssertTrue(tokens[8]->line == 1, "element 9 line");
    AssertTrue(tokens[8]->col == 11, "element 9 col");

    AssertTrue(tokens[9]->type == ATOM_TOKEN, "element 10 type");
    AssertTrue(tokens[9]->value == "bar", "element 10 value");
    AssertTrue(tokens[9]->line == 1, "element 10 line");
    AssertTrue(tokens[9]->col == 13, "element 10 col");
    
    clear(tokens);        
}

void run_tokenizer_tests() {
    TESTCASE
    test_tokenize_basic_space_separated_atoms();
    test_tokenize_space_and_new_line_separated_atoms();
    test_tokenize_basic_space_separated_numbers();
    test_tokenize_space_and_new_line_separated_numbers();
    test_tokenize_space_separated_mixed_numbers_and_atoms();
    test_tokenize_not_separated_by_space_numbers_and_atoms();
}