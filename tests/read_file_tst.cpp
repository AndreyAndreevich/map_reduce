//
// Created by Андрей Лукин on 17.10.2018.
//

#define BOOST_TEST_LOG_LEVEL test_suite
#define BOOST_TEST_MODULE test_main
#include <boost/test/unit_test.hpp>
#include <boost/mpl/assert.hpp>

#include <fstream>
#include <iostream>

#include "FileReaders.h"

constexpr auto simple_file = TEST_EXAMPLES_DIR "/simple_file.txt";
constexpr auto empty_file = TEST_EXAMPLES_DIR "/empty_file.txt";

const std::string context = "123\n"
                            "456\n"
                            "7 9\n"
                            "012\n"
                            "345\n"
                            "678\n"
                            "901\n"
                            "234\n"
                            "567\n"
                            "890\n";

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

    BOOST_REQUIRE_EQUAL(context.size(),40);

    std::stringstream stream(context);

    auto partitions = split_file(std::move(stream),partition_count);
    BOOST_REQUIRE_EQUAL(partitions.size(),partition_count);
    BOOST_CHECK_EQUAL(partitions[0],20);
    BOOST_CHECK_EQUAL(partitions[1],40);
}

BOOST_AUTO_TEST_SUITE_END()



BOOST_AUTO_TEST_SUITE(read_partition_test)

class TestMap : public IMap<std::string,int>
{
public:
    void push(value_type && value_) override {
        _vector.push_back(std::move(value_));
    }
    partitions_type split(const size_type & size_) override {
        return partitions_type();
    }
    std::vector<value_type> _vector;
};

BOOST_AUTO_TEST_CASE(incorrect_read)
{
    TestMap map;

    BOOST_REQUIRE_EQUAL(context.size(),40);

    BOOST_CHECK_THROW(read_partition(map,std::stringstream(context),-1,2),std::logic_error);
    BOOST_CHECK_THROW(read_partition(map,std::stringstream(context),3,2),std::logic_error);
    BOOST_CHECK_THROW(read_partition(map,std::stringstream(context),3,200),std::runtime_error);
    BOOST_CHECK_THROW(read_partition(map,std::stringstream(context),200,201),std::runtime_error);
}

BOOST_AUTO_TEST_CASE(correct_read)
{
    TestMap map;

    read_partition(map,std::stringstream(context),0,39);
    BOOST_CHECK_EQUAL(map._vector.size(),10);

    map._vector.clear();
    read_partition(map,std::stringstream(context),8,11);
    BOOST_CHECK_EQUAL(map._vector.size(),1);
    BOOST_CHECK_EQUAL(map._vector.at(0), "7 9");
}

BOOST_AUTO_TEST_SUITE_END()