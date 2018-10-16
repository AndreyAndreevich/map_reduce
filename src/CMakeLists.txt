cmake_minimum_required(VERSION 3.12)

set(TARGET_NAME yamr)

find_package(Boost COMPONENTS program_options REQUIRED)

add_executable(${TARGET_NAME} main.cpp)

set_target_properties(${TARGET_NAME} PROPERTIES
    INCLUDE_DERICTORIES ${Boost_INCLUDE_DIR}
    CXX_STANDARD_REQUIRED ON
    COMPILE_OPTIONS -Wpedantic -Wall -Wextra
    )

install(TARGETS ${TARGET_NAME} RUNTIME DESTINATION bin)