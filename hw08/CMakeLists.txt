
cmake_minimum_required(VERSION 3.5)

project(08.homework)

add_executable(top_words
        top_words.cpp
)

target_include_directories(
        top_words PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

set_target_properties(top_words PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)
