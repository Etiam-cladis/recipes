#ifndef DIRECTEDGRAPH_SRC_CONSTADJACENTNODESITERATOR_HPP
#define DIRECTEDGRAPH_SRC_CONSTADJACENTNODESITERATOR_HPP

#include <iterator>
#include <set>

namespace dgn
{
        template <typename GraphType>
        class ConstAdjacentNodesIterator
        {
        public:
                using value_type = typename GraphType::value_type;
                using reference = const value_type &;
                using pointer = const value_type *;
                using difference_type = ptrdiff_t;
                using iterator_category = std::bidirectional_iterator_tag;
                using iterator_type = std::set<size_t>::const_iterator;

                // End iterator
                ConstAdjacentNodesIterator() = default;

                ConstAdjacentNodesIterator(iterator_type it, const GraphType &graph);

                constexpr reference operator*() const;

                constexpr pointer operator->() const;

                ConstAdjacentNodesIterator &operator--();
                ConstAdjacentNodesIterator operator--(int);
                ConstAdjacentNodesIterator &operator++();
                ConstAdjacentNodesIterator operator++(int);

                bool operator==(const ConstAdjacentNodesIterator &rhs) const;
                bool operator!=(const ConstAdjacentNodesIterator &rhs) const;

        private:
                iterator_type m_iterator;
                const GraphType &m_graph;

                // Help methods
                void increment();
                void decrement();
        };

        template <typename GraphType>
        ConstAdjacentNodesIterator<GraphType>::ConstAdjacentNodesIterator(iterator_type it, const GraphType &graph)
            : m_iterator{it},
              m_graph{graph}
        {
        }

        template <typename GraphType>
        constexpr typename ConstAdjacentNodesIterator<GraphType>::reference
        ConstAdjacentNodesIterator<GraphType>::operator*() const
        {
                return m_graph[*m_iterator];
        }

        template <typename GraphType>
        constexpr typename ConstAdjacentNodesIterator<GraphType>::pointer
        ConstAdjacentNodesIterator<GraphType>::operator->() const
        {
                return &(m_graph[*m_iterator]);
        }

        template <typename GraphType>
        ConstAdjacentNodesIterator<GraphType> &
        ConstAdjacentNodesIterator<GraphType>::operator++()
        {
                increment();
                return *this;
        }

        template <typename GraphType>
        ConstAdjacentNodesIterator<GraphType>
        ConstAdjacentNodesIterator<GraphType>::operator++(int)
        {
                auto oldIt{*this};
                increment();
                return oldIt;
        }

        template <typename GraphType>
        ConstAdjacentNodesIterator<GraphType> &
        ConstAdjacentNodesIterator<GraphType>::operator--()
        {
                decrement();
                return *this;
        }

        template <typename GraphType>
        ConstAdjacentNodesIterator<GraphType>
        ConstAdjacentNodesIterator<GraphType>::operator--(int)
        {
                auto oldIt{*this};
                decrement();
                return oldIt;
        }

        template <typename GraphType>
        bool ConstAdjacentNodesIterator<GraphType>::operator==(const ConstAdjacentNodesIterator &rhs) const
        {
                return (m_iterator == rhs.m_iterator &&
                        m_graph == rhs.m_graph);
        }

        template <typename GraphType>
        bool ConstAdjacentNodesIterator<GraphType>::operator!=(const ConstAdjacentNodesIterator &rhs) const
        {
                return !(*this == rhs);
        }

        template <typename GraphType>
        void ConstAdjacentNodesIterator<GraphType>::increment()
        {
                ++m_iterator;
        }

        template <typename GraphType>
        void ConstAdjacentNodesIterator<GraphType>::decrement()
        {
                --m_iterator;
        }
} // namespace dgn

#endif // DIRECTEDGRAPH_SRC_CONSTADJACENTNODESITERATOR_HPP
