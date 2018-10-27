cmake_minimum_required(VERSION 3.12)

set(TARGET_NAME yamr)

find_package(Boost COMPONENTS program_options filesystem REQUIRED)

set(SOURCES
    Helpers.cpp)

add_executable(${TARGET_NAME} main.cpp)

set_target_properties(${TARGET_NAME} PROPERTIES
    COMPILE_DEFINITIONS BOOST_FILESYSTEM_NO_DEPRECATED
    INCLUDE_DERICTORIES ${Boost_INCLUDE_DIR}
    CXX_STANDARD_REQUIRED ON
    COMPILE_OPTIONS -Wpedantic -Wall -Wextra
    )

install(TARGETS ${TARGET_NAME} RUNTIME DESTINATION bin)