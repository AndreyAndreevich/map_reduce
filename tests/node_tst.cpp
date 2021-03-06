//
// Created by Андрей Лукин on 29.10.2018.
//

#define BOOST_TEST_LOG_LEVEL test_suite
#define BOOST_TEST_MODULE test_main
#include <boost/test/unit_test.hpp>
#include <boost/mpl/assert.hpp>

#include "Node.h"

BOOST_AUTO_TEST_SUITE(Node_test)

BOOST_AUTO_TEST_CASE(push)
{
    Node<int> node;
    Node<int>::value_type value {1,2,3,4};
    BOOST_CHECK_EQUAL(node.push({}),0);
    BOOST_CHECK_EQUAL(node.push(value),1);
    BOOST_CHECK_EQUAL(node.max_depth(),1);

    BOOST_CHECK_EQUAL(node.push({1, 3, 4, 5}),2);
    BOOST_CHECK_EQUAL(node.push({1, 2, 4, 5}),3);
    BOOST_CHECK_EQUAL(node.max_depth(),3);

    BOOST_CHECK_EQUAL(node.push({1, 2, 4, 5}),3);
    BOOST_CHECK_EQUAL(node.max_depth(),3);

    BOOST_CHECK_EQUAL(node.push({1, 3, 4, 5}),2);
    BOOST_CHECK_EQUAL(node.max_depth(),3);

    BOOST_CHECK_EQUAL(node.push({0, 1, 2, 3, 4, 5}),1);
    BOOST_CHECK_EQUAL(node.max_depth(),3);

    BOOST_CHECK_EQUAL(node.push({0, 1, 2, 3, 4, 5, 6}),7);
    BOOST_CHECK_EQUAL(node.max_depth(),7);

    BOOST_CHECK_EQUAL(node.push({0, 1, 2, 3, 4}),5);
    BOOST_CHECK_EQUAL(node.max_depth(),7);
}

BOOST_AUTO_TEST_SUITE_END()