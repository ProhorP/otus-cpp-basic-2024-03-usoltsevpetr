#include "MyVector.hpp"
#include "Widget.h"
#include <gtest/gtest.h>

TEST(MyVector, Create) {
    // Arrange
    MyVector<int> list;

    // Act (empty for this test)

    // Assert
    ASSERT_EQ(list.size(), 0);
}

struct MyVectorFixture : public testing::Test {

    const size_t count = 10;
    MyVector<std::size_t>* list = nullptr;

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
        list = new MyVector<std::size_t>(); // the same list instance for all
                                            // test cases

        // Create list with elementCount elements
        for (size_t i = 0; i < count; ++i)
            list->push_back(i);
    }

    // You can define per-test tear-down logic as usual.
    void TearDown() override {
        delete list;
        list = nullptr;
        //        std::cout << "TearDown" << std::endl;
        // Nothing to do for now
    }
};

TEST_F(MyVectorFixture, PushBack) {
    // Act
    list->push_back(0);

    // Assert
    ASSERT_EQ(list->size(), count + 1);
}

TEST_F(MyVectorFixture, PushFront) {

    list->insert(0, 10);

    // Assert
    ASSERT_EQ(list->size(), count + 1);
}

TEST_F(MyVectorFixture, PushMiddle) {

    list->insert(list->size() / 2, 20);

    // Assert
    ASSERT_EQ(list->size(), count + 1);
}

TEST_F(MyVectorFixture, EraseBack) {

    list->erase(list->size() - 1);

    // Assert
    ASSERT_EQ(list->size(), count - 1);
}

TEST_F(MyVectorFixture, EraseFront) {

    list->erase(0);

    // Assert
    ASSERT_EQ(list->size(), count - 1);
}

TEST_F(MyVectorFixture, EraseMiddle) {

    list->erase(list->size() / 2);

    // Assert
    ASSERT_EQ(list->size(), count - 1);
}

TEST_F(MyVectorFixture, GetBack) {

    // Assert
    ASSERT_EQ((*list)[list->size() - 1], 9);
}

TEST_F(MyVectorFixture, GetFront) {

    // Assert
    ASSERT_EQ((*list)[0], 0);
}

TEST_F(MyVectorFixture, GetMiddle) {

    // Assert
    ASSERT_EQ((*list)[list->size() / 2], 5);
}

TEST_F(MyVectorFixture, GetSize) {

    // Assert
    ASSERT_EQ(list->size(), 10);
}

TEST_F(MyVectorFixture, Copy) {

    MyVector<std::size_t> list_copy;
    list_copy.push_back(1);
    list_copy = *list;

    ASSERT_EQ(list_copy.size(), list->size());
    // Assert
    for (std::size_t i = 0; i < count; ++i) {
        ASSERT_EQ((*list)[i], list_copy[i]);
    }
}

TEST_F(MyVectorFixture, Move) {

    MyVector list_move = std::move(*list);

    // Assert
    ASSERT_EQ(list->size(), 0);
    ASSERT_EQ(list_move.size(), 10);
}

TEST(MyVector, CheckDestructor) {
    // Arrange
    std::size_t countDestructors = 0;
    const size_t count = 10;
    auto *list = new MyVector<Widget>();

    //act
    for (std::size_t i = 0; i < count; ++i) {
        list->push_back(Widget(&countDestructors));
    }

    //reset count destructor
    countDestructors = 0;

    delete list;

    // Assert
    ASSERT_EQ(countDestructors, count);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}