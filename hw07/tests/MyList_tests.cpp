#include "MyList.hpp"
#include "Widget.h"
#include <gtest/gtest.h>

TEST(MyList, Create) {
    // Arrange
    MyList<int> container;

    // Act (empty for this test)

    // Assert
    ASSERT_EQ(container.size(), 0);
}

struct MyListFixture : public testing::Test {

    const size_t count = 10;
    MyList<std::size_t>* container = nullptr;

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
        container = new MyList<std::size_t>(); // the same container instance for all
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

TEST_F(MyListFixture, PushBack) {
    // Act
    container->push_back(0);

    // Assert
    ASSERT_EQ(container->size(), count + 1);
}

TEST_F(MyListFixture, PushFront) {

    container->insert(0, 10);

    // Assert
    ASSERT_EQ(container->size(), count + 1);
}

TEST_F(MyListFixture, PushMiddle) {

    container->insert(container->size() / 2, 20);

    // Assert
    ASSERT_EQ(container->size(), count + 1);
}

TEST_F(MyListFixture, EraseBack) {

    container->erase(container->size() - 1);

    // Assert
    ASSERT_EQ(container->size(), count - 1);
}

TEST_F(MyListFixture, EraseFront) {

    container->erase(0);

    // Assert
    ASSERT_EQ(container->size(), count - 1);
}

TEST_F(MyListFixture, EraseMiddle) {

    container->erase(container->size() / 2);

    // Assert
    ASSERT_EQ(container->size(), count - 1);
}

TEST_F(MyListFixture, GetBack) {

    // Assert
    ASSERT_EQ((*container)[container->size() - 1], 9);
}

TEST_F(MyListFixture, GetFront) {

    // Assert
    ASSERT_EQ((*container)[0], 0);
}

TEST_F(MyListFixture, GetMiddle) {

    // Assert
    ASSERT_EQ((*container)[container->size() / 2], 5);
}

TEST_F(MyListFixture, GetSize) {

    // Assert
    ASSERT_EQ(container->size(), 10);
}

TEST_F(MyListFixture, Copy) {

    MyList<std::size_t> container_copy;
    container_copy.push_back(1);
    container_copy = *container;

    ASSERT_EQ(container_copy.size(), container->size());
    // Assert
    for (std::size_t i = 0; i < count; ++i) {
        ASSERT_EQ((*container)[i], container_copy[i]);
    }
}

TEST_F(MyListFixture, Move) {

    MyList container_move = std::move(*container);

    // Assert
    ASSERT_EQ(container->size(), 0);
    ASSERT_EQ(container_move.size(), 10);
}

TEST(MyList, CheckDestructor) {
    // Arrange
    std::size_t countDestructors = 0;
    const size_t count = 10;
    auto *container = new MyList<Widget>();

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