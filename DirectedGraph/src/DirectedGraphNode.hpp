#ifndef DIRECTEDGRAPH_DIRECTEDGRAPHNODE_HPP
#define DIRECTEDGRAPH_DIRECTEDGRAPHNODE_HPP

#include <optional>
#include <set>

#include "AdjacentNodesIterator.hpp"
#include "ConstAdjacentNodesIterator.hpp"
#include "DirectedGraphNodeAllocator.hpp"

namespace dgn
{
// Forward declaration
template <typename T, typename Allocator>
class DirectedGraph;

namespace details
{
template <typename T, typename Allocator = std::allocator<T>>
class DirectedGraphNode : private DirectedGraphNodeAllocator<T, Allocator>
{
public:
    DirectedGraphNode(DirectedGraph<T, Allocator> &graph, const T &data);
    DirectedGraphNode(DirectedGraph<T, Allocator> &graph, T &&data);

    DirectedGraphNode(DirectedGraph<T, Allocator> &graph, const T &data,
                      const Allocator &allocator);
    DirectedGraphNode(DirectedGraph<T, Allocator> &graph, T &&data,
                      const Allocator &allocator);

    DirectedGraphNode(const DirectedGraphNode &src);
    DirectedGraphNode(DirectedGraphNode &&src) noexcept;

    DirectedGraphNode &operator=(const DirectedGraphNode &rhs);
    DirectedGraphNode &operator=(DirectedGraphNode &&rhs) noexcept;

    [[nodiscard]] T &value() noexcept;
    [[nodiscard]] const T &value() const noexcept;

    bool operator==(const DirectedGraphNode &rhs) const;
    bool operator!=(const DirectedGraphNode &rhs) const;

    ~DirectedGraphNode();

private:
    friend DirectedGraph<T, Allocator>;
    DirectedGraph<T, Allocator> &m_graph;

    using adjancncyNodeListType = std::set<size_t>;
    adjancncyNodeListType m_adjancncyNodeIndices;

    [[nodiscard]] adjancncyNodeListType &getAdjancncyNodeList();
    [[nodiscard]] const adjancncyNodeListType &getAdjancncyNodeList() const;
};

template <typename T, typename Allocator>
DirectedGraphNode<T, Allocator>::DirectedGraphNode(
    DirectedGraph<T, Allocator> &graph, const T &data)
    : DirectedGraphNode<T, Allocator>{graph, data, Allocator()}
{}

template <typename T, typename Allocator>
DirectedGraphNode<T, Allocator>::DirectedGraphNode(
    DirectedGraph<T, Allocator> &graph, const T &data,
    const Allocator &allocator)
    : DirectedGraphNodeAllocator<T, Allocator>{allocator}, m_graph{graph}
{
    new (this->m_data) T{data};
}

template <typename T, typename Allocator>
DirectedGraphNode<T, Allocator>::DirectedGraphNode(
    DirectedGraph<T, Allocator> &graph, T &&data)
    : DirectedGraphNode<T, Allocator>{graph, std::move(data), Allocator{}}
{}

template <typename T, typename Allocator>
DirectedGraphNode<T, Allocator>::DirectedGraphNode(
    DirectedGraph<T, Allocator> &graph, T &&data, const Allocator &allocator)
    : DirectedGraphNodeAllocator<T, Allocator>{allocator}, m_graph{graph}
{
    new (this->m_data) T{std::move(data)};
}

template <typename T, typename Allocator>
DirectedGraphNode<T, Allocator>::DirectedGraphNode(const DirectedGraphNode &src)
    : DirectedGraphNodeAllocator<T, Allocator>{src.m_allocator},
      m_graph{src.m_graph},
      m_adjancncyNodeIndices{src.m_adjancncyNodeIndices}
{
    new (this->m_data) T(src.m_data);
}

template <typename T, typename Allocator>
DirectedGraphNode<T, Allocator>::DirectedGraphNode(
    DirectedGraphNode &&src) noexcept
    : DirectedGraphNodeAllocator<T, Allocator>{std::move(src)},
      m_graph{src.m_graph},
      m_adjancncyNodeIndices{std::move(src.m_adjancncyNodeIndices)}
{}

template <typename T, typename Allocator>
DirectedGraphNode<T, Allocator>::~DirectedGraphNode()
{
    if (this->m_data) { this->m_data->~T(); }
}

template <typename T, typename Allocator>
typename DirectedGraphNode<T, Allocator>::DirectedGraphNode &
DirectedGraphNode<T, Allocator>::operator=(
    const DirectedGraphNode<T, Allocator> &rhs)
{
    if (this != &rhs)
    {
        m_adjancncyNodeIndices = rhs.m_adjancncyNodeIndices;
        new (this->m_data) T(rhs.m_data);
    }
    return *this;
}

template <typename T, typename Allocator>
typename DirectedGraphNode<T, Allocator>::DirectedGraphNode &
DirectedGraphNode<T, Allocator>::operator=(
    DirectedGraphNode<T, Allocator> &&rhs) noexcept
{
    m_adjancncyNodeIndices = std::move(rhs.m_adjancncyNodeIndices);
    this->m_data = std::exchange(rhs.m_data, nullptr);

    return *this;
}

template <typename T, typename Allocator>
T &DirectedGraphNode<T, Allocator>::value() noexcept
{
    return *(this->m_data);
}

template <typename T, typename Allocator>
const T &DirectedGraphNode<T, Allocator>::value() const noexcept
{
    return *(this->m_data);
}

template <typename T, typename Allocator>
bool DirectedGraphNode<T, Allocator>::operator==(
    const DirectedGraphNode<T, Allocator> &rhs) const
{
    return &m_graph == &rhs.m_graph && *(this->m_data) == *(rhs.m_data)
           && this->m_adjancncyNodeIndices == rhs.m_adjancncyNodeIndices;
}

template <typename T, typename Allocator>
bool DirectedGraphNode<T, Allocator>::operator!=(
    const DirectedGraphNode<T, Allocator> &rhs) const
{
    return !(*this == rhs);
}

template <typename T, typename Allocator>
typename DirectedGraphNode<T, Allocator>::adjancncyNodeListType &
DirectedGraphNode<T, Allocator>::getAdjancncyNodeList()
{
    return m_adjancncyNodeIndices;
}

template <typename T, typename Allocator>
const typename DirectedGraphNode<T, Allocator>::adjancncyNodeListType &
DirectedGraphNode<T, Allocator>::getAdjancncyNodeList() const
{
    return m_adjancncyNodeIndices;
}
}  // namespace details
}  // namespace dgn

#endif  // DIRECTEDGRAPH_DIRECTEDGRAPHNODE_HPP
