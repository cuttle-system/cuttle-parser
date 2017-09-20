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
		AssertEqual(tree.src, (tree_src_type{ { 1, 2, 3 }, {}, {}, {} }), "Tree src");
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
		AssertEqual(tree.src, (tree_src_type { {1, 2}, {}, {} }), "Tree src");
    }
	// TODO: POSTFIX
}

inline void test_parses_nested_function_calls_of_one_type() {
	context_t context;

	context.funcs.insert({ "foo", function_t{ PREFIX_FUNCTION, 3 } });
	context.funcs.insert({ "bar", function_t{ INFIX_FUNCTION, 2 } });
	context.funcs.insert({ "baz", function_t{ PREFIX_FUNCTION, 2 } });
	context.funcs.insert({ "quxx", function_t{ POSTFIX_FUNCTION, 1 } });

	{
		call_tree_t tree;
		std::vector<token_t> tokens = {
			token_t{ ATOM_TOKEN, "foo", 1, 1 },
			token_t{ ATOM_TOKEN, "foo", 1, 5 },
			token_t{ NUMBER_TOKEN, "1", 1, 10 },
			token_t{ NUMBER_TOKEN, "2", 1, 12 },
			token_t{ NUMBER_TOKEN, "3", 1, 14 },
			token_t{ ATOM_TOKEN, "baz", 1, 16 },
			token_t{ NUMBER_TOKEN, "1", 1, 21 },
			token_t{ NUMBER_TOKEN, "2", 1, 23 },
			token_t{ ATOM_TOKEN, "foo", 1, 25 },
			token_t{ NUMBER_TOKEN, "1", 1, 30 },
			token_t{ NUMBER_TOKEN, "2", 1, 32 },
			token_t{ NUMBER_TOKEN, "3", 1, 34 }
		};
		parse(tokens, tree, context);
		AssertEqual(tree.src, (tree_src_type {
			{ 1, 5, 8 },
				{ 2, 3, 4 }, {}, {}, {},
				{ 6, 7 }, {}, {},
				{ 9, 10, 11 }, {}, {}, {}
		}), "Tree src");
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
	// TODO: POSTFIX
}

void run_parser_tests() {
    TESTCASE
    test_parses_basic_function_call();
	test_parses_nested_function_calls_of_one_type();
}