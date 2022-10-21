#include <gtest/gtest.h>

#include <iostream>

#include "src/DirectedGraph.hpp"

class op_test : public ::testing::Test
{
public:
    dgn::DirectedGraph<int> graph{1, 5, 6, 9, 8, 4};
    virtual void SetUp() override
    {
        graph.insertEdge(1, 5);
        graph.insertEdge(1, 6);
        graph.insertEdge(1, 9);
        graph.insertEdge(1, 8);
        graph.insertEdge(1, 4);
        graph.insertEdge(6, 5);
    }
    virtual void TearDown() override {}
};

TEST_F(op_test, insert) { EXPECT_EQ(6, graph.size()); }
TEST_F(op_test, remove)
{
    graph.erase(graph.begin());
    EXPECT_EQ(5, graph.size());
}

class foo_test
{
public:
    foo_test() = default;
    foo_test(int value) : m_value{value} {}

    friend std::ostream &operator<<(std::ostream &os,

                                    const foo_test &f)
    {
        os << f.m_value;
        return os;
    }

    bool operator==(const foo_test &) const = default;

private:
    int m_value;
};

TEST(foo, insert)
{
    dgn::DirectedGraph<foo_test> foo_graph{3, 2, 1, 9, 4, 5, 6, 11};
    foo_graph.insertEdge(3, 2);
    foo_graph.insertEdge(3, 1);
    foo_graph.insertEdge(2, 9);
    foo_graph.insertEdge(2, 4);
    foo_graph.insertEdge(1, 5);
    foo_graph.insertEdge(1, 6);
    foo_graph.insertEdge(3, 11);
    EXPECT_EQ(8, foo_graph.size());
}

TEST(foo, remove)
{
    dgn::DirectedGraph<foo_test> foo_graph{3, 2, 1, 9, 4, 5, 6, 11};
    foo_graph.insertEdge(3, 2);
    foo_graph.insertEdge(3, 1);
    foo_graph.insertEdge(2, 9);
    foo_graph.insertEdge(2, 4);
    foo_graph.insertEdge(1, 5);
    foo_graph.insertEdge(1, 6);
    foo_graph.insertEdge(3, 11);
    foo_graph.erase(foo_graph.begin());
    EXPECT_EQ(7, foo_graph.size());
}
