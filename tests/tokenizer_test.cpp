#include <string>
#include <vector>
#include <iostream>

#include "test.hpp"
#include "tokenizer.hpp"
#include "token.hpp"
#include "utils.hpp"

using namespace cuttle;

inline void test_tokenize_basic_space_separated_atoms() {
	tokenizer_config_t config = { {},{},{},{},true };
    tokens_t tokens;

    tokenize(config, "foo bar baz", tokens);

    AssertTrue(tokens[0].type == token_type::atom, "element 1 type");
    AssertTrue(tokens[0].value == "foo", "element 1 value");
    AssertTrue(tokens[0].line == 1, "element 1 line");
    AssertTrue(tokens[0].col == 1, "element 1 col");

    AssertTrue(tokens[1].type == token_type::atom, "element 2 type");
    AssertTrue(tokens[1].value == "bar", "element 2 value");
    AssertTrue(tokens[1].line == 1, "element 2 line");
    AssertTrue(tokens[1].col == 5, "element 2 col");

    AssertTrue(tokens[2].type == token_type::atom, "element 3 type");
    AssertTrue(tokens[2].value == "baz", "element 3 value");
    AssertTrue(tokens[2].line == 1, "element 3 line");
    AssertTrue(tokens[2].col == 9, "element 3 col");
}

inline void test_tokenize_space_and_new_line_separated_atoms() {
	tokenizer_config_t config = { {},{},{},{},true };
	tokens_t tokens;

    tokenize(config, "foo bar\n\n baz\nquxx\twww", tokens);

    AssertTrue(tokens[0].type == token_type::atom, "element 1 type");
    AssertTrue(tokens[0].value == "foo", "element 1 value");
    AssertTrue(tokens[0].line == 1, "element 1 line");
    AssertTrue(tokens[0].col == 1, "element 1 col");

    AssertTrue(tokens[1].type == token_type::atom, "element 2 type");
    AssertTrue(tokens[1].value == "bar", "element 2 value");
    AssertTrue(tokens[1].line == 1, "element 2 line");
    AssertTrue(tokens[1].col == 5, "element 2 col");

    AssertTrue(tokens[2].type == token_type::atom, "element 3 type");
    AssertTrue(tokens[2].value == "baz", "element 3 value");
    AssertTrue(tokens[2].line == 3, "element 3 line");
    AssertTrue(tokens[2].col == 2, "element 3 col");

    AssertTrue(tokens[3].type == token_type::atom, "element 4 type");
    AssertTrue(tokens[3].value == "quxx", "element 4 value");
    AssertTrue(tokens[3].line == 4, "element 4 line");
    AssertTrue(tokens[3].col == 1, "element 4 col");

	AssertTrue(tokens[4].type == token_type::atom, "element 5 type");
	AssertTrue(tokens[4].value == "www", "element 5 value");
	AssertTrue(tokens[4].line == 4, "element 5 line");
	AssertTrue(tokens[4].col == 6, "element 5 col");
}

inline void test_tokenize_basic_space_separated_numbers() {
	tokenizer_config_t config = { {},{},{},{},true };
    tokens_t tokens;

    tokenize(config, "10 323 2", tokens);

    AssertTrue(tokens[0].type == token_type::number, "element 1 type");
    AssertTrue(tokens[0].value == "10", "element 1 value");
    AssertTrue(tokens[0].line == 1, "element 1 line");
    AssertTrue(tokens[0].col == 1, "element 1 col");

    AssertTrue(tokens[1].type == token_type::number, "element 2 type");
    AssertTrue(tokens[1].value == "323", "element 2 value");
    AssertTrue(tokens[1].line == 1, "element 2 line");
    AssertTrue(tokens[1].col == 4, "element 2 col");

    AssertTrue(tokens[2].type == token_type::number, "element 3 type");
    AssertTrue(tokens[2].value == "2", "element 3 value");
    AssertTrue(tokens[2].line == 1, "element 3 line");
    AssertTrue(tokens[2].col == 8, "element 3 col");
}

inline void test_tokenize_space_and_new_line_separated_numbers() {
	tokenizer_config_t config = { {},{},{},{},true };
    tokens_t tokens;

    tokenize(config, "1 002\n\n 20\n320", tokens);

    AssertTrue(tokens[0].type == token_type::number, "element 1 type");
    AssertTrue(tokens[0].value == "1", "element 1 value");
    AssertTrue(tokens[0].line == 1, "element 1 line");
    AssertTrue(tokens[0].col == 1, "element 1 col");

    AssertTrue(tokens[1].type == token_type::number, "element 2 type");
    AssertTrue(tokens[1].value == "002", "element 2 value");
    AssertTrue(tokens[1].line == 1, "element 2 line");
    AssertTrue(tokens[1].col == 3, "element 2 col");

    AssertTrue(tokens[2].type == token_type::number, "element 3 type");
    AssertTrue(tokens[2].value == "20", "element 3 value");
    AssertTrue(tokens[2].line == 3, "element 3 line");
    AssertTrue(tokens[2].col == 2, "element 3 col");

    AssertTrue(tokens[3].type == token_type::number, "element 4 type");
    AssertTrue(tokens[3].value == "320", "element 4 value");
    AssertTrue(tokens[3].line == 4, "element 4 line");
    AssertTrue(tokens[3].col == 1, "element 4 col");       
}

inline void test_tokenize_space_separated_mixed_numbers_and_atoms() {
	tokenizer_config_t config = { {},{},{},{},true };
    tokens_t tokens;

    tokenize(config, "foo 002 20 bar", tokens);

    AssertTrue(tokens[0].type == token_type::atom, "element 1 type");
    AssertTrue(tokens[0].value == "foo", "element 1 value");
    AssertTrue(tokens[0].line == 1, "element 1 line");
    AssertTrue(tokens[0].col == 1, "element 1 col");

    AssertTrue(tokens[1].type == token_type::number, "element 2 type");
    AssertTrue(tokens[1].value == "002", "element 2 value");
    AssertTrue(tokens[1].line == 1, "element 2 line");
    AssertTrue(tokens[1].col == 5, "element 2 col");

    AssertTrue(tokens[2].type == token_type::number, "element 3 type");
    AssertTrue(tokens[2].value == "20", "element 3 value");
    AssertTrue(tokens[2].line == 1, "element 3 line");
    AssertTrue(tokens[2].col == 9, "element 3 col");

    AssertTrue(tokens[3].type == token_type::atom, "element 4 type");
    AssertTrue(tokens[3].value == "bar", "element 4 value");
    AssertTrue(tokens[3].line == 1, "element 4 line");
    AssertTrue(tokens[3].col == 12, "element 4 col");      
}

inline void test_tokenize_not_separated_by_space_numbers_and_atoms() {
	tokenizer_config_t config = { {},{},{},{},true };
    tokens_t tokens;

    tokenize(config, "2+5*3>1foo12bar44", tokens);

    AssertTrue(tokens[0].type == token_type::number, "element 1 type");
    AssertTrue(tokens[0].value == "2", "element 1 value");
    AssertTrue(tokens[0].line == 1, "element 1 line");
    AssertTrue(tokens[0].col == 1, "element 1 col");

    AssertTrue(tokens[1].type == token_type::atom, "element 2 type");
    AssertTrue(tokens[1].value == "+", "element 2 value");
    AssertTrue(tokens[1].line == 1, "element 2 line");
    AssertTrue(tokens[1].col == 2, "element 2 col");

    AssertTrue(tokens[2].type == token_type::number, "element 3 type");
    AssertTrue(tokens[2].value == "5", "element 3 value");
    AssertTrue(tokens[2].line == 1, "element 3 line");
    AssertTrue(tokens[2].col == 3, "element 3 col");

    AssertTrue(tokens[3].type == token_type::atom, "element 4 type");
    AssertTrue(tokens[3].value == "*", "element 4 value");
    AssertTrue(tokens[3].line == 1, "element 4 line");
    AssertTrue(tokens[3].col == 4, "element 4 col");

    AssertTrue(tokens[4].type == token_type::number, "element 5 type");
    AssertTrue(tokens[4].value == "3", "element 5 value");
    AssertTrue(tokens[4].line == 1, "element 5 line");
    AssertTrue(tokens[4].col == 5, "element 5 col");

    AssertTrue(tokens[5].type == token_type::atom, "element 6 type");
    AssertTrue(tokens[5].value == ">", "element 6 value");
    AssertTrue(tokens[5].line == 1, "element 6 line");
    AssertTrue(tokens[5].col == 6, "element 6 col");

    AssertTrue(tokens[6].type == token_type::number, "element 7 type");
    AssertTrue(tokens[6].value == "1", "element 7 value");
    AssertTrue(tokens[6].line == 1, "element 7 line");
    AssertTrue(tokens[6].col == 7, "element 7 col");

    AssertTrue(tokens[7].type == token_type::atom, "element 8 type");
    AssertTrue(tokens[7].value == "foo", "element 8 value");
    AssertTrue(tokens[7].line == 1, "element 8 line");
    AssertTrue(tokens[7].col == 8, "element 8 col");

    AssertTrue(tokens[8].type == token_type::number, "element 9 type");
    AssertTrue(tokens[8].value == "12", "element 9 value");
    AssertTrue(tokens[8].line == 1, "element 9 line");
    AssertTrue(tokens[8].col == 11, "element 9 col");

    AssertTrue(tokens[9].type == token_type::atom, "element 10 type");
    AssertTrue(tokens[9].value == "bar", "element 10 value");
    AssertTrue(tokens[9].line == 1, "element 10 line");
    AssertTrue(tokens[9].col == 13, "element 10 col"); 

	AssertTrue(tokens[10].type == token_type::number, "element 11 type");
	AssertTrue(tokens[10].value == "44", "element 11 value");
	AssertTrue(tokens[10].line == 1, "element 11 line");
	AssertTrue(tokens[10].col == 16, "element 11 col");
}

inline void test_tokenize_not_separated_by_space_numbers_and_atoms_with_config_not_separate_digits_and_alpha() {
	tokenizer_config_t config = { {},{},{},{},false };
	tokens_t tokens;

	tokenize(config, "2+5*3>1foo12bar44", tokens);

	AssertEqual(tokens.size(), 2, "Tokens size");

	AssertEqual(tokens[0].type, token_type::number, "element 1 type");
	AssertEqual(tokens[0].value, "2", "element 1 value");
	AssertEqual(tokens[0].line, 1, "element 1 line");
	AssertEqual(tokens[0].col, 1, "element 1 col");

	AssertEqual(tokens[1].type, token_type::atom, "element 2 type");
	AssertEqual(tokens[1].value, "+5*3>1foo12bar44", "element 2 value");
	AssertEqual(tokens[1].line, 1, "element 2 line");
	AssertEqual(tokens[1].col, 2, "element 2 col");
}

inline void test_tokenize_basic_comments_with_endline() {
	tokenizer_config_t config = { {},{},{},{{"#", {"\n"}}},false };
	tokens_t tokens;

	tokenize(config, "2+5#2+5*3>1foo12\nbar44", tokens);

	AssertEqual(tokens.size(), 3, "Tokens size");

	AssertTrue(tokens[0].type == token_type::number, "element 1 type");
	AssertTrue(tokens[0].value == "2", "element 1 value");
	AssertTrue(tokens[0].line == 1, "element 1 line");
	AssertTrue(tokens[0].col == 1, "element 1 col");

	AssertTrue(tokens[1].type == token_type::atom, "element 2 type");
	AssertTrue(tokens[1].value == "+5", "element 2 value");
	AssertTrue(tokens[1].line == 1, "element 2 line");
	AssertTrue(tokens[1].col == 2, "element 2 col");

	AssertTrue(tokens[2].type == token_type::atom, "element 3 type");
	AssertTrue(tokens[2].value == "bar44", "element 3 value");
	AssertTrue(tokens[2].line == 2, "element 3 line");
	AssertTrue(tokens[2].col == 1, "element 3 col");
}

inline void test_tokenize_basic_comments_with_endline_and_spaces() {
	tokenizer_config_t config = { {},{},{},{ { "#",{ "\n" } } },false };
	tokens_t tokens;

	tokenize(config, "2+5 #2+5*3>1foo12\nbar44", tokens);

	AssertEqual(tokens.size(), 3, "Tokens size");

	AssertTrue(tokens[0].type == token_type::number, "element 1 type");
	AssertTrue(tokens[0].value == "2", "element 1 value");
	AssertTrue(tokens[0].line == 1, "element 1 line");
	AssertTrue(tokens[0].col == 1, "element 1 col");

	AssertTrue(tokens[1].type == token_type::atom, "element 2 type");
	AssertTrue(tokens[1].value == "+5", "element 2 value");
	AssertTrue(tokens[1].line == 1, "element 2 line");
	AssertTrue(tokens[1].col == 2, "element 2 col");

	AssertTrue(tokens[2].type == token_type::atom, "element 3 type");
	AssertTrue(tokens[2].value == "bar44", "element 3 value");
	AssertTrue(tokens[2].line == 2, "element 3 line");
	AssertTrue(tokens[2].col == 1, "element 3 col");
}

inline void test_tokenize_basic_comments_with_two_characters() {
	tokenizer_config_t config = { {},{},{},{ { "//",{ "\n" } } },false };
	tokens_t tokens;

	tokenize(config, "2+5//2+5*3>1foo12\nbar44", tokens);

	AssertEqual(tokens.size(), 3, "Tokens size");

	AssertTrue(tokens[0].type == token_type::number, "element 1 type");
	AssertTrue(tokens[0].value == "2", "element 1 value");
	AssertTrue(tokens[0].line == 1, "element 1 line");
	AssertTrue(tokens[0].col == 1, "element 1 col");

	AssertTrue(tokens[1].type == token_type::atom, "element 2 type");
	AssertTrue(tokens[1].value == "+5", "element 2 value");
	AssertTrue(tokens[1].line == 1, "element 2 line");
	AssertTrue(tokens[1].col == 2, "element 2 col");

	AssertTrue(tokens[2].type == token_type::atom, "element 3 type");
	AssertTrue(tokens[2].value == "bar44", "element 3 value");
	AssertTrue(tokens[2].line == 2, "element 3 line");
	AssertTrue(tokens[2].col == 1, "element 3 col");
}

inline void test_tokenize_basic_multiline_comments_two_characters() {
	tokenizer_config_t config = { {},{},{},{ { "/*",{ "*/" } } },false };
	tokens_t tokens;

	tokenize(config, "2+5/*2+5*3>1foo12*/bar44", tokens);

	AssertEqual(tokens.size(), 3, "Tokens size");

	AssertTrue(tokens[0].type == token_type::number, "element 1 type");
	AssertTrue(tokens[0].value == "2", "element 1 value");
	AssertTrue(tokens[0].line == 1, "element 1 line");
	AssertTrue(tokens[0].col == 1, "element 1 col");

	AssertTrue(tokens[1].type == token_type::atom, "element 2 type");
	AssertTrue(tokens[1].value == "+5", "element 2 value");
	AssertTrue(tokens[1].line == 1, "element 2 line");
	AssertTrue(tokens[1].col == 2, "element 2 col");

	AssertTrue(tokens[2].type == token_type::atom, "element 3 type");
	AssertTrue(tokens[2].value == "bar44", "element 3 value");
	AssertTrue(tokens[2].line == 1, "element 3 line");
	AssertTrue(tokens[2].col == 20, "element 3 col");
}

inline void test_tokenize_normal_string() {
	tokenizer_config_t config = { {},{ { "'", {"'"} } },{},{},false };
	tokens_t tokens;

	tokenize(config, "2+5'foo'", tokens);

	AssertEqual(tokens.size(), 3, "Tokens size");

	AssertTrue(tokens[0].type == token_type::number, "element 1 type");
	AssertTrue(tokens[0].value == "2", "element 1 value");
	AssertTrue(tokens[0].line == 1, "element 1 line");
	AssertTrue(tokens[0].col == 1, "element 1 col");

	AssertTrue(tokens[1].type == token_type::atom, "element 2 type");
	AssertTrue(tokens[1].value == "+5", "element 2 value");
	AssertTrue(tokens[1].line == 1, "element 2 line");
	AssertTrue(tokens[1].col == 2, "element 2 col");

	AssertTrue(tokens[2].type == token_type::string, "element 3 type");
	AssertTrue(tokens[2].value == "foo", "element 3 value");
	AssertTrue(tokens[2].line == 1, "element 3 line");
	AssertTrue(tokens[2].col == 4, "element 3 col");
}

inline void test_tokenize_normal_string_with_endlines() {
	tokenizer_config_t config = { {},{ { "'",{ "'" } } },{},{},false };
	tokens_t tokens;

	tokenize(config, "2+5'foo\nbar\n\\n'", tokens);

	AssertEqual(tokens.size(), 3, "Tokens size");

	AssertTrue(tokens[0].type == token_type::number, "element 1 type");
	AssertTrue(tokens[0].value == "2", "element 1 value");
	AssertTrue(tokens[0].line == 1, "element 1 line");
	AssertTrue(tokens[0].col == 1, "element 1 col");

	AssertTrue(tokens[1].type == token_type::atom, "element 2 type");
	AssertTrue(tokens[1].value == "+5", "element 2 value");
	AssertTrue(tokens[1].line == 1, "element 2 line");
	AssertTrue(tokens[1].col == 2, "element 2 col");

	AssertTrue(tokens[2].type == token_type::string, "element 3 type");
	AssertTrue(tokens[2].value == "foo\nbar\n\\n", "element 3 value");
	AssertTrue(tokens[2].line == 1, "element 3 line");
	AssertTrue(tokens[2].col == 4, "element 3 col");
}

inline void test_tokenize_formatted_string() {
	tokenizer_config_t config = { { { "'",{ "'" } } },{},{},{},false };
	tokens_t tokens;

	tokenize(config, "2+5'foo\\t\\n\\r'", tokens);

	AssertEqual(tokens.size(), 3, "Tokens size");

	AssertTrue(tokens[0].type == token_type::number, "element 1 type");
	AssertTrue(tokens[0].value == "2", "element 1 value");
	AssertTrue(tokens[0].line == 1, "element 1 line");
	AssertTrue(tokens[0].col == 1, "element 1 col");

	AssertTrue(tokens[1].type == token_type::atom, "element 2 type");
	AssertTrue(tokens[1].value == "+5", "element 2 value");
	AssertTrue(tokens[1].line == 1, "element 2 line");
	AssertTrue(tokens[1].col == 2, "element 2 col");

	AssertTrue(tokens[2].type == token_type::string, "element 3 type");
	AssertTrue(tokens[2].value == "foo\t\n\r", "element 3 value");
	AssertTrue(tokens[2].line == 1, "element 3 line");
	AssertTrue(tokens[2].col == 4, "element 3 col");
}

inline void test_tokenize_formatted_string_with_endlines() {
	tokenizer_config_t config = { { { "'",{ "'" } }},{},{},{},false };
	tokens_t tokens;

	tokenize(config, "2+5'foo\nbar\n\\n\\t\\''", tokens);

	AssertEqual(tokens.size(), 3, "Tokens size");

	AssertTrue(tokens[0].type == token_type::number, "element 1 type");
	AssertTrue(tokens[0].value == "2", "element 1 value");
	AssertTrue(tokens[0].line == 1, "element 1 line");
	AssertTrue(tokens[0].col == 1, "element 1 col");

	AssertTrue(tokens[1].type == token_type::atom, "element 2 type");
	AssertTrue(tokens[1].value == "+5", "element 2 value");
	AssertTrue(tokens[1].line == 1, "element 2 line");
	AssertTrue(tokens[1].col == 2, "element 2 col");

	AssertTrue(tokens[2].type == token_type::string, "element 3 type");
	AssertTrue(tokens[2].value == "foo\nbar\n\n\t'", "element 3 value");
	AssertTrue(tokens[2].line == 1, "element 3 line");
	AssertTrue(tokens[2].col == 4, "element 3 col");
}

inline void test_tokenize_separated_symbols() {
	tokenizer_config_t config = { {},{},{ { "+", "-", "*","=" } },{},false };
	tokens_t tokens;

	tokenize(config, "foo123+a\n2a+5-1*5", tokens);

	AssertEqual(tokens.size(), 11, "Tokens size");

	AssertTrue(tokens[0].type == token_type::atom, "element 1 type");
	AssertTrue(tokens[0].value == "foo123", "element 1 value");
	AssertTrue(tokens[0].line == 1, "element 1 line");
	AssertTrue(tokens[0].col == 1, "element 1 col");

	AssertTrue(tokens[1].type == token_type::atom, "element 2 type");
	AssertTrue(tokens[1].value == "+", "element 2 value");
	AssertTrue(tokens[1].line == 1, "element 2 line");
	AssertTrue(tokens[1].col == 7, "element 2 col");

	AssertTrue(tokens[2].type == token_type::atom, "element 3 type");
	AssertTrue(tokens[2].value == "a", "element 3 value");
	AssertTrue(tokens[2].line == 1, "element 3 line");
	AssertTrue(tokens[2].col == 8, "element 3 col");

	AssertTrue(tokens[3].type == token_type::number, "element 4 type");
	AssertTrue(tokens[3].value == "2", "element 4 value");
	AssertTrue(tokens[3].line == 2, "element 4 line");
	AssertTrue(tokens[3].col == 1, "element 4 col");

	AssertTrue(tokens[4].type == token_type::atom, "element 5 type");
	AssertTrue(tokens[4].value == "a", "element 5 value");
	AssertTrue(tokens[4].line == 2, "element 5 line");
	AssertTrue(tokens[4].col == 2, "element 5 col");

	AssertTrue(tokens[5].type == token_type::atom, "element 6 type");
	AssertTrue(tokens[5].value == "+", "element 6 value");
	AssertTrue(tokens[5].line == 2, "element 6 line");
	AssertTrue(tokens[5].col == 3, "element 6 col");

	AssertTrue(tokens[6].type == token_type::number, "element 7 type");
	AssertTrue(tokens[6].value == "5", "element 7 value");
	AssertTrue(tokens[6].line == 2, "element 7 line");
	AssertTrue(tokens[6].col == 4, "element 7 col");

	AssertTrue(tokens[7].type == token_type::atom, "element 8 type");
	AssertTrue(tokens[7].value == "-", "element 8 value");
	AssertTrue(tokens[7].line == 2, "element 8 line");
	AssertTrue(tokens[7].col == 5, "element 8 col");

	AssertTrue(tokens[8].type == token_type::number, "element 9 type");
	AssertTrue(tokens[8].value == "1", "element 9 value");
	AssertTrue(tokens[8].line == 2, "element 9 line");
	AssertTrue(tokens[8].col == 6, "element 9 col");

	AssertTrue(tokens[9].type == token_type::atom, "element 10 type");
	AssertTrue(tokens[9].value == "*", "element 10 value");
	AssertTrue(tokens[9].line == 2, "element 10 line");
	AssertTrue(tokens[9].col == 7, "element 10 col");

	AssertTrue(tokens[10].type == token_type::number, "element 11 type");
	AssertTrue(tokens[10].value == "5", "element 11 value");
	AssertTrue(tokens[10].line == 2, "element 11 line");
	AssertTrue(tokens[10].col == 8, "element 11 col");
}

inline void test_tokenize_separated_symbols_with_spaces() {
	tokenizer_config_t config = { {},{},{{"+", "-", "*","="}},{},false };
	tokens_t tokens;

	tokenize(config, "foo123   +a\n  2a+\t5-1*5", tokens);

	AssertEqual(tokens.size(), 11, "Tokens size");

	AssertTrue(tokens[0].type == token_type::atom, "element 1 type");
	AssertTrue(tokens[0].value == "foo123", "element 1 value");
	AssertTrue(tokens[0].line == 1, "element 1 line");
	AssertTrue(tokens[0].col == 1, "element 1 col");

	AssertTrue(tokens[1].type == token_type::atom, "element 2 type");
	AssertTrue(tokens[1].value == "+", "element 2 value");
	AssertTrue(tokens[1].line == 1, "element 2 line");
	AssertTrue(tokens[1].col == 10, "element 2 col");

	AssertTrue(tokens[2].type == token_type::atom, "element 3 type");
	AssertTrue(tokens[2].value == "a", "element 3 value");
	AssertTrue(tokens[2].line == 1, "element 3 line");
	AssertTrue(tokens[2].col == 11, "element 3 col");

	AssertTrue(tokens[3].type == token_type::number, "element 4 type");
	AssertTrue(tokens[3].value == "2", "element 4 value");
	AssertTrue(tokens[3].line == 2, "element 4 line");
	AssertTrue(tokens[3].col == 3, "element 4 col");

	AssertTrue(tokens[4].type == token_type::atom, "element 5 type");
	AssertTrue(tokens[4].value == "a", "element 5 value");
	AssertTrue(tokens[4].line == 2, "element 5 line");
	AssertTrue(tokens[4].col == 4, "element 5 col");

	AssertTrue(tokens[5].type == token_type::atom, "element 6 type");
	AssertTrue(tokens[5].value == "+", "element 6 value");
	AssertTrue(tokens[5].line == 2, "element 6 line");
	AssertTrue(tokens[5].col == 5, "element 6 col");

	AssertTrue(tokens[6].type == token_type::number, "element 7 type");
	AssertTrue(tokens[6].value == "5", "element 7 value");
	AssertTrue(tokens[6].line == 2, "element 7 line");
	AssertTrue(tokens[6].col == 7, "element 7 col");

	AssertTrue(tokens[7].type == token_type::atom, "element 8 type");
	AssertTrue(tokens[7].value == "-", "element 8 value");
	AssertTrue(tokens[7].line == 2, "element 8 line");
	AssertTrue(tokens[7].col == 8, "element 8 col");

	AssertTrue(tokens[8].type == token_type::number, "element 9 type");
	AssertTrue(tokens[8].value == "1", "element 9 value");
	AssertTrue(tokens[8].line == 2, "element 9 line");
	AssertTrue(tokens[8].col == 9, "element 9 col");

	AssertTrue(tokens[9].type == token_type::atom, "element 10 type");
	AssertTrue(tokens[9].value == "*", "element 10 value");
	AssertTrue(tokens[9].line == 2, "element 10 line");
	AssertTrue(tokens[9].col == 10, "element 10 col");

	AssertTrue(tokens[10].type == token_type::number, "element 11 type");
	AssertTrue(tokens[10].value == "5", "element 11 value");
	AssertTrue(tokens[10].line == 2, "element 11 line");
	AssertTrue(tokens[10].col == 11, "element 11 col");
}

void run_tokenizer_tests() {
    TESTCASE
    test_tokenize_basic_space_separated_atoms();
    test_tokenize_space_and_new_line_separated_atoms();
    test_tokenize_basic_space_separated_numbers();
    test_tokenize_space_and_new_line_separated_numbers();
    test_tokenize_space_separated_mixed_numbers_and_atoms();
    test_tokenize_not_separated_by_space_numbers_and_atoms();
	test_tokenize_not_separated_by_space_numbers_and_atoms_with_config_not_separate_digits_and_alpha();
	test_tokenize_basic_comments_with_endline();
	test_tokenize_basic_comments_with_endline_and_spaces();
	test_tokenize_basic_comments_with_two_characters();
	test_tokenize_basic_multiline_comments_two_characters();
	test_tokenize_normal_string();
	test_tokenize_normal_string_with_endlines();
	test_tokenize_formatted_string();
	test_tokenize_formatted_string_with_endlines();
	test_tokenize_separated_symbols();
	test_tokenize_separated_symbols_with_spaces();
}