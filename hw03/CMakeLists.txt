project(03.GuessNumber)

add_library(
        random_value
        random_value.cpp
        random_value.h
)

add_library(
        check_value
        check_value.cpp
        check_value.h
)

add_library(
        high_scores
        high_scores.cpp
        high_scores.h
)

target_link_libraries(high_scores
        random_value
        check_value
)

add_executable(
        hw03_GuessNumber
        main.cpp
)

target_link_libraries(hw03_GuessNumber
        high_scores
)