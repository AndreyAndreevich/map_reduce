//
// Created by Андрей Лукин on 17.10.2018.
//

#define BOOST_TEST_LOG_LEVEL test_suite
#define BOOST_TEST_MODULE test_main
#include <boost/test/unit_test.hpp>
#include <boost/mpl/assert.hpp>

#include <fstream>
#include <iostream>

#include "Helpers.h"

constexpr auto simple_file = TEST_EXAMPLES_DIR "/simple_file.txt";
constexpr auto empty_file = TEST_EXAMPLES_DIR "/empty_file.txt";

BOOST_AUTO_TEST_SUITE(split_file_test)

std::ios::streamoff simple_file_size = []() {
    std::ifstream file(simple_file, std::ios_base::binary | std::ios_base::ate);
    std::ios::streamoff file_size = file.tellg();
    assert(file_size == 39);
    return file_size;
}();


BOOST_AUTO_TEST_CASE(incorrect_file)
{
    BOOST_CHECK_THROW(split_file("incorrect_file_name",1),std::logic_error);
    BOOST_CHECK_THROW(split_file(empty_file,0),std::logic_error);
}

BOOST_AUTO_TEST_CASE(incorrect_partition_count)
{
    BOOST_CHECK_THROW(split_file(simple_file,0),std::logic_error);
    BOOST_CHECK_THROW(split_file(simple_file,std::numeric_limits<unsigned int>::max()),std::logic_error);
    BOOST_CHECK_THROW(split_file(simple_file, simple_file_size + 1),std::logic_error);
}

BOOST_AUTO_TEST_CASE(get_partitions)
{
    uint partition_count = 2;
    auto partitions = split_file(simple_file,partition_count);
    BOOST_REQUIRE_EQUAL(partitions.size(),partition_count);
    BOOST_CHECK_EQUAL(partitions[0],20);
    BOOST_CHECK_EQUAL(partitions[1],simple_file_size);
}

BOOST_AUTO_TEST_SUITE_END()