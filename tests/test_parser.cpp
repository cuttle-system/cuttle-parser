#include <string>
#include <iostream>
#include <unordered_map>
#include <vector>

#include "test.hpp"
#include "parser.hpp"
#include "call_tree.hpp"
#include "context.hpp"

using namespace cuttle;

inline void test_parses_basic_function_call() {
    context_t context;

	initialize(context);

	add(context, "foo", function_t{ PREFIX_FUNCTION, 3 }, FUNCTION_ID_UNKNOWN);
	add(context, "bar", function_t{ INFIX_FUNCTION, 2 }, 2);
	add(context, "baz", function_t{ PREFIX_FUNCTION, 2 }, 3);
	add(context, "quxx", function_t{ POSTFIX_FUNCTION, 1 }, 4);

    {
        call_tree_t tree;
        std::vector<token_t> tokens = {
            token_t {ATOM_TOKEN, "foo", 1, 1},
            token_t {NUMBER_TOKEN, "1", 1, 5},
            token_t {NUMBER_TOKEN, "2", 1, 7},
            token_t {NUMBER_TOKEN, "3", 1, 9}
        };
        parse(tokens, tree, context);
		AssertEqual(tree.src, (tree_src_t{ { 1, 2, 3 }, {}, {}, {}, {0} }), "Tree src");
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
		AssertEqual(tree.src, (tree_src_t{ {1, 2}, {}, {}, {0} }), "Tree src");
    }
	{
		call_tree_t tree;
		std::vector<token_t> tokens = {
			token_t{ NUMBER_TOKEN, "1", 1, 1 },
			token_t{ ATOM_TOKEN, "quxx", 1, 3 },
		};
		parse(tokens, tree, context);
		AssertEqual(tree.src, (tree_src_t{
			{},{ 0 },
			{1}
		}), "Tree src");
	}
}

inline void test_parses_nested_function_calls_of_one_type() {
	context_t context;
	
	initialize(context);

	add(context, "foo", function_t{ PREFIX_FUNCTION, 3 }, FUNCTION_ID_UNKNOWN);
	add(context, "bar", function_t{ INFIX_FUNCTION, 2 }, 2);
	add(context, "baz", function_t{ PREFIX_FUNCTION, 2 }, 3);
	add(context, "quxx", function_t{ POSTFIX_FUNCTION, 1 }, 4);

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
		AssertEqual(tree.src, (tree_src_t{
			{ 1, 5, 8 },
				{ 2, 3, 4 }, {}, {}, {},
				{ 6, 7 }, {}, {},
				{ 9, 10, 11 }, {}, {}, {},
				{0}
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
	{
		call_tree_t tree;
		std::vector<token_t> tokens = {
			token_t{ NUMBER_TOKEN, "1", 1, 1 },
			token_t{ ATOM_TOKEN, "quxx", 1, 3 },
			token_t{ ATOM_TOKEN, "quxx", 1, 7 },
		};
		parse(tokens, tree, context);
		AssertEqual(tree.src, (tree_src_t{
			{},{ 0 },
			{ 1 },
			{2}
		}), "Tree src");
	}
}

inline void test_parses_nested_function_calls_with_different_priorities() {
	context_t context;

	initialize(context);

	add(context, "foo", function_t{ PREFIX_FUNCTION, 3 }, FUNCTION_ID_UNKNOWN);
	add(context, "bar", function_t{ INFIX_FUNCTION, 2 }, 2);
	add(context, "baz", function_t{ PREFIX_FUNCTION, 2 }, 3);
	add(context, "quxx", function_t{ POSTFIX_FUNCTION, 1 }, 4);

	{
		call_tree_t tree;
		std::vector<token_t> tokens = {
			token_t{ ATOM_TOKEN, "foo", 1, 1 },
			token_t{ NUMBER_TOKEN, "1", 1, 10 },
			token_t{ ATOM_TOKEN, "quxx", 1, 5 },
			token_t{ NUMBER_TOKEN, "2", 1, 12 },
			token_t{ ATOM_TOKEN, "baz", 1, 16 },
			token_t{ NUMBER_TOKEN, "1", 1, 21 },
			token_t{ NUMBER_TOKEN, "2", 1, 23 }
		};
		parse(tokens, tree, context);
		AssertEqual(tree.src, (tree_src_t{
			{ 2, 3, 4 },{},
			{ 1 },{},
			{ 5, 6 },{},{},
			{0}
		}), "Tree src");
	}
}

inline void test_parses_nested_function_calls_where_first_function_call_is_not_in_the_start() {
	context_t context;

	initialize(context);

	add(context, "quxx", function_t{ POSTFIX_FUNCTION, 1 }, FUNCTION_ID_UNKNOWN);
	add(context, "bar", function_t{ INFIX_FUNCTION, 2 }, 2);
	add(context, "baz", function_t{ PREFIX_FUNCTION, 2 }, 3);
	add(context, "foo", function_t{ PREFIX_FUNCTION, 3 }, 4);

	{
		call_tree_t tree;
		std::vector<token_t> tokens = {
			token_t{ ATOM_TOKEN, "foo", 1, 1 },
			token_t{ NUMBER_TOKEN, "2", 1, 12 },
			token_t{ ATOM_TOKEN, "baz", 1, 16 },
			token_t{ NUMBER_TOKEN, "1", 1, 21 },
			token_t{ NUMBER_TOKEN, "2", 1, 23 },
			token_t{ NUMBER_TOKEN, "1", 1, 10 },
			token_t{ ATOM_TOKEN, "quxx", 1, 5 },
			token_t{ ATOM_TOKEN, "quxx", 1, 12 }
		};
		parse(tokens, tree, context);
		AssertEqual(tree.src, (tree_src_t{
			{ 1, 2, 5 },{},
			{ 3, 4 },{},{},{},
			{ 0 },
			{ 6 },
			{7}
		}), "Tree src");
	}
}

void run_parser_tests() {
    TESTCASE
    test_parses_basic_function_call();
	test_parses_nested_function_calls_of_one_type();
	test_parses_nested_function_calls_with_different_priorities();
	test_parses_nested_function_calls_where_first_function_call_is_not_in_the_start();
}