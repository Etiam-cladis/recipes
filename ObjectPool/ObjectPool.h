#ifndef OBJECTPOOL_OBJECTPOOL_H
#define OBJECTPOOL_OBJECTPOOL_H

#include <memory>
#include <vector>

// Provides an object pool that can be use for any class that provides default constructor.
// This object pool not thread safe.
// The pool only grows:object are nerver removed from the pool,until the pool is destroyed.
template <typename T, typename Allocator = std::allocator<T>>
class ObjectPool
{
public:
        ObjectPool() = default;
        ObjectPool(const Allocator &allocator);
        virtual ~ObjectPool();

        // Allow move construction and move assigment.
        ObjectPool(ObjectPool &&src) noexcept = default;
        ObjectPool &operator=(ObjectPool &&src) noexcept = default;

        // Disallow copy construction and copy assigment.
        ObjectPool(const ObjectPool &) = delete;
        ObjectPool &operator=(const ObjectPool &) = delete;

        // Return an object from pool.
        // Arguments can be provided which are perfectly forwarded to a constructor of T.
        template <typename... Args>
        std::shared_ptr<T> acquiredObject(Args &&...args);

private:
        // Contains chunks of memory in which instances of T created.
        // For each chunks,the pointer to its first object is stored.
        std::vector<T *> m_poll;
        // Contains  poninters to all free instances of T.
        std::vector<T *> m_freeObjects;
        // The number of T instances should be fit in the first allocated chunk;
        static const size_t ms_initialChunkSize{5};
        // The number of T instances should be fit in newly allocated chunk;
        // This value is doubled after each newly created chunk;
        size_t m_newChunkSize{ms_initialChunkSize};
        // Creating a new block of uninitiliazed memory.big enough to hold m_newChunkSize instances of T.
        void addChunk();
        // Uses to allocating and deallocating chunks;
        Allocator m_allocator;
};

#endif // OBJECTPOOL_OBJECTPOOL_H
