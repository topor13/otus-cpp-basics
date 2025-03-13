cmake_minimum_required(VERSION 3.12)

project(06.containers)

add_executable(containers 
    src/containers.cpp
    src/include/list_container.hpp
    src/include/serial_container.hpp
)

set_target_properties(containers PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)