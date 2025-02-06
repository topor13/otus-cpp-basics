cmake_minimum_required(VERSION 3.12)

project(03.guess)

add_executable(guess 
    src/include/high_scores.h
    src/include/help.h
    src/guess.cpp
    src/high_scores.cpp
    src/help.cpp
)

set_target_properties(guess PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)