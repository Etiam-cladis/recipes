#ifndef DIRECTEDGRAPH_CONSTDIRECTEDGRAPHITERATOR_HPP
#define DIRECTEDGRAPH_CONSTDIRECTEDGRAPHITERATOR_HPP

#include <iterator>
#include <vector>

namespace dgn
{
// Forward declaration.
template <typename T, typename A>
class DirectedGraph;

template <typename GraphType>
class ConstDirectedGraphIterator
{
public:
    using value_type = typename GraphType::value_type;
    using reference = const value_type &;
    using pointer = const value_type *;
    using difference_type = ptrdiff_t;
    using iterator_category = std::random_access_iterator_tag;
    using iterator_type =
        typename GraphType::nodesContainerType::const_iterator;

    ConstDirectedGraphIterator() = default;

    constexpr ConstDirectedGraphIterator(iterator_type it,
                                         const GraphType &graph);

    constexpr reference operator*() const;

    constexpr pointer operator->() const;

    constexpr ConstDirectedGraphIterator &operator+=(
        difference_type n) noexcept;
    constexpr ConstDirectedGraphIterator &operator-=(
        difference_type n) noexcept;
    constexpr ConstDirectedGraphIterator operator-(difference_type n) noexcept;
    constexpr ConstDirectedGraphIterator operator+(difference_type n) noexcept;
    constexpr ConstDirectedGraphIterator &operator--();
    constexpr ConstDirectedGraphIterator operator--(int);
    constexpr ConstDirectedGraphIterator &operator++();
    constexpr ConstDirectedGraphIterator operator++(int);

    // No bounds checking
    constexpr reference operator[](size_t n) const;

    bool operator==(const ConstDirectedGraphIterator &it) const = default;

private:
    friend class DirectedGraph<value_type, typename GraphType::allocator_type>;

    iterator_type m_iterator;
    const GraphType &m_graph;
};

template <typename GraphType>
constexpr ConstDirectedGraphIterator<GraphType>::ConstDirectedGraphIterator(
    iterator_type it, const GraphType &graph)
    : m_iterator{it}, m_graph{graph}
{}

template <typename GraphType>
constexpr typename ConstDirectedGraphIterator<GraphType>::reference
ConstDirectedGraphIterator<GraphType>::operator*() const
{
    return *m_iterator;
}

template <typename GraphType>
constexpr typename ConstDirectedGraphIterator<GraphType>::pointer
ConstDirectedGraphIterator<GraphType>::operator->() const
{
    return &(*m_iterator);
}

template <typename GraphType>
constexpr ConstDirectedGraphIterator<GraphType> &
ConstDirectedGraphIterator<GraphType>::operator+=(difference_type n) noexcept
{
    m_iterator += n;
    return *this;
}

template <typename GraphType>
constexpr ConstDirectedGraphIterator<GraphType> &
ConstDirectedGraphIterator<GraphType>::operator-=(difference_type n) noexcept
{
    m_iterator -= n;
    return *this;
}

template <typename GraphType>
constexpr ConstDirectedGraphIterator<GraphType>
ConstDirectedGraphIterator<GraphType>::operator-(difference_type n) noexcept
{
    return ConstDirectedGraphIterator<GraphType>{m_iterator - n, m_graph};
}

template <typename GraphType>
constexpr ConstDirectedGraphIterator<GraphType>
ConstDirectedGraphIterator<GraphType>::operator+(difference_type n) noexcept
{
    return ConstDirectedGraphIterator<GraphType>{m_iterator + n, m_graph};
}

template <typename GraphType>
constexpr ConstDirectedGraphIterator<GraphType>
    &ConstDirectedGraphIterator<GraphType>::operator--()
{
    --m_iterator;
    return *this;
}

template <typename GraphType>
constexpr ConstDirectedGraphIterator<GraphType>
ConstDirectedGraphIterator<GraphType>::operator--(int)
{
    auto oldIt = *this;
    --m_iterator;
    return *oldIt;
}

template <typename GraphType>
constexpr ConstDirectedGraphIterator<GraphType>
    &ConstDirectedGraphIterator<GraphType>::operator++()
{
    ++m_iterator;
    return *this;
}

template <typename GraphType>
constexpr ConstDirectedGraphIterator<GraphType>
ConstDirectedGraphIterator<GraphType>::operator++(int)
{
    auto oldIt = *this;
    ++m_iterator;
    return *oldIt;
}

template <typename GraphType>
constexpr typename ConstDirectedGraphIterator<GraphType>::difference_type
operator-(
    const typename ConstDirectedGraphIterator<GraphType>::iterator_type &lhs,
    const typename ConstDirectedGraphIterator<GraphType>::iterator_type
        &rhs) noexcept
{
    return lhs - rhs;
}

template <typename GraphType>
constexpr typename ConstDirectedGraphIterator<GraphType>::reference
ConstDirectedGraphIterator<GraphType>::operator[](size_t n) const
{
    return *(m_graph.cbegin() + n);
}

template <typename T>
bool operator<(typename T::iterator_type lhs, typename T::iterator_type rhs)
{
    return (rhs - lhs) > 0;
}

template <typename T>
bool operator<=(typename T::iterator_type lhs, typename T::iterator_type rhs)
{
    return !(lhs > rhs);
}

template <typename T>
bool operator>(typename T::iterator_type lhs, typename T::iterator_type rhs)
{
    return rhs < lhs;
}

template <typename T>
bool operator>=(typename T::iterator_type lhs, typename T::iterator_type rhs)
{
    return !(lhs < rhs);
}

}  // namespace dgn

#endif  // DIRECTEDGRAPH_CONSTDIRECTEDGRAPHITERATOR_HPP
