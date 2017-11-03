#include <string>
#include <iostream>
#include <unordered_map>
#include <vector>

#include "test.hpp"
#include "parser.hpp"
#include "call_tree.hpp"
#include "context.hpp"
#include "test_function_priority.hpp"

using namespace cuttle;

inline void test_parses_basic_function_call() {
    context_t context;

    context.funcs.insert({"foo", function_t {PREFIX_FUNCTION, 3}});
    context.funcs.insert({"bar", function_t {INFIX_FUNCTION, 2}});
    context.funcs.insert({"baz", function_t {PREFIX_FUNCTION, 2}});
    context.funcs.insert({"quxx", function_t {POSTFIX_FUNCTION, 1}});

    {
        call_tree_t tree;
        std::vector<token_t> tokens = {
            token_t {ATOM_TOKEN, "foo", 1, 1},
            token_t {NUMBER_TOKEN, "1", 1, 5},
            token_t {NUMBER_TOKEN, "2", 1, 7},
            token_t {NUMBER_TOKEN, "3", 1, 9}
        };
        parse(tokens, tree, context);
		AssertEqual(tree.src, (tree_src_t{ { 1, 2, 3 }, {}, {}, {} }), "Tree src");
    }
    //{
    //    call_tree_t tree;
    //    std::vector<token_t> tokens = {
    //        token_t {NUMBER_TOKEN, "1", 1, 1},
    //        token_t {ATOM_TOKEN, "bar", 1, 3},
    //        token_t {NUMBER_TOKEN, "2", 1, 7},
    //    };
    //    parse(tokens, tree, context);
    //    AssertTrue(tree.src.size() == 1, "Tree src size");        
    //    AssertTrue(tree.src[0][0] == 1, "Function token number");
    //    AssertTrue(tree.src[0][1] == 0, "Argument 1 token number");
    //    AssertTrue(tree.src[0][2] == 2, "Argument 2 token number");
    //}
	{
		call_tree_t tree;
		std::vector<token_t> tokens = {
			token_t {ATOM_TOKEN, "baz", 1, 1},
			token_t {NUMBER_TOKEN, "1", 1, 5},
			token_t {NUMBER_TOKEN, "2", 1, 7},
		};
		parse(tokens, tree, context);
		AssertEqual(tree.src, (tree_src_t{ {1, 2}, {}, {} }), "Tree src");
    }
	// TODO: POSTFIX
}

void run_function_priority_tests() {
    TESTCASE
    test_priority_push_basic();
}