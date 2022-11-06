#include "solution.h"

#include <gtest/gtest.h>

#include <algorithm>
#include <vector>

TEST(invalid_input, input1)
{
    solve::solution test1(24, 1, 2, 3, 3, 3);
    EXPECT_FALSE(test1.valid_input());
}
TEST(invalid_input, input2)
{
    solve::solution test2(24, 1, 2, 3);
    EXPECT_FALSE(test2.valid_input());
}
TEST(invalid_input, input3)
{
    solve::solution test3(23);
    EXPECT_FALSE(test3.valid_input());
}
TEST(invalid_input, input4)
{
    solve::solution test4;
    EXPECT_FALSE(test4.valid_input());
}

TEST(valid_input, input)
{
    solve::solution test1(24, 1, 2, 3, 3);
    EXPECT_TRUE(test1.valid_input());
}

TEST(correctness, test1)
{
    solve::solution test1(24, 3, 3, 3, 3);
    EXPECT_TRUE(test1.judge());
    std::cout << test1.get_result() << std::endl;
}

TEST(correctness, test2)
{
    solve::solution test2(24, 9, 9, 9, 9);
    EXPECT_FALSE(test2.judge());
}

TEST(correctness, test3)
{
    solve::solution test3(24, 3, 3, 8, 8);
    EXPECT_TRUE(test3.judge());
    std::cout << test3.get_result() << std::endl;
}