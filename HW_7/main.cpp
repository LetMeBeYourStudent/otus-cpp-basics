//
// Created by Михаил Адаменко on 16.06.2023.
//

#include <gtest/gtest.h>
#include "source/test_SimpleVector.cpp"
#include "source/test_SingleLinkedList.cpp"

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}