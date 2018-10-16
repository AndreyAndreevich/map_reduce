//
// Created by Андрей Лукин on 17.10.2018.
//

#define BOOST_TEST_LOG_LEVEL test_suite
#define BOOST_TEST_MODULE test_main
#include <boost/test/unit_test.hpp>
#include <boost/mpl/assert.hpp>

BOOST_AUTO_TEST_SUITE(simple)

    BOOST_AUTO_TEST_CASE(simple_test)
    {
        BOOST_CHECK_EQUAL(1,2);
    }

BOOST_AUTO_TEST_SUITE_END()