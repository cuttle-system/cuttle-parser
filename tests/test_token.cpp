
#define BOOST_TEST_DYN_LINK

#include <iostream>
#include <boost/test/unit_test.hpp>
#include "token_methods.hpp"

using namespace cuttle;

BOOST_AUTO_TEST_SUITE(token_constructor_suite)

    BOOST_AUTO_TEST_CASE(case1) {
        token_t tok {token_type::number, "1", 2, 10};

        BOOST_CHECK(tok.type == token_type::number);
        BOOST_CHECK(tok.value == "1");
        BOOST_CHECK(tok.line == 2);
        BOOST_CHECK(tok.col == 10);
    }
    
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(token_right_after_suite)

    BOOST_AUTO_TEST_CASE(case1) {
        token_t tok1 {token_type::number, "1", 1, 10};
        token_t tok2 {token_type::number, "2", 1, 11};
        token_t tok3 {token_type::number, "3", 2, 1};
        token_t tok4 {token_type::number, "4", 2, 3};
        token_t tok5 {token_type::number, "5", 2, 10};
        token_t tok6 {token_type::number, "6", 3, 11};

        BOOST_CHECK(tok1 >= tok2);
        BOOST_CHECK(!(tok2 >= tok1));
        BOOST_CHECK(!(tok2 >= tok2));

        BOOST_CHECK(!(tok3 >= tok4));
        BOOST_CHECK(!(tok4 >= tok3));
        BOOST_CHECK(!(tok4 >= tok4));

        BOOST_CHECK(!(tok5 >= tok6));
        BOOST_CHECK(!(tok6 >= tok5));
        BOOST_CHECK(!(tok6 >= tok6));

        BOOST_CHECK(!(tok1 >= tok5));
        BOOST_CHECK(!(tok5 >= tok1));
        BOOST_CHECK(!(tok5 >= tok5));
    }

BOOST_AUTO_TEST_SUITE_END()