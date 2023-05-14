#ifndef TST_MY_TEST_H
#define TST_MY_TEST_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include "loginwindow.h"
#include "registrationwindow.h"

using namespace testing;

TEST(my_suit, my_test)
{
    EXPECT_EQ(1, 1);
    ASSERT_THAT(0, Eq(0));
}

#endif // TST_MY_TEST_H
