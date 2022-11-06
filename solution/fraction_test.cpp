#include "fraction.h"

#include <gtest/gtest.h>

TEST(invalid_input, input1)
{
    EXPECT_THROW(solve::fraction(1, 0), std::overflow_error);
}
TEST(invalid_input, input2)
{
    solve::fraction test2(2, 4);
    EXPECT_THROW(test2 / solve::fraction(0, 0), std::overflow_error);
}
TEST(correctness, test1)
{
    solve::fraction test1(2, 4);
    EXPECT_TRUE(test1 == solve::fraction(2, 4));
}

TEST(correctness, test1_output)
{
    solve::fraction test1(2, 4);
    EXPECT_STREQ(test1.to_string().c_str(), "1/2");
}

TEST(correctness, test2)
{
    EXPECT_EQ(solve::fraction(1, 2) + solve::fraction(3, 4),
              solve::fraction(10, 8));
}
TEST(correctness, test3)
{
    EXPECT_EQ(solve::fraction(1, 2) - solve::fraction(3, 4),
              solve::fraction(-2, 8));
}
TEST(correctness, test4)
{
    EXPECT_EQ(solve::fraction(1, 2) * solve::fraction(3, 4),
              solve::fraction(3, 8));
}
TEST(correctness, test5)
{
    EXPECT_EQ(solve::fraction(1, 2) / solve::fraction(3, 4),
              solve::fraction(4, 6));
}