#define BOOST_TEST_DYN_LINK

#include <iostream>
#include <boost/test/unit_test.hpp>
#include <string>
#include <unordered_map>
#include <vector>

#include "function_priority_methods.hpp"

using namespace cuttle;

struct func_priors_fixture {
    function_priority_table_t func_priors;

    void setup() {
        initialize(func_priors);
    }
};

BOOST_FIXTURE_TEST_SUITE(priority_initialize_suite, func_priors_fixture)

    BOOST_AUTO_TEST_CASE(case1) {
		BOOST_CHECK(func_priors.priors == (function_priorities_t {
			{ FUNCTION_ID_ERROR, FUNCTION_PRIORITY_ERROR, FUNCTION_ID_ERROR },
			{ FUNCTION_ID_ERROR, FUNCTION_PRIORITY_UNKNOWN, FUNCTION_ID_LAST },
			{ FUNCTION_ID_UNKNOWN, FUNCTION_PRIORITY_LAST, FUNCTION_ID_ERROR }
		}));
	}

    BOOST_AUTO_TEST_CASE(case2) {
		initialize(func_priors);
		BOOST_CHECK(func_priors.priors == (function_priorities_t{
		    { FUNCTION_ID_ERROR, FUNCTION_PRIORITY_ERROR, FUNCTION_ID_ERROR },
			{ FUNCTION_ID_ERROR, FUNCTION_PRIORITY_UNKNOWN, FUNCTION_ID_LAST },
			{ FUNCTION_ID_UNKNOWN, FUNCTION_PRIORITY_LAST, FUNCTION_ID_ERROR }
		}));
	}
}

BOOST_FIXTURE_TEST_SUITE(priority_push_basic_suite, func_priors_fixture)

    BOOST_AUTO_TEST_CASE(case1) {
		add(func_priors, 3, FUNCTION_ID_UNKNOWN);
		BOOST_CHECK(func_priors.priors == (function_priorities_t {
		    { FUNCTION_ID_ERROR, FUNCTION_PRIORITY_ERROR, FUNCTION_ID_ERROR },
			{ FUNCTION_ID_ERROR, FUNCTION_PRIORITY_UNKNOWN, 3 },
			{ 3, FUNCTION_PRIORITY_LAST, FUNCTION_ID_ERROR },
			{ FUNCTION_ID_UNKNOWN, 3, FUNCTION_ID_LAST}
		}));
    }

    BOOST_AUTO_TEST_CASE(case2) {
		add(func_priors, 3, FUNCTION_ID_UNKNOWN);
		add(func_priors, 4, FUNCTION_ID_UNKNOWN);
		BOOST_CHECK(func_priors.priors == (function_priorities_t{
		    { FUNCTION_ID_ERROR, FUNCTION_PRIORITY_ERROR, FUNCTION_ID_ERROR },
			{ FUNCTION_ID_ERROR, FUNCTION_PRIORITY_UNKNOWN, 4 },
			{ 3, FUNCTION_PRIORITY_LAST, FUNCTION_ID_ERROR },
			{ 4, 4, FUNCTION_ID_LAST },
			{ FUNCTION_ID_UNKNOWN, 3, 3 }
		}));
	}

    BOOST_AUTO_TEST_CASE(case3) {
		add(func_priors, 3, FUNCTION_ID_UNKNOWN);
		add(func_priors, 4, FUNCTION_ID_UNKNOWN);
		add(func_priors, 5, FUNCTION_ID_UNKNOWN);
		BOOST_CHECK(func_priors.priors == (function_priorities_t{
		    { FUNCTION_ID_ERROR, FUNCTION_PRIORITY_ERROR, FUNCTION_ID_ERROR },
			{ FUNCTION_ID_ERROR, FUNCTION_PRIORITY_UNKNOWN, 5 },
			{ 3, FUNCTION_PRIORITY_LAST, FUNCTION_ID_ERROR },
			{ 4, 5, FUNCTION_ID_LAST },
			{ 5, 4, 3 },
			{ FUNCTION_ID_UNKNOWN, 3, 4 }
		}));
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_FIXTURE_TEST_SUITE(priority_push_at_any_position_suite, func_priors_fixture)

	BOOST_AUTO_TEST_CASE(case1) {
		add(func_priors, 3, FUNCTION_ID_UNKNOWN);
		add(func_priors, 4, 3);
		add(func_priors, 5, 4);
		add(func_priors, 6, 3);
		BOOST_CHECK(func_priors.priors == (function_priorities_t{
		    { FUNCTION_ID_ERROR, FUNCTION_PRIORITY_ERROR, FUNCTION_ID_ERROR },
			{ FUNCTION_ID_ERROR, FUNCTION_PRIORITY_UNKNOWN, 3 },
			{ 5, FUNCTION_PRIORITY_LAST, FUNCTION_ID_ERROR },
			{ FUNCTION_ID_UNKNOWN, 3, 6 },
			{ 6, 5, 5 },
			{ 4, 6, FUNCTION_ID_LAST },
			{ 3, 4, 4 }
		}));
	}

	BOOST_AUTO_TEST_CASE(case2) {
		function_priority_table_t func_priors;
		initialize(func_priors);
		add(func_priors, 3, FUNCTION_ID_UNKNOWN);
		add(func_priors, 4, 3);
		add(func_priors, 5, 4);
		add(func_priors, 6, 5);
		add(func_priors, 7, 6);
		BOOST_CHECK(func_priors.priors == (function_priorities_t{
		    { FUNCTION_ID_ERROR, FUNCTION_PRIORITY_ERROR, FUNCTION_ID_ERROR },
			{ FUNCTION_ID_ERROR, FUNCTION_PRIORITY_UNKNOWN, 3 },
			{ 7, FUNCTION_PRIORITY_LAST, FUNCTION_ID_ERROR },
			{ FUNCTION_ID_UNKNOWN, 3, 4 },
			{ 3, 4, 5 },
			{ 4, 5, 6 },
			{ 5, 6, 7 },
			{ 6, 7, FUNCTION_ID_LAST }
		}));
	}

BOOST_AUTO_TEST_SUITE_END()