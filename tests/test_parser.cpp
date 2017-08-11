#include <string>
#include <iostream>
#include <unordered_map>
#include <vector>

#include "test.hpp"
#include "parser.hpp"
#include "call_tree.hpp"
#include "context.hpp"

using namespace husky;

inline void test_parses_basic_function_call() {
    context_t context;

    context.funcs.insert({"foo", (function_t) {PREFIX_FUNCTION, 3}});
    context.funcs.insert({"bar", (function_t) {INFIX_FUNCTION, 2}});
    context.funcs.insert({"baz", (function_t) {PREFIX_FUNCTION, 2}});
    context.funcs.insert({"quxx", (function_t) {POSTFIX_FUNCTION, 1}});

    {
        call_tree_t tree;
        std::vector<token_t *> tokens = {
            new token_t {ATOM_TOKEN, "foo", 1, 1},
            new token_t {NUMBER_TOKEN, "1", 1, 5},
            new token_t {NUMBER_TOKEN, "2", 1, 7},
            new token_t {NUMBER_TOKEN, "3", 1, 9}
        };
        parse(tokens, tree, context);
        AssertTrue(tree.src.length() == 1, "Tree src length");        
        AssertTrue(tree.src[0][0] == 0, "Function token number");
        AssertTrue(tree.src[0][1] == 1, "Argument 1 token number");
        AssertTrue(tree.src[0][2] == 2, "Argument 2 token number");
        AssertTrue(tree.src[0][3] == 3, "Argument 3 token number");
    }
    {
        call_tree_t tree;        
        std::vector<token_t *> tokens = {
            new token_t {NUMBER_TOKEN, "1", 1, 1},
            new token_t {ATOM_TOKEN, "bar", 1, 3},
            new token_t {NUMBER_TOKEN, "2", 1, 7},
        };
        parse(tokens, tree, context);
        AssertTrue(tree.src.length() == 1, "Tree src length");        
        AssertTrue(tree.src[0][0] == 1, "Function token number");
        AssertTrue(tree.src[0][1] == 0, "Argument 1 token number");
        AssertTrue(tree.src[0][2] == 2, "Argument 2 token number");
    }
    {
        call_tree_t tree;        
        std::vector<token_t *> tokens = {
            new token_t {ATOM_TOKEN, "baz", 1, 1},
            new token_t {NUMBER_TOKEN, "1", 1, 5},
            new token_t {NUMBER_TOKEN, "2", 1, 7},
        };
        parse(tokens, tree, context);
        AssertTrue(tree.src.length() == 1, "Tree src length");        
        AssertTrue(tree.src[0][0] == 0, "Function token number");
        AssertTrue(tree.src[0][1] == 1, "Argument 1 token number");
        AssertTrue(tree.src[0][2] == 2, "Argument 2 token number");
    }
    {
        call_tree_t tree;        
        std::vector<token_t *> tokens = {
            new token_t {ATOM_TOKEN, "baz", 1, 1},
            new token_t {NUMBER_TOKEN, "1", 1, 5},
            new token_t {NUMBER_TOKEN, "2", 1, 7},
        };
        parse(tokens, tree, context);
        AssertTrue(tree.src.length() == 1, "Tree src length");        
        AssertTrue(tree.src[0][0] == 0, "Function token number");
        AssertTrue(tree.src[0][1] == 1, "Argument 1 token number");
        AssertTrue(tree.src[0][2] == 2, "Argument 2 token number");
    }
}

void run_parser_tests() {
    TESTCASE
    test_parses_basic_function_call();
}