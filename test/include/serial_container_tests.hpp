#include "include/serial_container.hpp"
#include <gtest/gtest.h>
#include <iostream>

struct SerialContainerTestF : public testing::Test {

    const size_t elementCount = 10;
    SerialContainer<size_t> serial;

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
            serial.push_back(i);
     }

    void TearDown() override {
        // per-test tear-down
        serial.clear();
    }
};

TEST(SerialContainerTest, successfullyCreateEmptyContainer) {
    SerialContainer<int> serial;
    const size_t expectedZeroSize = 0;
    const auto curSize = serial.size();
    EXPECT_EQ(curSize, expectedZeroSize);
    EXPECT_EQ(expectedZeroSize, curSize);
}

TEST_F(SerialContainerTestF, sucessfullyDeleteContainer) {
    const size_t expectedSizeBefore = 10;
    const size_t expectedSizeAfter = 0;
    ASSERT_EQ(serial.size(), expectedSizeBefore);
    serial.~SerialContainer();
    ASSERT_EQ(serial.size(), expectedSizeAfter);
    size_t serial_new;
    ASSERT_FALSE(serial.get(0, serial_new));
}

TEST_F(SerialContainerTestF, successfullyInsertFirstElement) {
    const size_t expectedSize = 11;
    ASSERT_LT(serial.size(), expectedSize);
    ASSERT_EQ(serial[0], 0);
    serial.push_front(11);
    ASSERT_EQ(serial.size(), expectedSize);
    ASSERT_EQ(serial[0], 11);
}

TEST_F(SerialContainerTestF, successfullyInsertLastElement) {
    const size_t expectedSize = 11;
    ASSERT_LT(serial.size(), expectedSize);
    ASSERT_EQ(serial[serial.size() - 1], 9);
    serial.push_back(11);
    ASSERT_EQ(serial.size(), expectedSize);
    ASSERT_EQ(serial[serial.size() - 1], 11);
}

TEST_F(SerialContainerTestF, successfullyInsertElementByPos) {
    const size_t expectedSize = 11;
    ASSERT_LT(serial.size(), expectedSize);
    ASSERT_EQ(serial[3], 3);
    serial.insert(11, 3);
    ASSERT_EQ(serial.size(), expectedSize);
    ASSERT_EQ(serial[3], 11);
}

TEST_F(SerialContainerTestF, successfullyDeleteFirstElement) {
    const size_t expectedSize = 9;
    ASSERT_GT(serial.size(), expectedSize);
    ASSERT_EQ(serial[0], 0);
    ASSERT_TRUE(serial.pop_front());
    ASSERT_EQ(serial.size(), expectedSize);
    ASSERT_EQ(serial[0], 1);
}

TEST_F(SerialContainerTestF, successfullyDeleteLastElement) {
    const size_t expectedSize = 9;
    ASSERT_GT(serial.size(), expectedSize);
    ASSERT_EQ(serial[serial.size() - 1], 9);
    ASSERT_TRUE(serial.pop_back());
    ASSERT_EQ(serial.size(), expectedSize);
    ASSERT_EQ(serial[serial.size() - 1], 8);
}

TEST_F(SerialContainerTestF, successfullyDeleteElementByPos) {
    const size_t expectedSize = 9;
    ASSERT_GT(serial.size(), expectedSize);
    ASSERT_EQ(serial[3], 3);
    ASSERT_TRUE(serial.erase(3));
    ASSERT_EQ(serial.size(), expectedSize);
    ASSERT_EQ(serial[3], 4);
}

TEST_F(SerialContainerTestF, noErrorIfDeleteOutOfRange) {
    const size_t expectedSize = 10;
    ASSERT_EQ(serial.size(), expectedSize);
    ASSERT_FALSE(serial.erase(100));
    ASSERT_EQ(serial.size(), expectedSize);
}

TEST_F(SerialContainerTestF, getElementByHisNumber) {
    for (size_t i = 0; i < elementCount; ++i)
    {
        ASSERT_EQ(serial[i], i);
    }
}

TEST_F(SerialContainerTestF, getSize) {
    size_t real_size = serial.size();
    size_t expected_size = 10;
    ASSERT_EQ(expected_size, real_size);
}
