cmake_minimum_required(VERSION 3.12)

project(01.hello_world)

add_executable(hello_world 
    src/include/example.h
    src/include/move_me_out.h
    src/hello_world.cpp
    src/example.cpp
    src/move_me_out.cpp
    
)

set_target_properties(hello_world PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)