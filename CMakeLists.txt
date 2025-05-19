cmake_minimum_required(VERSION 3.12)

project(09.topk_words_parallel)

# serial target
add_executable(topk_words
    topk_words.cpp    
)

# multithread target
add_executable(topk_words_parallel
    topk_words_parallel.cpp    
)

set_target_properties(topk_words topk_words_parallel PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)
