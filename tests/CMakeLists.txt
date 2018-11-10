cmake_minimum_required(VERSION 3.12)

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

set(src ${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/src)
add_definitions(-DTEST_EXAMPLES_DIR="${CMAKE_CURRENT_SOURCE_DIR}/Test_examples")

function(add_target_test target test_source)
    set(sources ${test_source})

    if (${ARGC} GREATER 2)
        math(EXPR stop "${ARGC} - 1")
        foreach(loop_var RANGE 2 ${stop})
            list(APPEND sources ${ARGV${loop_var}})
        endforeach()
    endif()

    add_executable(${target} ${sources})

    target_include_directories(${target} PRIVATE
        ${Boost_INCLUDE_DIR}
        ${src}
        )

    set_target_properties(${target} PROPERTIES
        COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
        LINK_LIBRARIES ${Boost_LIBRARIES}
        CXX_STANDARD_REQUIRED ON
        COMPILE_OPTIONS -Wpedantic -Wall -Wextra
        )
    add_test(${target} ${target})
endfunction(add_target_test)

add_target_test(split_tst split_file_tst.cpp ${src}/Helpers.h)
add_target_test(node_tst node_tst.cpp ${src}/Node.h)
add_target_test(map_tst map_tst.cpp ${src}/Map.h)
