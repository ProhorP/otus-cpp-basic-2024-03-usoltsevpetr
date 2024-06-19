cmake_minimum_required(VERSION 3.5)

project(06.homework)

add_executable(my_container
        main.cpp
        MyContainer.h
        MyVector.h
        MyVector.cpp
        MyForvardList.h
        MyForvardList.cpp
        MyList.h
        MyList.cpp
)

set_target_properties(my_container PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)
