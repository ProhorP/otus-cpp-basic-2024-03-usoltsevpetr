#include "MyVector.hpp"
#include <gtest/gtest.h>

TEST(List, Create) {
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

TEST(List, PushFront) {
    // Arrange
    const size_t count = 10;
    MyVector<std::size_t> list;

    // Act
    for (std::size_t i = 0; i < count; ++i) {
        list.push_back(i);
    }

    list.insert(0, 10);

    // Assert
    ASSERT_EQ(list.size(), count + 1);
}

TEST(List, PushMiddle) {
    // Arrange
    const size_t count = 10;
    MyVector<std::size_t> list;

    // Act
    for (std::size_t i = 0; i < count; ++i) {
        list.push_back(i);
    }

    list.insert(list.size() / 2, 20);

    // Assert
    ASSERT_EQ(list.size(), count + 1);
}

TEST(List, EraseBack) {
    // Arrange
    const size_t count = 10;
    MyVector<std::size_t> list;

    // Act
    for (std::size_t i = 0; i < count; ++i) {
        list.push_back(i);
    }

    list.erase(list.size() - 1);

    // Assert
    ASSERT_EQ(list.size(), count - 1);
}

TEST(List, EraseFront) {
    // Arrange
    const size_t count = 10;
    MyVector<std::size_t> list;

    // Act
    for (std::size_t i = 0; i < count; ++i) {
        list.push_back(i);
    }

    list.erase(0);

    // Assert
    ASSERT_EQ(list.size(), count - 1);
}

TEST(List, EraseMiddle) {
    // Arrange
    const size_t count = 10;
    MyVector<std::size_t> list;

    // Act
    for (std::size_t i = 0; i < count; ++i) {
        list.push_back(i);
    }

    list.erase(list.size() / 2);

    // Assert
    ASSERT_EQ(list.size(), count - 1);
}

TEST(List, GetBack) {
    // Arrange
    const size_t count = 10;
    MyVector<std::size_t> list;

    // Act
    for (std::size_t i = 0; i < count; ++i) {
        list.push_back(i);
    }

    // Assert
    ASSERT_EQ(list[list.size() - 1], 9);
}

TEST(List, GetFront) {
    // Arrange
    const size_t count = 10;
    MyVector<std::size_t> list;

    // Act
    for (std::size_t i = 0; i < count; ++i) {
        list.push_back(i);
    }

    // Assert
    ASSERT_EQ(list[0], 0);
}

TEST(List, GetMiddle) {
    // Arrange
    const size_t count = 10;
    MyVector<std::size_t> list;

    // Act
    for (std::size_t i = 0; i < count; ++i) {
        list.push_back(i);
    }

    // Assert
    ASSERT_EQ(list[list.size() / 2], 5);
}

TEST(List, GetSize) {
    // Arrange
    const size_t count = 10;
    MyVector<std::size_t> list;

    // Act
    for (std::size_t i = 0; i < count; ++i) {
        list.push_back(i);
    }

    // Assert
    ASSERT_EQ(list.size(), 10);
}

TEST(List, Copy) {
    // Arrange
    const size_t count = 10;
    MyVector<std::size_t> list;

    // Act
    for (std::size_t i = 0; i < count; ++i) {
        list.push_back(i);
    }

    MyVector<std::size_t> list_copy(list);

    // Assert
    for (std::size_t i = 0; i < count; ++i) {
        ASSERT_EQ(list[i], list_copy[i]);
    }
}

TEST(List, Move) {
    // Arrange
    const size_t count = 10;
    MyVector<std::size_t> list;

    // Act
    for (std::size_t i = 0; i < count; ++i) {
        list.push_back(i);
    }

    MyVector list_move = std::move(list);

    // Assert
    ASSERT_EQ(list.size(), 0);
    ASSERT_EQ(list_move.size(), 10);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}