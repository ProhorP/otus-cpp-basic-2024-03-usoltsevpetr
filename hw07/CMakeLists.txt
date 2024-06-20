cmake_minimum_required(VERSION 3.5)

project(07.homework)

add_subdirectory(googletest)

add_executable(containers_tests
        tests/MyVector_tests.cpp
)

target_include_directories(
        containers_tests PRIVATE
        "${CMAKE_SOURCE_DIR}/hw06"
)

# Link test target against gtest libraries
target_link_libraries(
        containers_tests PRIVATE
        gtest gtest_main
)

set_target_properties(containers_tests PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)
