cmake_minimum_required(VERSION 3.2.0)

project(cpp_basic_otus_hw_5)

add_executable(statistics
        main.cpp
        source/statistics.cpp)

target_compile_features(statistics PUBLIC cxx_std_17)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR
    CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(statistics PRIVATE 
        -g
        -Wall
        -Wextra
        -Werror
        -pedantic
    )
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(statistics PRIVATE
        /EHsc
        /W4
        /WX
    )
endif()