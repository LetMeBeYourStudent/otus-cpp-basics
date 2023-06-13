cmake_minimum_required(VERSION 3.2.0)

project(cpp_basic_otus)

add_executable(hello_world
       hello_world.cpp
       headers/functions.h
       source/functions.cpp)

target_compile_features(hello_world PUBLIC cxx_std_17)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR
    CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(hello_world PRIVATE 
        -g
        -Wall
        -Wextra
        -Werror
        -pedantic
    )
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(hello_world PRIVATE
        /EHsc
        /W4
        /WX
    )
endif()