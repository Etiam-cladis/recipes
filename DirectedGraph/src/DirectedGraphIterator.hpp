#ifndef DIRECTEDGRAPH_DIRECTEDGRAPHITERATOR_HPP
#define DIRECTEDGRAPH_DIRECTEDGRAPHITERATOR_HPP

#include "ConstDirectedGraphIterator.hpp"

namespace dgn
{
template <typename GraphType>
class DirectedGraphIterator : public ConstDirectedGraphIterator<GraphType>
{
public:
    using value_type = typename GraphType::value_type;
    using reference = value_type &;
    using pointer = value_type *;
    using difference_type = ptrdiff_t;
    using iterator_category = std::random_access_iterator_tag;
    using iterator_type = typename GraphType::nodesContainerType::iterator;

    DirectedGraphIterator() = default;

    constexpr DirectedGraphIterator(iterator_type it, const GraphType &graph);

    constexpr reference operator*() const;

    constexpr pointer operator->() const;

    constexpr DirectedGraphIterator &operator+=(difference_type n) noexcept;
    constexpr DirectedGraphIterator &operator-=(difference_type n) noexcept;
    constexpr DirectedGraphIterator operator-(difference_type n) noexcept;
    constexpr DirectedGraphIterator operator+(difference_type n) noexcept;
    constexpr DirectedGraphIterator &operator--();
    constexpr DirectedGraphIterator operator--(int);
    constexpr DirectedGraphIterator &operator++();
    constexpr DirectedGraphIterator operator++(int);

    // No bounds checking
    constexpr reference operator[](size_t n) const;

    bool operator==(const DirectedGraphIterator &it) const = default;
};

template <typename GraphType>
constexpr DirectedGraphIterator<GraphType>::DirectedGraphIterator(
    iterator_type it, const GraphType &graph)
    : ConstDirectedGraphIterator<GraphType>{it, graph}
{}

template <typename GraphType>
constexpr typename DirectedGraphIterator<GraphType>::reference
DirectedGraphIterator<GraphType>::operator*() const
{
    return const_cast<reference>(*this->m_iterator);
}

template <typename GraphType>
constexpr typename DirectedGraphIterator<GraphType>::pointer
DirectedGraphIterator<GraphType>::operator->() const
{
    return const_cast<pointer>(&(*this->m_iterator));
}

template <typename GraphType>
constexpr DirectedGraphIterator<GraphType>
    &DirectedGraphIterator<GraphType>::operator+=(difference_type n) noexcept
{
    this->m_iterator += n;
    return *this;
}

template <typename GraphType>
constexpr DirectedGraphIterator<GraphType>
    &DirectedGraphIterator<GraphType>::operator-=(difference_type n) noexcept
{
    this->m_iterator -= n;
    return *this;
}

template <typename GraphType>
constexpr DirectedGraphIterator<GraphType>
DirectedGraphIterator<GraphType>::operator-(difference_type n) noexcept
{
    return DirectedGraphIterator<GraphType>{this->m_iterator - n,
                                            this->m_graph};
}

template <typename GraphType>
constexpr DirectedGraphIterator<GraphType>
DirectedGraphIterator<GraphType>::operator+(difference_type n) noexcept
{
    return DirectedGraphIterator<GraphType>{this->m_iterator + n,
                                            this->m_graph};
}

template <typename GraphType>
constexpr DirectedGraphIterator<GraphType>
    &DirectedGraphIterator<GraphType>::operator--()
{
    --this->m_iterator;
    return *this;
}

template <typename GraphType>
constexpr DirectedGraphIterator<GraphType>
DirectedGraphIterator<GraphType>::operator--(int)
{
    auto oldIt = *this;
    --this->m_iterator;
    return *oldIt;
}

template <typename GraphType>
constexpr DirectedGraphIterator<GraphType>
    &DirectedGraphIterator<GraphType>::operator++()
{
    ++this->m_iterator;
    return *this;
}

template <typename GraphType>
constexpr DirectedGraphIterator<GraphType>
DirectedGraphIterator<GraphType>::operator++(int)
{
    auto oldIt = *this;
    ++this->m_iterator;
    return *oldIt;
}

template <typename GraphType>
constexpr typename DirectedGraphIterator<GraphType>::difference_type operator-(
    const typename DirectedGraphIterator<GraphType>::iterator_type &lhs,
    const typename DirectedGraphIterator<GraphType>::iterator_type
        &rhs) noexcept
{
    return lhs - rhs;
}

template <typename GraphType>
constexpr typename DirectedGraphIterator<GraphType>::reference
DirectedGraphIterator<GraphType>::operator[](size_t n) const
{
    return const_cast<reference>(*(this->m_graph.cbegin() + n));
}

template <typename GraphType>
bool operator<(typename DirectedGraphIterator<GraphType>::iterator_type lhs,
               typename DirectedGraphIterator<GraphType>::iterator_type rhs)
{
    return (rhs - lhs) > 0;
}

template <typename GraphType>
bool operator<=(typename DirectedGraphIterator<GraphType>::iterator_type lhs,
                typename DirectedGraphIterator<GraphType>::iterator_type rhs)
{
    return !(lhs > rhs);
}

template <typename GraphType>
bool operator>(typename DirectedGraphIterator<GraphType>::iterator_type lhs,
               typename DirectedGraphIterator<GraphType>::iterator_type rhs)
{
    return rhs < lhs;
}

template <typename GraphType>
bool operator>=(typename DirectedGraphIterator<GraphType>::iterator_type lhs,
                typename DirectedGraphIterator<GraphType>::iterator_type rhs)
{
    return !(lhs < rhs);
}

}  // namespace dgn

#endif  // DIRECTEDGRAPH_DIRECTEDGRAPHITERATOR_HPP
