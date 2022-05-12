#include "src/DirectedGraph.hpp"

#include <iostream>

class foo
{
public:
        foo() = default;
        foo(int value) : m_value{value} {}

        friend std::ostream &operator<<(std::ostream &os, const foo &f)
        {
                os << f.m_value;
                return os;
        }

        bool operator==(const foo &) const = default;

private:
        int m_value;
};

int main()
{
        dgn::DirectedGraph<int> graph{1, 5, 6, 9, 8, 4};

        graph.insertEdge(1, 5);
        graph.insertEdge(1, 6);
        graph.insertEdge(1, 9);
        graph.insertEdge(1, 8);
        graph.insertEdge(1, 4);
        graph.insertEdge(6, 5);

        std::cout << "------------------------------start int graph  dfs------------------------------" << std::endl;
        graph.dfs(0, [&graph](size_t i)
                  { std::cout << "index:" << i << "  value:" << graph[i] << std::endl; });
        std::cout << "------------------------------end int graph dfs------------------------------" << std::endl;
        std::cout << '\n';
        std::cout << "------------------------------start int graph bfs------------------------------" << std::endl;
        graph.bfs(0, [&graph](size_t i)
                  { std::cout << "index:" << i << "  value:" << graph[i] << std::endl; });
        std::cout << "------------------------------end int graph bfs------------------------------" << std::endl;

        //----------------------------------------------------------------------------------------------------------------------------------------------------------

        dgn::DirectedGraph<foo> foo_graph{3, 2, 1, 9, 4, 5, 6, 11};
        foo_graph.insertEdge(3, 2);
        foo_graph.insertEdge(3, 1);
        foo_graph.insertEdge(2, 9);
        foo_graph.insertEdge(2, 4);
        foo_graph.insertEdge(1, 5);
        foo_graph.insertEdge(1, 6);
        foo_graph.insertEdge(3, 11);

        std::cout << "------------------------------start foo_graph  dfs------------------------------" << std::endl;
        foo_graph.dfs(0, [&foo_graph](size_t i)
                      { std::cout << "index:" << i << "  value:" << foo_graph[i] << std::endl; });
        std::cout << "------------------------------end foo_graph dfs------------------------------" << std::endl;
        std::cout << '\n';
        std::cout << "------------------------------start foo_graph bfs------------------------------" << std::endl;
        foo_graph.bfs(0, [&foo_graph](size_t i)
                      { std::cout << "index:" << i << "  value:" << foo_graph[i] << std::endl; });
        std::cout << "------------------------------end foo_graph bfs------------------------------" << std::endl;
}