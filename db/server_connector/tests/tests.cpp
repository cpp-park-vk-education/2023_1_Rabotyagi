#include <gtest/gtest.h>
#include "connector_backend_tests.hpp"
#include "connector_tests.hpp"

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}