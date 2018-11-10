//
// Created by Андрей Лукин on 17.10.2018.
//

#define BOOST_TEST_LOG_LEVEL test_suite
#define BOOST_TEST_MODULE test_main
#include <boost/test/unit_test.hpp>
#include <boost/mpl/assert.hpp>

#include <fstream>

#include "Helpers.h"

constexpr auto simple_file = TEST_EXAMPLES_DIR "/simple_file.txt";
constexpr auto empty_file = TEST_EXAMPLES_DIR "/empty_file.txt";

BOOST_AUTO_TEST_SUITE(split_file_test)

BOOST_AUTO_TEST_CASE(incorrect_file)
{
    std::ifstream file(simple_file, std::ios_base::binary);
    file.close();
    BOOST_CHECK_THROW(split_file(std::move(file),1),std::logic_error);
    BOOST_CHECK_THROW(split_file(std::ifstream (empty_file, std::ios_base::binary),1),std::logic_error);
    BOOST_CHECK_THROW(split_file(std::stringstream(),1),std::logic_error);
}

BOOST_AUTO_TEST_CASE(incorrect_partition_count)
{
    BOOST_CHECK_THROW(split_file(std::stringstream("context"),0),std::logic_error);
    BOOST_CHECK_THROW(split_file(std::stringstream("context"),
            std::numeric_limits<uint>::max()),std::logic_error);
    BOOST_CHECK_THROW(split_file(std::stringstream("1234"), 5),std::logic_error);
}

BOOST_AUTO_TEST_CASE(get_partitions)
{
    uint partition_count = 2;
    std::string context = "123\n"
                          "456\n"
                          "789\n"
                          "012\n"
                          "345\n"
                          "678\n"
                          "901\n"
                          "234\n"
                          "567\n"
                          "890\n";

    BOOST_REQUIRE_EQUAL(context.size(),40);

    std::stringstream stream(context);

    auto partitions = split_file(std::move(stream),partition_count);
    BOOST_REQUIRE_EQUAL(partitions.size(),partition_count);
    BOOST_CHECK_EQUAL(partitions[0],20);
    BOOST_CHECK_EQUAL(partitions[1],context.size());
}

BOOST_AUTO_TEST_SUITE_END()