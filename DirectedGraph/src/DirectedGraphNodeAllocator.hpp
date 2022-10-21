#ifndef DIRECTEDGRAPH_DIRECTEDGRAPHNODEALLOCATOR_HPP
#define DIRECTEDGRAPH_DIRECTEDGRAPHNODEALLOCATOR_HPP

#include <memory>

namespace dgn
{

namespace details
{
// For exception safe allocate
template <typename T, typename Allocator = std::allocator<T>>
class DirectedGraphNodeAllocator
{
protected:
    explicit DirectedGraphNodeAllocator(const Allocator &allocator);

    DirectedGraphNodeAllocator(const DirectedGraphNodeAllocator &) = delete;
    DirectedGraphNodeAllocator(DirectedGraphNodeAllocator &&) noexcept;

    DirectedGraphNodeAllocator &operator=(const DirectedGraphNodeAllocator &) =
        delete;
    DirectedGraphNodeAllocator &operator=(
        DirectedGraphNodeAllocator &&) noexcept = delete;

    ~DirectedGraphNodeAllocator();

    Allocator m_allocator;
    T *m_data{nullptr};
};

template <typename T, typename Allocator>
DirectedGraphNodeAllocator<T, Allocator>::DirectedGraphNodeAllocator(
    const Allocator &allocator)
    : m_allocator{allocator}
{
    m_data = m_allocator.allocate(1);
}

template <typename T, typename Allocator>
DirectedGraphNodeAllocator<T, Allocator>::DirectedGraphNodeAllocator(
    DirectedGraphNodeAllocator &&src) noexcept
    : m_allocator{std::move(src.m_allocator)},
      m_data{std::exchange(src.m_data, nullptr)}
{}

template <typename T, typename Allocator>
DirectedGraphNodeAllocator<T, Allocator>::~DirectedGraphNodeAllocator()
{
    m_allocator.deallocate(m_data, 1);
    m_data = nullptr;
}

}  // namespace details
}  // namespace dgn

#endif  // DIRECTEDGRAPH_DIRECTEDGRAPHNODEALLOCATOR_HPP
