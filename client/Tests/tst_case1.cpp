#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

using namespace testing;

TEST(Suite1, Case1)
{
    EXPECT_EQ(1, 1);
    ASSERT_THAT(0, Eq(0));
}

