#include "MyVector.hpp"
#include "Widget.h"
#include <gtest/gtest.h>

TEST(MyVector, Create) {
    // Arrange
    MyVector<int> container;

    // Act (empty for this test)

    // Assert
    ASSERT_EQ(container.size(), 0);
}

struct MyVectorFixture : public testing::Test {

    const size_t count = 10;
    MyVector<std::size_t>* container = nullptr;

    // Per-test-suite set-up.
    static void SetUpTestSuite() {
        //        std::cout << "SetUpTestSuite" << std::endl;
    }

    // Per-test-suite tear-down.
    static void TearDownTestSuite() {
        //        std::cout << "TearDownTestSuite" << std::endl;
    }

    // Per-test set-up
    void SetUp() override {
        //        std::cout << "SetUp" << std::endl;
        // Arrange
        container = new MyVector<std::size_t>(); // the same container instance for all
                                            // test cases

        // Create container with elementCount elements
        for (size_t i = 0; i < count; ++i)
            container->push_back(i);
    }

    // You can define per-test tear-down logic as usual.
    void TearDown() override {
        delete container;
        container = nullptr;
        //        std::cout << "TearDown" << std::endl;
        // Nothing to do for now
    }
};

TEST_F(MyVectorFixture, PushBack) {
    // Act
    container->push_back(0);

    // Assert
    ASSERT_EQ(container->size(), count + 1);
}

TEST_F(MyVectorFixture, PushFront) {

    container->insert(0, 10);

    // Assert
    ASSERT_EQ(container->size(), count + 1);
}

TEST_F(MyVectorFixture, PushMiddle) {

    container->insert(container->size() / 2, 20);

    // Assert
    ASSERT_EQ(container->size(), count + 1);
}

TEST_F(MyVectorFixture, EraseBack) {

    container->erase(container->size() - 1);

    // Assert
    ASSERT_EQ(container->size(), count - 1);
}

TEST_F(MyVectorFixture, EraseFront) {

    container->erase(0);

    // Assert
    ASSERT_EQ(container->size(), count - 1);
}

TEST_F(MyVectorFixture, EraseMiddle) {

    container->erase(container->size() / 2);

    // Assert
    ASSERT_EQ(container->size(), count - 1);
}

TEST_F(MyVectorFixture, GetBack) {

    // Assert
    ASSERT_EQ((*container)[container->size() - 1], 9);
}

TEST_F(MyVectorFixture, GetFront) {

    // Assert
    ASSERT_EQ((*container)[0], 0);
}

TEST_F(MyVectorFixture, GetMiddle) {

    // Assert
    ASSERT_EQ((*container)[container->size() / 2], 5);
}

TEST_F(MyVectorFixture, GetSize) {

    // Assert
    ASSERT_EQ(container->size(), 10);
}

TEST_F(MyVectorFixture, Copy) {

    MyVector<std::size_t> container_copy;
    container_copy.push_back(1);
    container_copy = *container;

    ASSERT_EQ(container_copy.size(), container->size());
    // Assert
    for (std::size_t i = 0; i < count; ++i) {
        ASSERT_EQ((*container)[i], container_copy[i]);
    }
}

TEST_F(MyVectorFixture, Move) {

    MyVector container_move = std::move(*container);

    // Assert
    ASSERT_EQ(container->size(), 0);
    ASSERT_EQ(container_move.size(), 10);
}

TEST(MyVector, CheckDestructor) {
    // Arrange
    std::size_t countDestructors = 0;
    const size_t count = 10;
    auto *container = new MyVector<Widget>();

    //act
    for (std::size_t i = 0; i < count; ++i) {
        container->push_back(Widget(&countDestructors));
    }

    //reset count destructor
    countDestructors = 0;

    delete container;

    // Assert
    ASSERT_EQ(countDestructors, count);
}