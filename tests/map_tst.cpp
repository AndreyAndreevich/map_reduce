//
// Created by Андрей Лукин on 29.10.2018.
//

#define BOOST_TEST_LOG_LEVEL test_suite
#define BOOST_TEST_MODULE test_main
#include <boost/test/unit_test.hpp>
#include <boost/mpl/assert.hpp>

#include "Map.h"
#include <numeric>

BOOST_AUTO_TEST_SUITE(Maper)

BOOST_AUTO_TEST_CASE(incorrect_split)
{
    Map map;
    map.push("1234");
    map.push("2345");
    map.push("2222");
    map.push("3456");

    BOOST_CHECK_THROW(map.split(0),std::logic_error);
    BOOST_CHECK_THROW(map.split(std::numeric_limits<Map::size_type>::min()),std::logic_error);
    BOOST_CHECK_THROW(map.split(std::numeric_limits<Map::size_type>::max()),std::logic_error);
    BOOST_CHECK_THROW(map.split(std::numeric_limits<char>::max() -
        std::numeric_limits<char>::min() + 1),std::logic_error);

    auto partitions_1 = map.split(1);
    BOOST_CHECK_EQUAL(partitions_1.size(),1);

    auto partitions_3 = map.split(3);
    BOOST_CHECK_EQUAL(partitions_3.size(),3);

    auto partitions_100 = map.split(100);
    BOOST_CHECK_EQUAL(partitions_100.size(),100);

}

BOOST_AUTO_TEST_CASE(correct_split)
{
    constexpr char first_symbol = std::numeric_limits<char>::min();
    constexpr char last_symbol = std::numeric_limits<char>::max();
    static_assert(last_symbol - first_symbol == 255, "char must be equal one byte");

    std::string s1;
    std::string s2;
    std::string s3;
    std::string s4;
    std::string s5;
    std::string s6;
    std::string s7;
    std::string s8;

    s1.push_back(first_symbol);
    s2.push_back(first_symbol);
    s3.push_back(first_symbol + char(4));
    s4.push_back(first_symbol + char(21));

    s5.push_back(last_symbol);
    s6.push_back(last_symbol - char(24));
    s7.push_back(last_symbol - char(57));
    s8.push_back(last_symbol - char(57));

    Map map;
    map.push(s1 + "asd");
    map.push(s2 + "sad");
    map.push(s3 + "fdas");
    map.push(s4 + "ajsdlka");
    map.push(s5 + "ljslad");
    map.push(s6 + "dhjd");
    map.push(s7 + "sadasd");
    map.push(s8 + "ubskas");

    auto partitions = map.split(2);
    BOOST_REQUIRE_EQUAL(partitions.size(),2);
    BOOST_CHECK_EQUAL(partitions.at(0).size(),4);
    BOOST_CHECK_EQUAL(partitions.at(1).size(),4);
}

BOOST_AUTO_TEST_SUITE_END()