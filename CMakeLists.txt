cmake_minimum_required(VERSION 3.0.0)

project(hello_world)

add_executable(hello_world
        hello_world.cpp
        headers/functions.h
        source/functions.cpp)

add_executable(guess_number
        guess_number.cpp
        headers/GuessNumberGame.h
        source/GuessNumberGame.cpp
        source/binary_search.cpp
        headers/binary_search.h)