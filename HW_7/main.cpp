//
// Created by Михаил Адаменко on 16.06.2023.
//

#include <gtest/gtest.h>

#ifndef TEST_SIMPLEVECTOR_CPP
#define TEST_SIMPLEVECTOR_CPP

#include "../HW_6/headers/simple_vector.h"

#pragma region GlobalTests

TEST(SimpleVectorTest, Create) {
    // Arrange
    SimpleVector<int> v1{1, 2, 3};
    SimpleVector<int> v2{1, 2, 3};
    // Act
    //Assert
    ASSERT_EQ(v1, v2);
}

TEST(SimpleVectorTest, Size) {
    // Arrange
    SimpleVector<int> v1{1, 2, 3};
    int expected_count = 3;
    // Act
    //Assert
    ASSERT_EQ(v1.size(), expected_count);
}

TEST(SimpleVectorTest, PopBack) {
    // Arrange
    SimpleVector<int> v1{1, 2, 3, 4};
    SimpleVector<int> v2{1, 2, 3};
    int expected_count = 3;
    // Act
    v1.pop_back();
    //Assert
    ASSERT_EQ(v1.size(), expected_count);
    ASSERT_EQ(v1, v2);
}

TEST(SimpleVectorTest, PushBack) {
    // Arrange
    SimpleVector<int> v1{1, 2, 3};
    SimpleVector<int> v2{1, 2, 3, 4};
    int expected_count = 4;
    // Act
    v1.push_back(4);
    //Assert
    ASSERT_EQ(v1.size(), expected_count);
    ASSERT_EQ(v1, v2);
}

TEST(SimpleVectorTest, At) {
    // Arrange
    SimpleVector<int> v1{1, 2, 3};
    int expected_value = 2;
    // Act
    //Assert
    ASSERT_EQ(v1.at(1), expected_value);
}

TEST(SimpleVectorTest, InsertFront) {
    // Arrange
    SimpleVector<int> v1{1, 2, 3};
    SimpleVector<int> v2{4, 1, 2, 3};
    // Act
    v1.insert(v1.cbegin(), 4);
    //Assert
    ASSERT_EQ(v1, v2);
}

TEST(SimpleVectorTest, InsertAtPosition) {
    // Arrange
    SimpleVector<int> v1{1, 2, 3};
    SimpleVector<int> v2{1, 2, 4, 3};
    // Act
    v1.insert(v1.cbegin() + 2, 4);
    //Assert
    ASSERT_EQ(v1, v2);
}

TEST(SimpleVectorTest, EraseAtPosition) {
    // Arrange
    SimpleVector<int> v1{1, 2, 3};
    SimpleVector<int> v2{1, 3};
    // Act
    v1.erase(v1.cbegin() + 1);
    //Assert
    ASSERT_EQ(v1, v2);
}

TEST(SimpleVectorTest, Clear) {
    // Arrange
    SimpleVector<int> v1{1, 2, 3};
    int expected_count = 0;
    // Act
    v1.clear();
    //Assert
    ASSERT_EQ(v1.size(), expected_count);
}

#pragma endregion

#endif

#ifndef TEST_SINGLELINKEDLIST_CPP
#define TEST_SINGLELINKEDLIST_CPP

#include "../HW_6/headers/single_linked_list.h"

#pragma region GlobalTests

TEST(SingleLinkedListTest, Create) {
    // Arrange
    SingleLinkedList<int> l1{1, 2, 3};
    SingleLinkedList<int> l2{1, 2, 3};
    // Act
    //Assert
    ASSERT_EQ(l1, l2);
}

TEST(SingleLinkedListTest, Size) {
    // Arrange
    SingleLinkedList<int> v1{1, 2, 3};
    int expected_count = 3;
    // Act
    //Assert
    ASSERT_EQ(v1.size(), expected_count);
}

TEST(SingleLinkedListTest, PopFront) {
    // Arrange
    SingleLinkedList<int> v1{1, 2, 3, 4};
    SingleLinkedList<int> v2{2, 3, 4};
    int expected_count = 3;
    // Act
    v1.pop_front();
    //Assert
    ASSERT_EQ(v1.size(), expected_count);
    ASSERT_EQ(v1, v2);
}

TEST(SingleLinkedListTest, PushFront) {
    // Arrange
    SingleLinkedList<int> v1{1, 2, 3};
    SingleLinkedList<int> v2{4, 1, 2, 3};
    int expected_count = 4;
    // Act
    v1.push_front(4);
    //Assert
    ASSERT_EQ(v1.size(), expected_count);
    ASSERT_EQ(v1, v2);
}
TEST(SingleLinkedListTest, InsertAfter) {
    // Arrange
    SingleLinkedList<int> v1{1, 2, 3};
    SingleLinkedList<int> v2{1, 4, 2, 3};
    // Act
    v1.insert_after(v1.cbegin(), 4);
    //Assert
    ASSERT_EQ(v1, v2);
}

TEST(SingleLinkedListTest, Clear) {
    // Arrange
    SingleLinkedList<int> v1{1, 2, 3};
    int expected_count = 0;
    // Act
    v1.clear();
    //Assert
    ASSERT_EQ(v1.size(), expected_count);
}

#pragma endregion

#endif

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}