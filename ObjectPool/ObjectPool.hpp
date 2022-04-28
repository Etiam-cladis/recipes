#include "ObjectPool/ObjectPool.h"

#include <utility>
#include <numeric>

template <typename T, typename Allocator>
ObjectPool<T, Allocator>::ObjectPool(const Allocator &allocator)
    : m_allocator{allocator}
{
}

template <typename T, typename Allocator>
ObjectPool<T, Allocator>::~ObjectPool()
{
        auto chunkSize = ms_initialChunkSize;
        for (auto *p : m_poll)
        {
                m_allocator.deallocate(p, chunkSize);
                chunkSize *= 2;
        }
        m_poll.clear();
}

template <typename T, typename Allocator>
template <typename... Args>
std::shared_ptr<T> ObjectPool<T, Allocator>::acquiredObject(Args &&...args)
{
        if (m_freeObjects.empty())
        {
                addChunk();
        }

        T *object{m_freeObjects.back()};
        new (object) T{std::forward<Args>(args)...};

        m_freeObjects.pop_back();

        return std::shared_ptr<T>{object, [this](T *object)
                                  {
                                          std::destroy_at(object);
                                          m_freeObjects.push_back(object);
                                  }};
}

template <typename T, typename Allocator>
void ObjectPool<T, Allocator>::addChunk()
{

        auto *object{m_allocator.allocate(m_newChunkSize)};
        m_poll.push_back(object);

        auto oldSize{m_freeObjects.size()};
        m_freeObjects.resize(oldSize + m_newChunkSize);
        std::iota(std::begin(m_freeObjects) + oldSize, std::end(m_freeObjects), object);

        m_newChunkSize *= 2;
}