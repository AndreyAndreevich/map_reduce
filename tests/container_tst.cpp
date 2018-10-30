//
// Created by Андрей Лукин on 29.10.2018.
//

#define BOOST_TEST_LOG_LEVEL test_suite
#define BOOST_TEST_MODULE test_main
#include <boost/test/unit_test.hpp>
#include <boost/mpl/assert.hpp>

#include "Map.h"

BOOST_AUTO_TEST_SUITE(Container_test)

BOOST_AUTO_TEST_CASE(add_value)
{
    std::string context = "a\n"
                          "b\n"
                          "c\n";

    std::stringstream stream(context);
    std::string buffer;
    Map map;
    while(std::getline(stream,buffer)) {
        map.add_value(buffer);
    }
    auto result = map.get_result();
    BOOST_CHECK_EQUAL(result.size(),3);
}

BOOST_AUTO_TEST_SUITE_END()

