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

    std::map<char,Node<char>> first_map;
    first_map.emplace('a',Node<char>{{'a','b','c'},{'a','b','d'},{'a','c'}});
    first_map.emplace('b',Node<char>{{'b','b','c'},{'b','b','d'},{'b','c'}});

    std::map<char,Node<char>> second_map;
    second_map.emplace('a',Node<char>{{'a','b','s'},{'a','b','c','l'},{'a','c'}});
    second_map.emplace('c',Node<char>{{'c','b','c'},{'c','b','d'},{'c','c'}});

    reduce.add_partition(std::move(first_map));
    reduce.add_partition(std::move(second_map));
    BOOST_CHECK_EQUAL(reduce.process(),4);
}

BOOST_AUTO_TEST_SUITE_END()