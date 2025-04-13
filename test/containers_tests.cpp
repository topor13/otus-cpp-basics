#include <iostream>
#include "include/serial_container_tests.hpp"
#include "include/list_container_tests.hpp"

#include <gtest/gtest.h>

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}