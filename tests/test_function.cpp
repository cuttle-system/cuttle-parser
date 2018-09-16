#define BOOST_TEST_DYN_LINK

#include <iostream>
#include <boost/test/unit_test.hpp>
#include <string>

#include "function.hpp"

using namespace cuttle;

BOOST_AUTO_TEST_SUITE(function_constructor_suite)

    BOOST_AUTO_TEST_CASE(case1) {
        function_t func {function_type::infix, 2};

        BOOST_CHECK_EQUAL(func.type, function_type::infix);
        BOOST_CHECK_EQUAL(func.args_number, 2u);
    }

BOOST_AUTO_TEST_SUITE_END()