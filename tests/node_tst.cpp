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

    auto value_list = node.get_all_values();
    BOOST_CHECK_EQUAL(value_list.size(),1);
    BOOST_CHECK_EQUAL(node.size(),1);
    BOOST_CHECK(value_list.front() == value);

    BOOST_CHECK_EQUAL(node.push({1, 3, 4, 5}),2);
    BOOST_CHECK_EQUAL(node.push({1, 2, 4, 5}),3);
    BOOST_CHECK_EQUAL(node.size(),3);
    BOOST_CHECK_EQUAL(node.max_depth(),3);

    BOOST_CHECK_EQUAL(node.push({1, 2, 4, 5}),3);
    BOOST_CHECK_EQUAL(node.size(),3);
    BOOST_CHECK_EQUAL(node.max_depth(),3);

    BOOST_CHECK_EQUAL(node.push({1, 3, 4, 5}),2);
    BOOST_CHECK_EQUAL(node.size(),3);
    BOOST_CHECK_EQUAL(node.max_depth(),3);

    BOOST_CHECK_EQUAL(node.push({0, 1, 2, 3, 4, 5}),1);
    BOOST_CHECK_EQUAL(node.size(),4);
    BOOST_CHECK_EQUAL(node.max_depth(),3);

    BOOST_CHECK_EQUAL(node.push({0, 1, 2, 3, 4, 5, 6}),7);
    BOOST_CHECK_EQUAL(node.size(),4);
    BOOST_CHECK_EQUAL(node.max_depth(),7);

    BOOST_CHECK_EQUAL(node.push({0, 1, 2, 3, 4}),5);
    BOOST_CHECK_EQUAL(node.size(),4);
    BOOST_CHECK_EQUAL(node.max_depth(),7);

    value_list = node.get_all_values();
    BOOST_CHECK_EQUAL(value_list.size(),4);
    BOOST_CHECK(value_list.front() == Node<int>::value_type ({0,1,2,3,4,5,6}));
    value_list.pop_front();
    BOOST_CHECK(value_list.front() == Node<int>::value_type ({1,3,4,5}));
    value_list.pop_front();
    BOOST_CHECK(value_list.front() == Node<int>::value_type ({1,2,3,4}));
    value_list.pop_front();
    BOOST_CHECK(value_list.front() == Node<int>::value_type ({1,2,4,5}));
    value_list.pop_front();
}

BOOST_AUTO_TEST_CASE(merge)
{
    Node<int>::value_type value {1,2,3,4};

    Node<int> a(value);
    Node<int> node1 {{1,2,3},{1,3,4},{1,3,5,6,7},{1,2,3,4}};
    Node<int> node2 {{1,2,3},{1,2,3,4,5},{7,8,9}};
    BOOST_CHECK_EQUAL(node1.size(),3);
    BOOST_CHECK_EQUAL(node1.max_depth(),4);
    BOOST_CHECK_EQUAL(node2.size(),2);
    BOOST_CHECK_EQUAL(node2.max_depth(),4);

    node1.merge(node2);
    BOOST_CHECK_EQUAL(node1.size(),4);
    BOOST_CHECK_EQUAL(node1.max_depth(),5);
}

BOOST_AUTO_TEST_CASE(move) {
    Node<int> node1 {{1,2,3},{1,3,4},{1,3,5,6,7},{1,2,3,4}};
    BOOST_REQUIRE_EQUAL(node1.size(),3);

    Node<int> node2(std::move(node1));
    BOOST_REQUIRE_EQUAL(node2.size(),3);
    BOOST_REQUIRE_EQUAL(node1.size(),0);

    Node<int> node3;
    node3 = std::move(node2);
    BOOST_REQUIRE_EQUAL(node3.size(),3);
    BOOST_REQUIRE_EQUAL(node2.size(),0);
}

BOOST_AUTO_TEST_SUITE_END()