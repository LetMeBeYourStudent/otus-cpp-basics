cmake_minimum_required(VERSION 3.2.0)

project(cpp_basic_otus_hw_7)

add_executable(google_tests_homework
        main.cpp
        ../HW_6/headers/array_ptr.h
        ../HW_6/headers/simple_vector.h
        ../HW_6/headers/single_linked_list.h
        source/test_SimpleVector.cpp
        source/test_SingleLinkedList.cpp)

target_link_libraries(google_tests_homework gtest gtest_main)
add_subdirectory(googletests)

target_compile_features(google_tests_homework PUBLIC cxx_std_17)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR
    CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(google_tests_homework PRIVATE 
        -g
        -Wall
        -Wextra
        -Werror
        -pedantic
        -Wno-unknown-pragmas
    )
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(google_tests_homework PRIVATE
        /EHsc
        /W4
        /WX
    )
endif()