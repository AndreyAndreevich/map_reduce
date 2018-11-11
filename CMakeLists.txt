cmake_minimum_required(VERSION 3.12)

if($ENV{TRAVIS_BUILD_NUMBER})
    project(map_reduce VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else()
    project(map_reduce VERSION 0.0.1)
endif()

set(CMAKE_CXX_STANDARD 14)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()
set(CMAKE_SKIP_RPATH OFF)

add_subdirectory(src)

enable_testing()
add_subdirectory(tests)

set(CPACK_GENERATOR DEB)
set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)
set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
set(CPACK_PACKAGE_CONTACT l.a.r.p@yandex.ru)

include(CPack)