cmake_minimum_required(VERSION 3.5)

project(06.homework)

add_executable(my_container
        main.cpp
        MyContainer.h
        MyVector.hpp
        MyForvardList.hpp
        MyList.hpp
)

set_target_properties(my_container PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)
