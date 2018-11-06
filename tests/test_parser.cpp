#define BOOST_TEST_DYN_LINK

#include <iostream>
#include <boost/test/unit_test.hpp>
#include <string>
#include <iostream>
#include <unordered_map>
#include <vector>

#include "parser.hpp"
#include "parse_error.hpp"
#include "context_methods.hpp"

using namespace cuttle;


struct parses_basic_function_call_suite_fixture {
    context_t context;

    void setup() {
        initialize(context);

        add(context, "foo", function_t{ function_type::prefix, 3 }, FUNCTION_ID_UNKNOWN);
        add(context, "bar", function_t{ function_type::infix, 2 }, 3);
        add(context, "baz", function_t{ function_type::prefix, 2 }, 4);
        add(context, "quxx", function_t{ function_type::postfix, 1 }, 5);
    }
};

BOOST_FIXTURE_TEST_SUITE(parses_basic_function_call_suite, parses_basic_function_call_suite_fixture)

    BOOST_AUTO_TEST_CASE(case1) {
        call_tree_t tree;
        std::vector<token_t> tokens = {
            token_t {token_type::atom, "foo", 1, 1},
            token_t {token_type::number, "1", 1, 5},
            token_t {token_type::number, "2", 1, 7},
            token_t {token_type::number, "3", 1, 9}
        };
        parse(tokens, tree, context);
		BOOST_CHECK(tree.src == (tree_src_t{ { 1, 2, 3 }, {}, {}, {}, {0} }));
    }

    BOOST_AUTO_TEST_CASE(case2) {
        call_tree_t tree;
        std::vector<token_t> tokens = {
            token_t {token_type::number, "1", 1, 1},
            token_t {token_type::atom, "bar", 1, 3},
            token_t {token_type::number, "2", 1, 7},
        };
		parse(tokens, tree, context);
		BOOST_CHECK(tree.src == (tree_src_t{
			{},{0, 2},{},
			{ 1 }
		}));
    }

    BOOST_AUTO_TEST_CASE(case3) {
        call_tree_t tree;
		std::vector<token_t> tokens = {
			token_t {token_type::atom, "baz", 1, 1},
			token_t {token_type::number, "1", 1, 5},
			token_t {token_type::number, "2", 1, 7},
		};
		parse(tokens, tree, context);
        BOOST_CHECK(tree.src == (tree_src_t{ {1, 2}, {}, {}, {0} }));
    }

    BOOST_AUTO_TEST_CASE(case4) {
        call_tree_t tree;
		std::vector<token_t> tokens = {
			token_t{ token_type::number, "1", 1, 1 },
			token_t{ token_type::atom, "quxx", 1, 3 },
		};
		parse(tokens, tree, context);
        BOOST_CHECK(tree.src == (tree_src_t{
			{},{ 0 },
			{1}
		}));
	}

BOOST_AUTO_TEST_SUITE_END()

struct parses_nested_function_calls_of_one_type_suite_fixture {
    context_t context;

    void setup() {
        initialize(context);

        add(context, "foo", function_t{ function_type::prefix, 3 }, FUNCTION_ID_UNKNOWN);
        add(context, "bar", function_t{ function_type::infix, 2 }, 3);
        add(context, "baz", function_t{ function_type::prefix, 2 }, 4);
        add(context, "+", function_t{ function_type::infix, 2 }, 5);
        add(context, "quxx", function_t{ function_type::postfix, 1 }, 6);
    }
};

BOOST_FIXTURE_TEST_SUITE(parses_nested_function_calls_of_one_type_suite, parses_nested_function_calls_of_one_type_suite_fixture)

    BOOST_AUTO_TEST_CASE(case1) {
		call_tree_t tree;
		std::vector<token_t> tokens = {
			token_t{ token_type::atom, "foo", 1, 1 },
			token_t{ token_type::atom, "foo", 1, 5 },
			token_t{ token_type::number, "1", 1, 10 },
			token_t{ token_type::number, "2", 1, 12 },
			token_t{ token_type::number, "3", 1, 14 },
			token_t{ token_type::atom, "baz", 1, 16 },
			token_t{ token_type::number, "1", 1, 21 },
			token_t{ token_type::number, "2", 1, 23 },
			token_t{ token_type::atom, "foo", 1, 25 },
			token_t{ token_type::number, "1", 1, 30 },
			token_t{ token_type::number, "2", 1, 32 },
			token_t{ token_type::number, "3", 1, 34 }
		};
		parse(tokens, tree, context);
		BOOST_CHECK(tree.src == (tree_src_t{
			{ 1, 5, 8 },
				{ 2, 3, 4 }, {}, {}, {},
				{ 6, 7 }, {}, {},
				{ 9, 10, 11 }, {}, {}, {},
				{0}
		}));
	}

    BOOST_AUTO_TEST_CASE(case2) {
	    call_tree_t tree;
	    std::vector<token_t> tokens = {
	        token_t {token_type::number, "1", 1, 1},
	        token_t {token_type::atom, "bar", 1, 3},
	        token_t {token_type::number, "2", 1, 7},
			token_t{ token_type::atom, "+", 1, 7 },
			token_t{ token_type::number, "3", 1, 7 },
	    };
	    parse(tokens, tree, context);
		BOOST_CHECK(tree.src == (tree_src_t{
			{},{ 0, 3 },
			{},{2, 4},{},
			{ 1 }
		}));
	}

    BOOST_AUTO_TEST_CASE(case3) {
		call_tree_t tree;
		std::vector<token_t> tokens = {
			token_t{ token_type::number, "1", 1, 1 },
			token_t{ token_type::atom, "quxx", 1, 3 },
			token_t{ token_type::atom, "quxx", 1, 7 },
		};
		parse(tokens, tree, context);
		BOOST_CHECK(tree.src == (tree_src_t{
			{},{ 0 },
			{ 1 },
			{2}
		}));
	}

BOOST_AUTO_TEST_SUITE_END()

struct parses_nested_function_calls_with_different_priorities_suite_fixture {
    context_t context;

    void setup() {
        initialize(context);

        add(context, "foo", function_t{ function_type::prefix, 3 }, FUNCTION_ID_UNKNOWN);
        add(context, "bar", function_t{ function_type::infix, 2 }, 3);
        add(context, "baz", function_t{ function_type::prefix, 2 }, 4);
        add(context, "quxx", function_t{ function_type::postfix, 1 }, 5);
    }
};

BOOST_FIXTURE_TEST_SUITE(parses_nested_function_calls_with_different_priorities_suite, parses_nested_function_calls_with_different_priorities_suite_fixture)

    BOOST_AUTO_TEST_CASE(case1) {
		call_tree_t tree;
		std::vector<token_t> tokens = {
			token_t{ token_type::atom, "foo", 1, 1 },
			token_t{ token_type::number, "1", 1, 10 },
			token_t{ token_type::atom, "quxx", 1, 5 },
			token_t{ token_type::number, "2", 1, 12 },
			token_t{ token_type::atom, "baz", 1, 16 },
			token_t{ token_type::number, "1", 1, 21 },
			token_t{ token_type::number, "2", 1, 23 }
		};
		parse(tokens, tree, context);
		BOOST_CHECK(tree.src == (tree_src_t{
			{ 2, 3, 4 },{},
			{ 1 },{},
			{ 5, 6 },{},{},
			{0}
		}));
	}

BOOST_AUTO_TEST_SUITE_END()

struct parses_nested_function_calls_where_first_function_call_is_not_in_the_start_suite_fixture {
    context_t context;

    void setup() {
        initialize(context);

        add(context, "quxx", function_t{ function_type::postfix, 1 }, FUNCTION_ID_UNKNOWN);
        add(context, "bar", function_t{ function_type::infix, 2 }, 3);
        add(context, "baz", function_t{ function_type::prefix, 2 }, 4);
        add(context, "foo", function_t{ function_type::prefix, 3 }, 5);
    }
};

BOOST_FIXTURE_TEST_SUITE(parses_nested_function_calls_where_first_function_call_is_not_in_the_start_suite,
        parses_nested_function_calls_where_first_function_call_is_not_in_the_start_suite_fixture)

    BOOST_AUTO_TEST_CASE(case1) {
		call_tree_t tree;
		std::vector<token_t> tokens = {
			token_t{ token_type::atom, "foo", 1, 1 },
			token_t{ token_type::number, "2", 1, 12 },
			token_t{ token_type::atom, "baz", 1, 16 },
			token_t{ token_type::number, "1", 1, 21 },
			token_t{ token_type::number, "2", 1, 23 },
			token_t{ token_type::number, "1", 1, 10 },
			token_t{ token_type::atom, "quxx", 1, 5 },
			token_t{ token_type::atom, "quxx", 1, 12 }
		};
		parse(tokens, tree, context);
		BOOST_CHECK(tree.src == (tree_src_t{
			{ 1, 2, 5 },{},
			{ 3, 4 },{},{},{},
			{ 0 },
			{ 6 },
			{7}
		}));
	}

BOOST_AUTO_TEST_SUITE_END()

struct parses_nested_function_calls_with_priorities_and_multiple_parents_suite_fixture {
    context_t context;

    void setup() {
        initialize(context);

        add(context, "!", function_t{ function_type::postfix, 1 }, FUNCTION_ID_UNKNOWN);
        add(context, "-", function_t{ function_type::infix, 2 }, 3);
        add(context, "+", function_t{ function_type::infix, 2 }, 4);
        add(context, "*", function_t{ function_type::infix, 2 }, 5);
    }
};

BOOST_FIXTURE_TEST_SUITE(parses_nested_function_calls_with_priorities_and_multiple_parents_suite,
                         parses_nested_function_calls_with_priorities_and_multiple_parents_suite_fixture)

    BOOST_AUTO_TEST_CASE(case1) {
		call_tree_t tree;
		std::vector<token_t> tokens = {
			token_t{ token_type::number, "1", 0, 0 },
			token_t{ token_type::atom, "-", 0, 0 },
			token_t{ token_type::number, "2", 0, 0 },
			token_t{ token_type::atom, "+", 0, 0 },
			token_t{ token_type::number, "3", 0, 0 },
			token_t{ token_type::atom, "!", 0, 0},
		};
		parse(tokens, tree, context);
		BOOST_CHECK(tree.src == (tree_src_t{
			{},{0, 3},
			{},{2, 4},{},
			{1},
			{5}
		}));
	}

    BOOST_AUTO_TEST_CASE(case2) {
		call_tree_t tree;
		std::vector<token_t> tokens = {
			token_t{ token_type::number, "1", 0, 0 },
			token_t{ token_type::atom, "-", 0, 0 },
			token_t{ token_type::number, "2", 0, 0 },
			token_t{ token_type::atom, "+", 0, 0 },
			token_t{ token_type::number, "3", 0, 0 },
			token_t{ token_type::atom, "*", 0, 0 },
			token_t{ token_type::number, "4", 0, 0 },
			token_t{ token_type::atom, "!", 0, 0 },
		};
		parse(tokens, tree, context);
		BOOST_CHECK(tree.src == (tree_src_t{
			{},{ 0, 3 },
			{},{ 2, 5 },
			{},{ 4, 6 },{},
			{ 1 },
			{ 7 }
		}));
	}

BOOST_AUTO_TEST_SUITE_END()

struct parser_throws_errors_suite_fixture {
    context_t context;

    void setup() {
        initialize(context);

        add(context, "foo", function_t{ function_type::prefix, 2 }, FUNCTION_ID_UNKNOWN);
    }
};

BOOST_FIXTURE_TEST_SUITE(parser_throws_errors_suite,
                         parser_throws_errors_suite_fixture)

    BOOST_AUTO_TEST_CASE(case1) {
        call_tree_t tree;
        std::vector<token_t> tokens = {
                token_t{ token_type::atom, "foo", 0, 0 },
                token_t{ token_type::number, "2", 0, 0 },
        };

        BOOST_CHECK_THROW(do {
            parse(tokens, tree, context);
        } while (0), parse_error);
    }

BOOST_AUTO_TEST_SUITE_END()

struct parses_function_calls_with_any_function_name_suite_fixture {
	context_t context;

	void setup() {
		initialize(context);

		add(context, "*", function_t{ function_type::infix, 2 }, FUNCTION_ID_UNKNOWN);
		add(context, "+", function_t{ function_type::infix, 2 }, 3);
	}
};

BOOST_FIXTURE_TEST_SUITE(parses_function_calls_with_any_function_name_suite,
						 parses_function_calls_with_any_function_name_suite_fixture)

	BOOST_AUTO_TEST_CASE(case1) {
		call_tree_t tree;
		std::vector<token_t> tokens = {
				token_t{ token_type::atom, "foo", 0, 0 },
				token_t{ token_type::atom, "+", 0, 0 },
				token_t{ token_type::number, "2", 0, 0 },
				token_t{ token_type::atom, "*", 0, 0 },
				token_t{ token_type::number, "3", 0, 0 },
		};
		parse(tokens, tree, context);
		BOOST_CHECK(tree.src == (tree_src_t{
				{},{0, 2}, {},
				{1, 4},{},
				{3}
		}));
	}

BOOST_AUTO_TEST_SUITE_END()

struct parses_postprefix_functions_suite_fixture {
    context_t context;

    void setup() {
        initialize(context);

        add(context, "(", function_t{ function_type::postprefix }, FUNCTION_ID_UNKNOWN, ")");
        add(context, "+", function_t{ function_type::infix, 2 }, 3);
    }
};

BOOST_FIXTURE_TEST_SUITE(parses_postprefix_functions_suite,
                         parses_postprefix_functions_suite_fixture)

    BOOST_AUTO_TEST_CASE(case1) {
        call_tree_t tree;
        std::vector<token_t> tokens = {
                token_t{ token_type::atom, "foo", 0, 0 },
                token_t{ token_type::atom, "(", 0, 0 },
                token_t{ token_type::number, "2", 0, 0 },
                token_t{ token_type::atom, ")", 0, 0 },
        };
        parse(tokens, tree, context);
        BOOST_CHECK(tree.src == (tree_src_t{
                {},{2, 3}, {}, {}, {0, 1}
        }));
    }

    BOOST_AUTO_TEST_CASE(case2) {
        call_tree_t tree;
        std::vector<token_t> tokens = {
                token_t{ token_type::atom, "(", 0, 0 },
                token_t{ token_type::number, "2", 0, 0 },
                token_t{ token_type::atom, ")", 0, 0 },
        };
        parse(tokens, tree, context);
        BOOST_CHECK(tree.src == (tree_src_t{
                {1, 2}, {}, {}, {0}
        }));
    }

    BOOST_AUTO_TEST_CASE(case3) {
        call_tree_t tree;
        std::vector<token_t> tokens = {
                token_t{ token_type::atom, "(", 0, 0 },
                token_t{ token_type::atom, ")", 0, 0 },
        };
        parse(tokens, tree, context);
        BOOST_CHECK(tree.src == (tree_src_t{
                {1}, {}, {0}
        }));
    }

    BOOST_AUTO_TEST_CASE(case4) {
        call_tree_t tree;
        std::vector<token_t> tokens = {
                token_t{ token_type::atom, "(", 0, 0 },
                token_t{ token_type::atom, "(", 0, 0 },
                token_t{ token_type::atom, ")", 0, 0 },
                token_t{ token_type::atom, ")", 0, 0 },
        };
        parse(tokens, tree, context);
        BOOST_CHECK(tree.src == (tree_src_t{
                {1, 3}, {2}, {}, {}, {0}
        }));
    }

    BOOST_AUTO_TEST_CASE(case5) {
        call_tree_t tree;
        std::vector<token_t> tokens = {
                token_t{ token_type::atom, "(", 0, 0 },
                token_t{ token_type::atom, "(", 0, 0 },
                token_t{ token_type::number, "2", 0, 0 },
                token_t{ token_type::atom, ")", 0, 0 },
                token_t{ token_type::atom, ")", 0, 0 },
        };
        parse(tokens, tree, context);
        BOOST_CHECK(tree.src == (tree_src_t{
                {1, 4}, {2, 3}, {}, {}, {}, {0}
        }));
    }

    BOOST_AUTO_TEST_CASE(case6) {
        call_tree_t tree;
        std::vector<token_t> tokens = {
                token_t{ token_type::atom, "(", 0, 0 },
                token_t{ token_type::atom, "(", 0, 0 },
                token_t{ token_type::atom, ")", 0, 0 },
                token_t{ token_type::atom, "(", 0, 0 },
                token_t{ token_type::atom, ")", 0, 0 },
                token_t{ token_type::atom, ")", 0, 0 },
        };
        parse(tokens, tree, context);
        BOOST_CHECK(tree.src == (tree_src_t{
                {1, 3, 5}, {2}, {}, {4}, {}, {}, {0}
        }));
    }

BOOST_AUTO_TEST_SUITE_END()