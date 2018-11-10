//
// Created by Andrey on 11/11/2018.
//

#define BOOST_TEST_LOG_LEVEL test_suite
#define BOOST_TEST_MODULE test_main
#include <boost/test/unit_test.hpp>
#include <boost/mpl/assert.hpp>

#include "Reduce.h"

BOOST_AUTO_TEST_SUITE(Reducer)

BOOST_AUTO_TEST_CASE(process)
{
    Reduce reduce;

    BOOST_CHECK_EQUAL(reduce.process(),0);

    reduce.push("abc");
    reduce.push("abd");
    reduce.push("ac");
    reduce.push("bbc");
    reduce.push("bbd");
    reduce.push("bc");
    reduce.push("abs");
    reduce.push("abcl");
    reduce.push("ac");
    reduce.push("cbc");
    reduce.push("cbd");
    reduce.push("cc");

    BOOST_CHECK_EQUAL(reduce.process(),4);
}

BOOST_AUTO_TEST_SUITE_END()