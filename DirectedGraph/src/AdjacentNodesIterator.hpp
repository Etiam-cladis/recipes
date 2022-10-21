#ifndef DIRECTEDGRAPH_ADJACENTNODESITERATOR_HPP
#define DIRECTEDGRAPH_ADJACENTNODESITERATOR_HPP

#include <set>

#include "ConstAdjacentNodesIterator.hpp"

namespace dgn
{
template <typename GraphType>
class AdjacentNodesIterator : public ConstAdjacentNodesIterator<GraphType>
{
public:
    using value_type = typename GraphType::value_type;
    using reference = value_type &;
    using pointer = value_type *;
    using difference_type = ptrdiff_t;
    using iterator_category = std::bidirectional_iterator_tag;
    using iterator_type = std::set<size_t>::iterator;

    // End iterator
    AdjacentNodesIterator() = default;

    AdjacentNodesIterator(iterator_type it, const GraphType &graph);

    reference operator*() const;

    pointer operator->() const;

    AdjacentNodesIterator &operator--();
    AdjacentNodesIterator operator--(int);
    AdjacentNodesIterator &operator++();
    AdjacentNodesIterator operator++(int);
};

template <typename GraphType>
AdjacentNodesIterator<GraphType>::AdjacentNodesIterator(iterator_type it,
                                                        const GraphType &graph)
    : ConstAdjacentNodesIterator<GraphType>{it, graph}
{}

template <typename GraphType>
typename AdjacentNodesIterator<GraphType>::reference
AdjacentNodesIterator<GraphType>::operator*() const
{
    return const_cast<reference>((this->m_graph[*(this->m_iterator)]));
}

template <typename GraphType>
typename AdjacentNodesIterator<GraphType>::pointer
AdjacentNodesIterator<GraphType>::operator->() const
{
    return const_cast<pointer>(&(this->m_graph[*(this->m_iterator)]));
}

template <typename GraphType>
AdjacentNodesIterator<GraphType> &AdjacentNodesIterator<GraphType>::operator++()
{
    this->increment();
    return *this;
}

template <typename GraphType>
AdjacentNodesIterator<GraphType> AdjacentNodesIterator<GraphType>::operator++(
    int)
{
    auto oldIt{*this};
    this->increment();
    return oldIt;
}

template <typename GraphType>
AdjacentNodesIterator<GraphType> &AdjacentNodesIterator<GraphType>::operator--()
{
    this->decrement();
    return *this;
}

template <typename GraphType>
AdjacentNodesIterator<GraphType> AdjacentNodesIterator<GraphType>::operator--(
    int)
{
    auto oldIt{*this};
    this->decrement();
    return oldIt;
}
}  // namespace dgn

#endif  // DIRECTEDGRAPH_ADJACENTNODESITERATOR_HPP
