#include <gtest/gtest.h>
#include <server_tests.hpp>

int main(int argc, char** argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}