
project(02.hello_world)

add_executable(hw02_hello_world
        hello_world.cpp
        example.cpp
        example.h
        move.h
        move.cpp
)

set_target_properties(hw02_hello_world PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
)