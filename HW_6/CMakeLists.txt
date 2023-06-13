cmake_minimum_required(VERSION 3.2.0)

project(cpp_basic_otus_hw_6)

add_executable(basicContainers
        main.cpp
        headers/array_ptr.h
        headers/simple_vector.h
        headers/single_linked_list.h
        headers/double_linked_list.h)

target_compile_features(basicContainers PUBLIC cxx_std_17)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR
    CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(basicContainers PRIVATE 
        -g
        -Wall
        -Wextra
        -Werror
        -pedantic
    )
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(basicContainers PRIVATE
        /EHsc
        /W4
        /WX
    )
endif()