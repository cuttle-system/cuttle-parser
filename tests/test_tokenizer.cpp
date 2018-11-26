#define BOOST_TEST_DYN_LINK

#include <iostream>
#include <boost/test/unit_test.hpp>
#include <string>
#include <vector>

#include "tokenizer.hpp"
#include "token.hpp"
#include "utils.hpp"

using namespace cuttle;

BOOST_AUTO_TEST_SUITE(tokenizer_test_suite)

    BOOST_AUTO_TEST_CASE(tokenize_basic_space_separated_atoms) {
        tokenizer_config_t config = {{}, {}, {}, {}, {}, {}, {}, {}, {}, {},{}, {}, {}, {}, {}, {}, {}, true};
        tokens_t tokens;

        tokenize(config, "foo bar baz", tokens);

        BOOST_CHECK(tokens[0].type == token_type::atom);
        BOOST_CHECK(tokens[0].value == "foo");
        BOOST_CHECK(tokens[0].line == 1);
        BOOST_CHECK(tokens[0].col == 1);

        BOOST_CHECK(tokens[1].type == token_type::atom);
        BOOST_CHECK(tokens[1].value == "bar");
        BOOST_CHECK(tokens[1].line == 1);
        BOOST_CHECK(tokens[1].col == 5);

        BOOST_CHECK(tokens[2].type == token_type::atom);
        BOOST_CHECK(tokens[2].value == "baz");
        BOOST_CHECK(tokens[2].line == 1);
        BOOST_CHECK(tokens[2].col == 9);
    }

    BOOST_AUTO_TEST_CASE(tokenize_space_and_new_line_separated_atoms) {
        tokenizer_config_t config = {{}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {},{}, true};
        tokens_t tokens;

        tokenize(config, "foo bar\n\n baz\nquxx\twww", tokens);

        BOOST_CHECK(tokens[0].type == token_type::atom);
        BOOST_CHECK(tokens[0].value == "foo");
        BOOST_CHECK(tokens[0].line == 1);
        BOOST_CHECK(tokens[0].col == 1);

        BOOST_CHECK(tokens[1].type == token_type::atom);
        BOOST_CHECK(tokens[1].value == "bar");
        BOOST_CHECK(tokens[1].line == 1);
        BOOST_CHECK(tokens[1].col == 5);

        BOOST_CHECK(tokens[2].type == token_type::atom);
        BOOST_CHECK(tokens[2].value == "baz");
        BOOST_CHECK(tokens[2].line == 3);
        BOOST_CHECK(tokens[2].col == 2);

        BOOST_CHECK(tokens[3].type == token_type::atom);
        BOOST_CHECK(tokens[3].value == "quxx");
        BOOST_CHECK(tokens[3].line == 4);
        BOOST_CHECK(tokens[3].col == 1);

        BOOST_CHECK(tokens[4].type == token_type::atom);
        BOOST_CHECK(tokens[4].value == "www");
        BOOST_CHECK(tokens[4].line == 4);
        BOOST_CHECK(tokens[4].col == 6);
    }


    BOOST_AUTO_TEST_CASE(tokenize_basic_space_separated_numbers) {
        tokenizer_config_t config = {{}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, true};
        tokens_t tokens;

        tokenize(config, "10 323 2", tokens);

        BOOST_CHECK(tokens[0].type == token_type::number);
        BOOST_CHECK(tokens[0].value == "10");
        BOOST_CHECK(tokens[0].line == 1);
        BOOST_CHECK(tokens[0].col == 1);

        BOOST_CHECK(tokens[1].type == token_type::number);
        BOOST_CHECK(tokens[1].value == "323");
        BOOST_CHECK(tokens[1].line == 1);
        BOOST_CHECK(tokens[1].col == 4);

        BOOST_CHECK(tokens[2].type == token_type::number);
        BOOST_CHECK(tokens[2].value == "2");
        BOOST_CHECK(tokens[2].line == 1);
        BOOST_CHECK(tokens[2].col == 8);
    }

    BOOST_AUTO_TEST_CASE(tokenize_space_and_new_line_separated_numbers) {
        tokenizer_config_t config = {{}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, true};
        tokens_t tokens;

        tokenize(config, "1 002\n\n 20\n320", tokens);

        BOOST_CHECK(tokens[0].type == token_type::number);
        BOOST_CHECK(tokens[0].value == "1");
        BOOST_CHECK(tokens[0].line == 1);
        BOOST_CHECK(tokens[0].col == 1);

        BOOST_CHECK(tokens[1].type == token_type::number);
        BOOST_CHECK(tokens[1].value == "002");
        BOOST_CHECK(tokens[1].line == 1);
        BOOST_CHECK(tokens[1].col == 3);

        BOOST_CHECK(tokens[2].type == token_type::number);
        BOOST_CHECK(tokens[2].value == "20");
        BOOST_CHECK(tokens[2].line == 3);
        BOOST_CHECK(tokens[2].col == 2);

        BOOST_CHECK(tokens[3].type == token_type::number);
        BOOST_CHECK(tokens[3].value == "320");
        BOOST_CHECK(tokens[3].line == 4);
        BOOST_CHECK(tokens[3].col == 1);
    }

    BOOST_AUTO_TEST_CASE(tokenize_space_separated_mixed_numbers_and_atoms) {
        tokenizer_config_t config = {{}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, true};
        tokens_t tokens;

        tokenize(config, "foo 002 20 bar", tokens);

        BOOST_CHECK(tokens[0].type == token_type::atom);
        BOOST_CHECK(tokens[0].value == "foo");
        BOOST_CHECK(tokens[0].line == 1);
        BOOST_CHECK(tokens[0].col == 1);

        BOOST_CHECK(tokens[1].type == token_type::number);
        BOOST_CHECK(tokens[1].value == "002");
        BOOST_CHECK(tokens[1].line == 1);
        BOOST_CHECK(tokens[1].col == 5);

        BOOST_CHECK(tokens[2].type == token_type::number);
        BOOST_CHECK(tokens[2].value == "20");
        BOOST_CHECK(tokens[2].line == 1);
        BOOST_CHECK(tokens[2].col == 9);

        BOOST_CHECK(tokens[3].type == token_type::atom);
        BOOST_CHECK(tokens[3].value == "bar");
        BOOST_CHECK(tokens[3].line == 1);
        BOOST_CHECK(tokens[3].col == 12);
    }

    BOOST_AUTO_TEST_CASE(tokenize_not_separated_by_space_numbers_and_atoms) {
        tokenizer_config_t config = {{}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, true};
        tokens_t tokens;

        tokenize(config, "2+5*3>1foo12bar44", tokens);

        BOOST_CHECK(tokens[0].type == token_type::number);
        BOOST_CHECK(tokens[0].value == "2");
        BOOST_CHECK(tokens[0].line == 1);
        BOOST_CHECK(tokens[0].col == 1);

        BOOST_CHECK(tokens[1].type == token_type::atom);
        BOOST_CHECK(tokens[1].value == "+");
        BOOST_CHECK(tokens[1].line == 1);
        BOOST_CHECK(tokens[1].col == 2);

        BOOST_CHECK(tokens[2].type == token_type::number);
        BOOST_CHECK(tokens[2].value == "5");
        BOOST_CHECK(tokens[2].line == 1);
        BOOST_CHECK(tokens[2].col == 3);

        BOOST_CHECK(tokens[3].type == token_type::atom);
        BOOST_CHECK(tokens[3].value == "*");
        BOOST_CHECK(tokens[3].line == 1);
        BOOST_CHECK(tokens[3].col == 4);

        BOOST_CHECK(tokens[4].type == token_type::number);
        BOOST_CHECK(tokens[4].value == "3");
        BOOST_CHECK(tokens[4].line == 1);
        BOOST_CHECK(tokens[4].col == 5);

        BOOST_CHECK(tokens[5].type == token_type::atom);
        BOOST_CHECK(tokens[5].value == ">");
        BOOST_CHECK(tokens[5].line == 1);
        BOOST_CHECK(tokens[5].col == 6);

        BOOST_CHECK(tokens[6].type == token_type::number);
        BOOST_CHECK(tokens[6].value == "1");
        BOOST_CHECK(tokens[6].line == 1);
        BOOST_CHECK(tokens[6].col == 7);

        BOOST_CHECK(tokens[7].type == token_type::atom);
        BOOST_CHECK(tokens[7].value == "foo");
        BOOST_CHECK(tokens[7].line == 1);
        BOOST_CHECK(tokens[7].col == 8);

        BOOST_CHECK(tokens[8].type == token_type::number);
        BOOST_CHECK(tokens[8].value == "12");
        BOOST_CHECK(tokens[8].line == 1);
        BOOST_CHECK(tokens[8].col == 11);

        BOOST_CHECK(tokens[9].type == token_type::atom);
        BOOST_CHECK(tokens[9].value == "bar");
        BOOST_CHECK(tokens[9].line == 1);
        BOOST_CHECK(tokens[9].col == 13);

        BOOST_CHECK(tokens[10].type == token_type::number);
        BOOST_CHECK(tokens[10].value == "44");
        BOOST_CHECK(tokens[10].line == 1);
        BOOST_CHECK(tokens[10].col == 16);
    }

    BOOST_AUTO_TEST_CASE(tokenize_not_separated_by_space_numbers_and_atoms_with_config_not_separate_digits_and_alpha) {
        tokenizer_config_t config = {{}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, false};
        tokens_t tokens;

        tokenize(config, "2+5*3>1foo12bar44", tokens);

        BOOST_CHECK_EQUAL(tokens.size(), 2u);

        BOOST_CHECK_EQUAL(tokens[0].type, token_type::number);
        BOOST_CHECK_EQUAL(tokens[0].value, "2");
        BOOST_CHECK_EQUAL(tokens[0].line, 1);
        BOOST_CHECK_EQUAL(tokens[0].col, 1);

        BOOST_CHECK_EQUAL(tokens[1].type, token_type::atom);
        BOOST_CHECK_EQUAL(tokens[1].value, "+5*3>1foo12bar44");
        BOOST_CHECK_EQUAL(tokens[1].line, 1);
        BOOST_CHECK_EQUAL(tokens[1].col, 2);
    }

    BOOST_AUTO_TEST_CASE(tokenize_basic_comments_with_endline) {
        tokenizer_config_t config = {{}, {}, {}, {{"#", {"\n"}}}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, false};
        tokens_t tokens;

        tokenize(config, "2+5#2+5*3>1foo12\nbar44", tokens);

        BOOST_CHECK_EQUAL(tokens.size(), 3u);

        BOOST_CHECK(tokens[0].type == token_type::number);
        BOOST_CHECK(tokens[0].value == "2");
        BOOST_CHECK(tokens[0].line == 1);
        BOOST_CHECK(tokens[0].col == 1);

        BOOST_CHECK(tokens[1].type == token_type::atom);
        BOOST_CHECK(tokens[1].value == "+5");
        BOOST_CHECK(tokens[1].line == 1);
        BOOST_CHECK(tokens[1].col == 2);

        BOOST_CHECK(tokens[2].type == token_type::atom);
        BOOST_CHECK(tokens[2].value == "bar44");
        BOOST_CHECK(tokens[2].line == 2);
        BOOST_CHECK(tokens[2].col == 1);
    }

    BOOST_AUTO_TEST_CASE(tokenize_basic_comments_with_endline_and_spaces) {
        tokenizer_config_t config = {{}, {}, {}, {{"#", {"\n"}}}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, false};
        tokens_t tokens;

        tokenize(config, "2+5 #2+5*3>1foo12\nbar44", tokens);

        BOOST_CHECK_EQUAL(tokens.size(), 3u);

        BOOST_CHECK(tokens[0].type == token_type::number);
        BOOST_CHECK(tokens[0].value == "2");
        BOOST_CHECK(tokens[0].line == 1);
        BOOST_CHECK(tokens[0].col == 1);

        BOOST_CHECK(tokens[1].type == token_type::atom);
        BOOST_CHECK(tokens[1].value == "+5");
        BOOST_CHECK(tokens[1].line == 1);
        BOOST_CHECK(tokens[1].col == 2);

        BOOST_CHECK(tokens[2].type == token_type::atom);
        BOOST_CHECK(tokens[2].value == "bar44");
        BOOST_CHECK(tokens[2].line == 2);
        BOOST_CHECK(tokens[2].col == 1);
    }

    BOOST_AUTO_TEST_CASE(tokenize_basic_comments_with_two_characters) {
        tokenizer_config_t config = {{}, {}, {}, {{"//", {"\n"}}}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, false};
        tokens_t tokens;

        tokenize(config, "2+5//2+5*3>1foo12\nbar44", tokens);

        BOOST_CHECK_EQUAL(tokens.size(), 3u);

        BOOST_CHECK(tokens[0].type == token_type::number);
        BOOST_CHECK(tokens[0].value == "2");
        BOOST_CHECK(tokens[0].line == 1);
        BOOST_CHECK(tokens[0].col == 1);

        BOOST_CHECK(tokens[1].type == token_type::atom);
        BOOST_CHECK(tokens[1].value == "+5");
        BOOST_CHECK(tokens[1].line == 1);
        BOOST_CHECK(tokens[1].col == 2);

        BOOST_CHECK(tokens[2].type == token_type::atom);
        BOOST_CHECK(tokens[2].value == "bar44");
        BOOST_CHECK(tokens[2].line == 2);
        BOOST_CHECK(tokens[2].col == 1);
    }

    BOOST_AUTO_TEST_CASE(tokenize_basic_multiline_comments_two_characters) {
        tokenizer_config_t config = {{}, {}, {}, {{"/*", {"*/"}}}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, false};
        tokens_t tokens;

        tokenize(config, "2+5/*2+5*3>1foo12*/bar44", tokens);

        BOOST_CHECK_EQUAL(tokens.size(), 3u);

        BOOST_CHECK(tokens[0].type == token_type::number);
        BOOST_CHECK(tokens[0].value == "2");
        BOOST_CHECK(tokens[0].line == 1);
        BOOST_CHECK(tokens[0].col == 1);

        BOOST_CHECK(tokens[1].type == token_type::atom);
        BOOST_CHECK(tokens[1].value == "+5");
        BOOST_CHECK(tokens[1].line == 1);
        BOOST_CHECK(tokens[1].col == 2);

        BOOST_CHECK(tokens[2].type == token_type::atom);
        BOOST_CHECK(tokens[2].value == "bar44");
        BOOST_CHECK(tokens[2].line == 1);
        BOOST_CHECK(tokens[2].col == 20);
    }

    BOOST_AUTO_TEST_CASE(tokenize_normal_string) {
        tokenizer_config_t config = {{}, {{"'", {"'"}}}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, false};
        tokens_t tokens;

        tokenize(config, "2+5'foo'", tokens);

        BOOST_CHECK_EQUAL(tokens.size(), 3u);

        BOOST_CHECK(tokens[0].type == token_type::number);
        BOOST_CHECK(tokens[0].value == "2");
        BOOST_CHECK(tokens[0].line == 1);
        BOOST_CHECK(tokens[0].col == 1);

        BOOST_CHECK(tokens[1].type == token_type::atom);
        BOOST_CHECK(tokens[1].value == "+5");
        BOOST_CHECK(tokens[1].line == 1);
        BOOST_CHECK(tokens[1].col == 2);

        BOOST_CHECK(tokens[2].type == token_type::string);
        BOOST_CHECK(tokens[2].value == "foo");
        BOOST_CHECK(tokens[2].line == 1);
        BOOST_CHECK(tokens[2].col == 4);
    }

    BOOST_AUTO_TEST_CASE(tokenize_normal_string_with_endlines) {
        tokenizer_config_t config = {{}, {{"'", {"'"}}}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, false};
        tokens_t tokens;

        tokenize(config, "2+5'foo\nbar\n\\n'", tokens);

        BOOST_CHECK_EQUAL(tokens.size(), 3u);

        BOOST_CHECK(tokens[0].type == token_type::number);
        BOOST_CHECK(tokens[0].value == "2");
        BOOST_CHECK(tokens[0].line == 1);
        BOOST_CHECK(tokens[0].col == 1);

        BOOST_CHECK(tokens[1].type == token_type::atom);
        BOOST_CHECK(tokens[1].value == "+5");
        BOOST_CHECK(tokens[1].line == 1);
        BOOST_CHECK(tokens[1].col == 2);

        BOOST_CHECK(tokens[2].type == token_type::string);
        BOOST_CHECK(tokens[2].value == "foo\nbar\n\\n");
        BOOST_CHECK(tokens[2].line == 1);
        BOOST_CHECK(tokens[2].col == 4);
    }

    BOOST_AUTO_TEST_CASE(tokenize_formatted_string) {
        tokenizer_config_t config = {{{"'", {"'"}}}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, false};
        tokens_t tokens;

        tokenize(config, "2+5'foo\\t\\n\\r'", tokens);

        BOOST_CHECK_EQUAL(tokens.size(), 3u);

        BOOST_CHECK(tokens[0].type == token_type::number);
        BOOST_CHECK(tokens[0].value == "2");
        BOOST_CHECK(tokens[0].line == 1);
        BOOST_CHECK(tokens[0].col == 1);

        BOOST_CHECK(tokens[1].type == token_type::atom);
        BOOST_CHECK(tokens[1].value == "+5");
        BOOST_CHECK(tokens[1].line == 1);
        BOOST_CHECK(tokens[1].col == 2);

        BOOST_CHECK(tokens[2].type == token_type::string);
        BOOST_CHECK(tokens[2].value == "foo\t\n\r");
        BOOST_CHECK(tokens[2].line == 1);
        BOOST_CHECK(tokens[2].col == 4);
    }

    BOOST_AUTO_TEST_CASE(tokenize_formatted_string_with_endlines) {
        tokenizer_config_t config = {{{"'", {"'"}}}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, false};
        tokens_t tokens;

        tokenize(config, "2+5'foo\nbar\n\\n\\t\\''", tokens);

        BOOST_CHECK_EQUAL(tokens.size(), 3u);

        BOOST_CHECK(tokens[0].type == token_type::number);
        BOOST_CHECK(tokens[0].value == "2");
        BOOST_CHECK(tokens[0].line == 1);
        BOOST_CHECK(tokens[0].col == 1);

        BOOST_CHECK(tokens[1].type == token_type::atom);
        BOOST_CHECK(tokens[1].value == "+5");
        BOOST_CHECK(tokens[1].line == 1);
        BOOST_CHECK(tokens[1].col == 2);

        BOOST_CHECK(tokens[2].type == token_type::string);
        BOOST_CHECK(tokens[2].value == "foo\nbar\n\n\t'");
        BOOST_CHECK(tokens[2].line == 1);
        BOOST_CHECK(tokens[2].col == 4);
    }

    BOOST_AUTO_TEST_CASE(tokenize_empty_string) {
        tokenizer_config_t config = {{{"'", {"'"}}}, {{{"\"", {"\""}}}}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, false};
        tokens_t tokens;

        tokenize(config, "2+5'' \"\" \"\"", tokens);

        BOOST_CHECK_EQUAL(tokens.size(), 5u);

        BOOST_CHECK(tokens[0].type == token_type::number);
        BOOST_CHECK(tokens[0].value == "2");
        BOOST_CHECK(tokens[0].line == 1);
        BOOST_CHECK(tokens[0].col == 1);

        BOOST_CHECK(tokens[1].type == token_type::atom);
        BOOST_CHECK(tokens[1].value == "+5");
        BOOST_CHECK(tokens[1].line == 1);
        BOOST_CHECK(tokens[1].col == 2);

        BOOST_CHECK(tokens[2].type == token_type::string);
        BOOST_CHECK(tokens[2].value == "");
        BOOST_CHECK(tokens[2].line == 1);
        BOOST_CHECK(tokens[2].col == 4);

        BOOST_CHECK(tokens[3].type == token_type::string);
        BOOST_CHECK(tokens[3].value == "");
        BOOST_CHECK(tokens[3].line == 1);
        BOOST_CHECK(tokens[3].col == 7);

        BOOST_CHECK(tokens[4].type == token_type::string);
        BOOST_CHECK(tokens[4].value == "");
        BOOST_CHECK(tokens[4].line == 1);
        BOOST_CHECK(tokens[4].col == 10);
    }

    BOOST_AUTO_TEST_CASE(tokenize_formatted_characters) {
        tokenizer_config_t config = {{{"'", {"'"}}}, {{{"\"", {"\""}}}}, {}, {}, {{{"\\s", "\n"}}}, {{{"\n", "\\s"}}}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, false};
        tokens_t tokens;

        tokenize(config, "'\\s sdf\\sddsf\\\\n'", tokens);

        BOOST_CHECK_EQUAL(tokens.size(), 1u);

        BOOST_CHECK(tokens[0].type == token_type::string);
        BOOST_CHECK_EQUAL(tokens[0].value, "\n sdf\nddsf\\\\n");
        BOOST_CHECK(tokens[0].line == 1);
        BOOST_CHECK(tokens[0].col == 1);
    }

    BOOST_AUTO_TEST_CASE(tokenize_separated_symbols) {
        tokenizer_config_t config = {{}, {}, {{"+", "-", "*", "="}}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, false};
        tokens_t tokens;

        tokenize(config, "foo123+a\n2a+5-1*5", tokens);

        BOOST_CHECK_EQUAL(tokens.size(), 11u);

        BOOST_CHECK(tokens[0].type == token_type::atom);
        BOOST_CHECK(tokens[0].value == "foo123");
        BOOST_CHECK(tokens[0].line == 1);
        BOOST_CHECK(tokens[0].col == 1);

        BOOST_CHECK(tokens[1].type == token_type::atom);
        BOOST_CHECK(tokens[1].value == "+");
        BOOST_CHECK(tokens[1].line == 1);
        BOOST_CHECK(tokens[1].col == 7);

        BOOST_CHECK(tokens[2].type == token_type::atom);
        BOOST_CHECK(tokens[2].value == "a");
        BOOST_CHECK(tokens[2].line == 1);
        BOOST_CHECK(tokens[2].col == 8);

        BOOST_CHECK(tokens[3].type == token_type::number);
        BOOST_CHECK(tokens[3].value == "2");
        BOOST_CHECK(tokens[3].line == 2);
        BOOST_CHECK(tokens[3].col == 1);

        BOOST_CHECK(tokens[4].type == token_type::atom);
        BOOST_CHECK(tokens[4].value == "a");
        BOOST_CHECK(tokens[4].line == 2);
        BOOST_CHECK(tokens[4].col == 2);

        BOOST_CHECK(tokens[5].type == token_type::atom);
        BOOST_CHECK(tokens[5].value == "+");
        BOOST_CHECK(tokens[5].line == 2);
        BOOST_CHECK(tokens[5].col == 3);

        BOOST_CHECK(tokens[6].type == token_type::number);
        BOOST_CHECK(tokens[6].value == "5");
        BOOST_CHECK(tokens[6].line == 2);
        BOOST_CHECK(tokens[6].col == 4);

        BOOST_CHECK(tokens[7].type == token_type::atom);
        BOOST_CHECK(tokens[7].value == "-");
        BOOST_CHECK(tokens[7].line == 2);
        BOOST_CHECK(tokens[7].col == 5);

        BOOST_CHECK(tokens[8].type == token_type::number);
        BOOST_CHECK(tokens[8].value == "1");
        BOOST_CHECK(tokens[8].line == 2);
        BOOST_CHECK(tokens[8].col == 6);

        BOOST_CHECK(tokens[9].type == token_type::atom);
        BOOST_CHECK(tokens[9].value == "*");
        BOOST_CHECK(tokens[9].line == 2);
        BOOST_CHECK(tokens[9].col == 7);

        BOOST_CHECK(tokens[10].type == token_type::number);
        BOOST_CHECK(tokens[10].value == "5");
        BOOST_CHECK(tokens[10].line == 2);
        BOOST_CHECK(tokens[10].col == 8);
    }

    BOOST_AUTO_TEST_CASE(tokenize_separated_symbols_with_spaces) {
        tokenizer_config_t config = {{}, {}, {{"+", "-", "*", "="}}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, false};
        tokens_t tokens;

        tokenize(config, "foo123   +a\n  2a+\t5-1*5", tokens);

        BOOST_CHECK_EQUAL(tokens.size(), 11u);

        BOOST_CHECK(tokens[0].type == token_type::atom);
        BOOST_CHECK(tokens[0].value == "foo123");
        BOOST_CHECK(tokens[0].line == 1);
        BOOST_CHECK(tokens[0].col == 1);

        BOOST_CHECK(tokens[1].type == token_type::atom);
        BOOST_CHECK(tokens[1].value == "+");
        BOOST_CHECK(tokens[1].line == 1);
        BOOST_CHECK(tokens[1].col == 10);

        BOOST_CHECK(tokens[2].type == token_type::atom);
        BOOST_CHECK(tokens[2].value == "a");
        BOOST_CHECK(tokens[2].line == 1);
        BOOST_CHECK(tokens[2].col == 11);

        BOOST_CHECK(tokens[3].type == token_type::number);
        BOOST_CHECK(tokens[3].value == "2");
        BOOST_CHECK(tokens[3].line == 2);
        BOOST_CHECK(tokens[3].col == 3);

        BOOST_CHECK(tokens[4].type == token_type::atom);
        BOOST_CHECK(tokens[4].value == "a");
        BOOST_CHECK(tokens[4].line == 2);
        BOOST_CHECK(tokens[4].col == 4);

        BOOST_CHECK(tokens[5].type == token_type::atom);
        BOOST_CHECK(tokens[5].value == "+");
        BOOST_CHECK(tokens[5].line == 2);
        BOOST_CHECK(tokens[5].col == 5);

        BOOST_CHECK(tokens[6].type == token_type::number);
        BOOST_CHECK(tokens[6].value == "5");
        BOOST_CHECK(tokens[6].line == 2);
        BOOST_CHECK(tokens[6].col == 7);

        BOOST_CHECK(tokens[7].type == token_type::atom);
        BOOST_CHECK(tokens[7].value == "-");
        BOOST_CHECK(tokens[7].line == 2);
        BOOST_CHECK(tokens[7].col == 8);

        BOOST_CHECK(tokens[8].type == token_type::number);
        BOOST_CHECK(tokens[8].value == "1");
        BOOST_CHECK(tokens[8].line == 2);
        BOOST_CHECK(tokens[8].col == 9);

        BOOST_CHECK(tokens[9].type == token_type::atom);
        BOOST_CHECK(tokens[9].value == "*");
        BOOST_CHECK(tokens[9].line == 2);
        BOOST_CHECK(tokens[9].col == 10);

        BOOST_CHECK(tokens[10].type == token_type::number);
        BOOST_CHECK(tokens[10].value == "5");
        BOOST_CHECK(tokens[10].line == 2);
        BOOST_CHECK(tokens[10].col == 11);
    }

    BOOST_AUTO_TEST_CASE(tokenize_separated_symbols_which_consist_of_other_separated_symbols) {
        tokenizer_config_t config = {{}, {}, {{"+", "++", "="}}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, false};
        tokens_t tokens;

        tokenize(config, "foo bar++6", tokens);

        BOOST_CHECK(tokens[0].type == token_type::atom);
        BOOST_CHECK(tokens[0].value == "foo");
        BOOST_CHECK(tokens[0].line == 1);
        BOOST_CHECK(tokens[0].col == 1);

        BOOST_CHECK(tokens[1].type == token_type::atom);
        BOOST_CHECK(tokens[1].value == "bar");
        BOOST_CHECK(tokens[1].line == 1);
        BOOST_CHECK(tokens[1].col == 5);

        BOOST_CHECK(tokens[2].type == token_type::atom);
        BOOST_CHECK(tokens[2].value == "++");
        BOOST_CHECK(tokens[2].line == 1);
        BOOST_CHECK(tokens[2].col == 8);

        BOOST_CHECK(tokens[3].type == token_type::number);
        BOOST_CHECK(tokens[3].value == "6");
        BOOST_CHECK(tokens[3].line == 1);
        BOOST_CHECK(tokens[3].col == 10);
    }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(tokenizer_parameters)

    BOOST_AUTO_TEST_CASE(case1) {
        tokenizer_config_t config = {{}, {}, {}, {}, {}, {}, {{"0if"}}, {{"0elif"}}, {{"0else"}}, {{"0eq"}}, {{"0s"}}, {{"0e"}}, {{"0set"}}, {{"0get"}}, {{"0ps", {"0"}}}, {{"0pf", {"0"}}}, {{"0p", {"0"}}}, false};
        tokens_t tokens;

        tokenize(config, "0if 0p_just_some_argument0 0ps_args0 0pf_func0", tokens);

        BOOST_CHECK(tokens[0].type == token_type::macro_if);
        BOOST_CHECK_EQUAL(tokens[0].value, "0if");
        BOOST_CHECK_EQUAL(tokens[0].line, 1);
        BOOST_CHECK_EQUAL(tokens[0].col, 1);

        BOOST_CHECK(tokens[1].type == token_type::macro_p);
        BOOST_CHECK_EQUAL(tokens[1].value, "_just_some_argument");
        BOOST_CHECK_EQUAL(tokens[1].line, 1);
        BOOST_CHECK_EQUAL(tokens[1].col, 5);

        BOOST_CHECK(tokens[2].type == token_type::macro_ps);
        BOOST_CHECK_EQUAL(tokens[2].value, "_args");
        BOOST_CHECK_EQUAL(tokens[2].line, 1);
        BOOST_CHECK_EQUAL(tokens[2].col, 28);

        BOOST_CHECK(tokens[3].type == token_type::macro_pf);
        BOOST_CHECK_EQUAL(tokens[3].value, "_func");
        BOOST_CHECK_EQUAL(tokens[3].line, 1);
        BOOST_CHECK_EQUAL(tokens[3].col, 38);
    }

    BOOST_AUTO_TEST_CASE(case2) {
        tokenizer_config_t config = {{}, {}, {}, {}, {}, {}, {{"0if"}}, {{"0elif"}}, {{"0else"}}, {{"0eq"}}, {{"0s"}}, {{"0e"}}, {{"0set"}}, {{"0get"}}, {{"0ps", {"0"}}}, {{"0pf", {"0pf"}}}, {{"0p", {"0"}}}, false};
        tokens_t tokens;

        tokenize(config, "0p_left0 + 0p_right0 - 1", tokens);

        BOOST_CHECK(tokens[0].type == token_type::macro_p);
        BOOST_CHECK_EQUAL(tokens[0].value, "_left");
        BOOST_CHECK_EQUAL(tokens[0].line, 1);
        BOOST_CHECK_EQUAL(tokens[0].col, 1);

        BOOST_CHECK(tokens[1].type == token_type::atom);
        BOOST_CHECK_EQUAL(tokens[1].value, "+");
        BOOST_CHECK_EQUAL(tokens[1].line, 1);
        BOOST_CHECK_EQUAL(tokens[1].col, 10);

        BOOST_CHECK(tokens[2].type == token_type::macro_p);
        BOOST_CHECK_EQUAL(tokens[2].value, "_right");
        BOOST_CHECK_EQUAL(tokens[2].line, 1);
        BOOST_CHECK_EQUAL(tokens[2].col, 12);

        BOOST_CHECK(tokens[3].type == token_type::atom);
        BOOST_CHECK_EQUAL(tokens[3].value, "-");
        BOOST_CHECK_EQUAL(tokens[3].line, 1);
        BOOST_CHECK_EQUAL(tokens[3].col, 22);

        BOOST_CHECK(tokens[4].type == token_type::number);
        BOOST_CHECK_EQUAL(tokens[4].value, "1");
        BOOST_CHECK_EQUAL(tokens[4].line, 1);
        BOOST_CHECK_EQUAL(tokens[4].col, 24);
    }

    BOOST_AUTO_TEST_CASE(case3) {
        tokenizer_config_t config = {{}, {}, {}, {}, {}, {}, {{"0if"}}, {{"0elif"}}, {{"0else"}}, {{"0eq"}}, {{"0s"}}, {{"0e"}}, {{"0set"}}, {{"0get"}}, {{"0ps", {"0"}}}, {{"0pf", {"0pf"}}}, {{"0p", {"0"}}}, false};
        tokens_t tokens;

        tokenize(config, "0p_just_some_argument0foo0ps_args0", tokens);

        BOOST_CHECK(tokens[0].type == token_type::macro_p);
        BOOST_CHECK_EQUAL(tokens[0].value, "_just_some_argument");
        BOOST_CHECK_EQUAL(tokens[0].line, 1);
        BOOST_CHECK_EQUAL(tokens[0].col, 1);

        BOOST_CHECK(tokens[1].type == token_type::atom);
        BOOST_CHECK_EQUAL(tokens[1].value, "foo");
        BOOST_CHECK_EQUAL(tokens[1].line, 1);
        BOOST_CHECK_EQUAL(tokens[1].col, 23);

        BOOST_CHECK(tokens[2].type == token_type::macro_ps);
        BOOST_CHECK_EQUAL(tokens[2].value, "_args");
        BOOST_CHECK_EQUAL(tokens[2].line, 1);
        BOOST_CHECK_EQUAL(tokens[2].col, 26);
    }

BOOST_AUTO_TEST_SUITE_END()