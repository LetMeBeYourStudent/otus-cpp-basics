cmake_minimum_required(VERSION 3.2.0)

project(cpp_basic_otus)

add_executable(guess_number
        guess_number.cpp
        headers/GuessNumberGame.h
        source/GuessNumberGame.cpp
        source/binary_search.cpp
        headers/binary_search.h)

target_compile_features(guess_number PUBLIC cxx_std_17)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR
    CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(guess_number PRIVATE 
        -g
        -Wall
        -Wextra
        -Werror
        -pedantic
    )
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(guess_number PRIVATE
        /EHsc
        /W4
        /WX
    )
endif()