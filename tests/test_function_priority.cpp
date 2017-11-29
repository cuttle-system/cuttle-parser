#include <string>
#include <iostream>
#include <unordered_map>
#include <vector>

#include "test.hpp"
#include "test_function_priority.hpp"
#include "function_priority.hpp"

using namespace cuttle;

inline void test_priority_initialize() {
	{
		function_priority_table_t func_priors;
		initialize(func_priors);
		AssertEqual(func_priors.priors, (function_priorities_t {
			{ FUNCTION_ID_ERROR, FUNCTION_PRIORITY_UNKNOWN, FUNCTION_ID_LAST }, 
			{ FUNCTION_ID_UNKNOWN, FUNCTION_PRIORITY_LAST, FUNCTION_ID_ERROR }
		}), "Function priorities");
	}
	{
		function_priority_table_t func_priors;
		initialize(func_priors);
		initialize(func_priors);
		AssertEqual(func_priors.priors, (function_priorities_t{
			{ FUNCTION_ID_ERROR, FUNCTION_PRIORITY_UNKNOWN, FUNCTION_ID_LAST },
			{ FUNCTION_ID_UNKNOWN, FUNCTION_PRIORITY_LAST, FUNCTION_ID_ERROR }
		}), "Function priorities");
	}
}

inline void test_priority_push_basic() {
	{
		function_priority_table_t func_priors;
		initialize(func_priors);
		add(func_priors, 2, FUNCTION_ID_UNKNOWN);
		AssertEqual(func_priors.priors, (function_priorities_t {
			{ FUNCTION_ID_ERROR, FUNCTION_PRIORITY_UNKNOWN, 2 },
			{ 2, FUNCTION_PRIORITY_LAST, FUNCTION_ID_ERROR },
			{ FUNCTION_ID_UNKNOWN, 2, FUNCTION_ID_LAST}
		}), "Function priorities");
    }
	{
		function_priority_table_t func_priors;
		initialize(func_priors);
		add(func_priors, 2, FUNCTION_ID_UNKNOWN);
		add(func_priors, 3, FUNCTION_ID_UNKNOWN);
		AssertEqual(func_priors.priors, (function_priorities_t{
			{ FUNCTION_ID_ERROR, FUNCTION_PRIORITY_UNKNOWN, 3 },
			{ 2, FUNCTION_PRIORITY_LAST, FUNCTION_ID_ERROR },
			{ 3, 3, FUNCTION_ID_LAST },
			{ FUNCTION_ID_UNKNOWN, 2, 2 }
		}), "Function priorities");
	}
	{
		function_priority_table_t func_priors;
		initialize(func_priors);
		add(func_priors, 2, FUNCTION_ID_UNKNOWN);
		add(func_priors, 3, FUNCTION_ID_UNKNOWN);
		add(func_priors, 4, FUNCTION_ID_UNKNOWN);
		AssertEqual(func_priors.priors, (function_priorities_t{
			{ FUNCTION_ID_ERROR, FUNCTION_PRIORITY_UNKNOWN, 4 },
			{ 2, FUNCTION_PRIORITY_LAST, FUNCTION_ID_ERROR },
			{ 3, 4, FUNCTION_ID_LAST },
			{ 4, 3, 2 },
			{ FUNCTION_ID_UNKNOWN, 2, 3 }
		}), "Function priorities");
	}
}

inline void test_priority_push_at_any_position() {
	{
		function_priority_table_t func_priors;
		initialize(func_priors);
		add(func_priors, 2, FUNCTION_ID_UNKNOWN);
		add(func_priors, 3, 2);
		add(func_priors, 4, 3);
		add(func_priors, 5, 2);
		AssertEqual(func_priors.priors, (function_priorities_t{
			{ FUNCTION_ID_ERROR, FUNCTION_PRIORITY_UNKNOWN, 2 },
			{ 4, FUNCTION_PRIORITY_LAST, FUNCTION_ID_ERROR },
			{ FUNCTION_ID_UNKNOWN, 2, 5 },
			{ 5, 4
			, 4 },
			{ 3, 5, FUNCTION_ID_LAST },
			{ 2, 3, 3 }
		}), "Function priorities");
	}
	{
		function_priority_table_t func_priors;
		initialize(func_priors);
		add(func_priors, 2, FUNCTION_ID_UNKNOWN);
		add(func_priors, 3, 2);
		add(func_priors, 4, 3);
		add(func_priors, 5, 4);
		add(func_priors, 6, 5);
		AssertEqual(func_priors.priors, (function_priorities_t{
			{ FUNCTION_ID_ERROR, FUNCTION_PRIORITY_UNKNOWN, 2 },
			{ 6, FUNCTION_PRIORITY_LAST, FUNCTION_ID_ERROR },
			{ FUNCTION_ID_UNKNOWN, 2, 3 },
			{ 2, 3, 4 },
			{ 3, 4, 5 },
			{ 4, 5, 6 },
			{ 5, 6, FUNCTION_ID_LAST }
		}), "Function priorities");
	}
}

void run_function_priority_tests() {
	TESTCASE
	test_priority_initialize();
    test_priority_push_basic();
	test_priority_push_at_any_position();
}