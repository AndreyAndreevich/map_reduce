//
// Created by Андрей Лукин on 29.10.2018.
//

#define BOOST_TEST_LOG_LEVEL test_suite
#define BOOST_TEST_MODULE test_main
#include <boost/test/unit_test.hpp>
#include <boost/mpl/assert.hpp>

#include "Node.h"

#include <iostream>

BOOST_AUTO_TEST_SUITE(Node_test)

BOOST_AUTO_TEST_CASE(add_value)
{
    Node<int> node;
    Node<int>::value_type empty_value;
    Node<int>::value_type value {1,2,3,4};
    BOOST_CHECK_EQUAL(node.add_value({}),0);
    BOOST_CHECK_EQUAL(node.add_value(value),1);

    auto value_list = node.get_all_values();
    BOOST_CHECK_EQUAL(value_list.size(),1);
    BOOST_CHECK_EQUAL(node.size(),1);
    BOOST_CHECK(value_list.front() == value);

    BOOST_CHECK_EQUAL(node.add_value({1,3,4,5}),2);
    BOOST_CHECK_EQUAL(node.add_value({1,2,4,5}),3);
    BOOST_CHECK_EQUAL(node.size(),3);

    BOOST_CHECK_EQUAL(node.add_value({1,2,4,5}),3);
    BOOST_CHECK_EQUAL(node.size(),3);

    BOOST_CHECK_EQUAL(node.add_value({1,3,4,5}),2);
    BOOST_CHECK_EQUAL(node.size(),3);

    BOOST_CHECK_EQUAL(node.add_value({0,1,2,3,4,5}),1);
    BOOST_CHECK_EQUAL(node.size(),4);

    BOOST_CHECK_EQUAL(node.add_value({0,1,2,3,4,5,6}),7);
    BOOST_CHECK_EQUAL(node.size(),4);

    BOOST_CHECK_EQUAL(node.add_value({0,1,2,3,4}),5);
    BOOST_CHECK_EQUAL(node.size(),4);

    value_list = node.get_all_values();
    BOOST_CHECK_EQUAL(value_list.size(),4);
    BOOST_CHECK(value_list.front() == Node<int>::value_type ({0,1,2,3,4,5,6}));
    value_list.pop_front();
    std::cout << std::endl;
    BOOST_CHECK(value_list.front() == Node<int>::value_type ({1,3,4,5}));
    value_list.pop_front();
    BOOST_CHECK(value_list.front() == Node<int>::value_type ({1,2,3,4}));
    value_list.pop_front();
    BOOST_CHECK(value_list.front() == Node<int>::value_type ({1,2,4,5}));
    value_list.pop_front();
}

BOOST_AUTO_TEST_SUITE_END()