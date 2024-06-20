#include "MyVector.hpp"
#include <gtest/gtest.h>

TEST(List, Empty) {
    // Arrange
    MyVector<int> list;

    // Act (empty for this test)

    // Assert
    ASSERT_EQ(list.size(), 0);
}

TEST(List, PushBack) {
    // Arrange
    const size_t count = 10;
    MyVector<std::size_t> list;

    // Act
    for (std::size_t i = 0; i < count; ++i) {
        list.push_back(i);
    }

    // Assert
    ASSERT_EQ(list.size(), count);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}