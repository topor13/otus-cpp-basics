cmake_minimum_required(VERSION 3.12)

project(08.crc32_crack)

add_executable(crc32_crack 
    src/include/IO.hpp
    src/include/CRC32.hpp
    src/IO.cpp
    src/CRC32.cpp
    src/main.cpp
    
)

set_target_properties(crc32_crack PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

if (MSVC)
    target_compile_options(crc32_crack PUBLIC /W4)
else ()
    target_compile_options(crc32_crack PUBLIC -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion)
endif ()