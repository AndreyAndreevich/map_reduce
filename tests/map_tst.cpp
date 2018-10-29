//
// Created by Андрей Лукин on 29.10.2018.
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

}
