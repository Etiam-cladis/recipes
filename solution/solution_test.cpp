#include "solution.h"

#include <gtest/gtest.h>

#include <algorithm>
#include <vector>

TEST(invalid_input, input)
{
    solution test1({1, 2, 3, 3, 3}, 24);
    EXPECT_FALSE(test1.valid_input());

    solution test2({1, 2, 3, 3}, 23);
    EXPECT_FALSE(test2.valid_input());

    solution test3({}, 23);
    EXPECT_FALSE(test3.valid_input());
}

TEST(valid_input, input)
{
    solution test1({1, 2, 3, 3}, 24);
    EXPECT_TRUE(test1.valid_input());
}

TEST(correctness, test)
{
    solution test1({3, 3, 3, 3}, 24);
    std::vector<std::string> test1_result{"3*3*3-3"};
    EXPECT_EQ(test1.get_result(), test1_result);

    solution test2({9, 9, 9, 9}, 24);
    EXPECT_EQ(test2.get_result(), std::vector<std::string>());

    solution test3({24, 0, 1, 1}, 24);
    std::vector<std::string> test3_result{"24*1*1",   "24*1/1",   "24+0*1*1", "24+0*1/1", "24+0+1-1",
                                          "24+0-1+1", "24+0/1*1", "24+0/1/1", "24+1-1",   "24-0*1*1",
                                          "24-0*1/1", "24-0+1-1", "24-0-1+1", "24-0/1*1", "24-0/1/1",
                                          "24-1+1",   "24/1*1",   "24/1/1"};
    std::sort(test3_result.begin(), test3_result.end());
    std::vector<std::string> test3_sorted = test3.get_result();
    std::sort(test3_sorted.begin(), test3_sorted.end());
    EXPECT_EQ(test3_result, test3_sorted);
}