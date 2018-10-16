cmake_minimum_required(VERSION 3.12)

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

function(add_target_test target test_source)
    set(sources ${test_source} )

    if (${ARGC} GREATER 2)
        math(EXPR stop "${ARGC} - 1")
        foreach(loop_var RANGE 2 ${stop})
            list(APPEND sources ${ARGV${loop_var}})
        endforeach()
    endif()

    add_executable(${target} ${sources})
    set_target_properties(${target} PROPERTIES
        COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
        INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
        LINK_LIBRARIES ${Boost_LIBRARIES}
        CXX_STANDARD_REQUIRED ON
        COMPILE_OPTIONS -Wpedantic -Wall -Wextra
        )
    add_test(${target} ${target})
endfunction(add_target_test)

add_target_test(simple simple_tst.cpp)