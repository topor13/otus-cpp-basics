#include "include/list_container.hpp"
#include <gtest/gtest.h>
#include <iostream>

struct ListContainerTestF : public testing::Test {

    const size_t elementCount = 10;
    ListContainer<size_t> list;

    static void SetUpTestSuite() {
        // Per-test-suite set-up.
    }

    static void TearDownTestSuite() {
        // Per-test-suite tear-down.
    }

    void SetUp() override { 
        // Per-test set-up
        // Create list with elementCount elements
        for (size_t i = 0; i < elementCount; ++i) 
            list.push_back(i);
     }

    void TearDown() override {
        // per-test tear-down.
        list.clear();
    }
};

TEST(ListContainerTest, successfullyCreateEmptyContainer) {
    ListContainer<size_t> list;
    const size_t expectedZeroSize = 0;
    const auto curSize = list.size();
    EXPECT_EQ(curSize, expectedZeroSize);
    EXPECT_EQ(expectedZeroSize, curSize);
}

TEST_F(ListContainerTestF, sucessfullyDeleteContainer) {
    const size_t expectedSizeBefore = 10;
    const size_t expectedSizeAfter = 0;
    ASSERT_EQ(list.size(), expectedSizeBefore);
    list.~ListContainer();
    //ASSERT_EQ(list.size(), expectedSizeAfter);
    size_t list_new;
    ASSERT_FALSE(list.get(0, list_new));
}

TEST_F(ListContainerTestF, successfullyCopyFromOther) {
    const size_t expectedSize = 10;
    ListContainer<size_t> copied = ListContainer(list);
    ASSERT_EQ(list.size(), expectedSize);
    ASSERT_EQ(copied.size(), expectedSize);
    for (size_t i = 0; i < expectedSize; i++)
    {
        ASSERT_EQ(list[i], copied[i]);
        ASSERT_EQ(copied[i], list[i]);
    }
}

TEST_F(ListContainerTestF, successfullyInsertFirstElement) {
    const size_t expectedSize = 11;
    ASSERT_LT(list.size(), expectedSize);
    ASSERT_EQ(list[0], 0);
    list.push_front(11);
    ASSERT_EQ(list.size(), expectedSize);
    ASSERT_EQ(list[0], 11);
}

TEST_F(ListContainerTestF, successfullyInsertLastElement) {
    const size_t expectedSize = 11;
    ASSERT_LT(list.size(), expectedSize);
    ASSERT_EQ(list[list.size() - 1], 9);
    list.push_back(11);
    ASSERT_EQ(list.size(), expectedSize);
    ASSERT_EQ(list[list.size() - 1], 11);
}

TEST_F(ListContainerTestF, successfullyInsertElementByPos) {
    const size_t expectedSize = 11;
    ASSERT_LT(list.size(), expectedSize);
    ASSERT_EQ(list[3], 3);
    list.insert(11, 3);
    ASSERT_EQ(list.size(), expectedSize);
    ASSERT_EQ(list[3], 11);
}

TEST_F(ListContainerTestF, successfullyDeleteFirstElement) {
    const size_t expectedSize = 9;
    ASSERT_GT(list.size(), expectedSize);
    ASSERT_EQ(list[0], 0);
    ASSERT_TRUE(list.pop_front());
    ASSERT_EQ(list.size(), expectedSize);
    ASSERT_EQ(list[0], 1);
}

TEST_F(ListContainerTestF, successfullyDeleteLastElement) {
    const size_t expectedSize = 9;
    ASSERT_GT(list.size(), expectedSize);
    ASSERT_EQ(list[list.size() - 1], 9);
    ASSERT_TRUE(list.pop_back());
    ASSERT_EQ(list.size(), expectedSize);
    ASSERT_EQ(list[list.size() - 1], 8);
}

TEST_F(ListContainerTestF, successfullyDeleteElementByPos) {
    const size_t expectedSize = 9;
    ASSERT_GT(list.size(), expectedSize);
    ASSERT_EQ(list[3], 3);
    ASSERT_TRUE(list.erase(3));
    ASSERT_EQ(list.size(), expectedSize);
    ASSERT_EQ(list[3], 4);
}

TEST_F(ListContainerTestF, noErrorIfDeleteOutOfRange) {
    const size_t expectedSize = 10;
    ASSERT_EQ(list.size(), expectedSize);
    ASSERT_FALSE(list.erase(100));
    ASSERT_EQ(list.size(), expectedSize);
}

TEST_F(ListContainerTestF, getElementByHisNumber) {
    for (size_t i = 0; i < elementCount; ++i)
    {
        ASSERT_EQ(list[i], i);
    }
}

TEST_F(ListContainerTestF, getSize) {
    size_t real_size = list.size();
    size_t expected_size = 10;
    ASSERT_EQ(expected_size, real_size);
}
