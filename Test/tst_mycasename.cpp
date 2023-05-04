
#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include "client.h"

using namespace testing;

TEST(MySuiteName, MyCaseName)
{
    EXPECT_EQ(1, 1);
    ASSERT_THAT(0, Eq(0));
}

