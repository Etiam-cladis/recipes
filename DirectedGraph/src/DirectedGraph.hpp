#ifndef DIRECTEDGRAPH_DIRECTEDGRAPH_HPP
#define DIRECTEDGRAPH_DIRECTEDGRAPH_HPP

#include "DirectedGraphNode.hpp"
#include "AdjacentNodesIterator.hpp"
#include "ConstAdjacentNodesIterator.hpp"
#include "ConstDirectedGraphIterator.hpp"
#include "DirectedGraphIterator.hpp"

#include <memory>
#include <utility>
#include <vector>
#include <stack>
#include <queue>
#include <iterator>
#include <optional>
#include <initializer_list>
#include <set>
#include <algorithm>
#include <concepts>

namespace dgn
{
        template <typename T>
        concept has_size_type = requires
        {
                typename T::size_type;
        };

        template <typename T, typename Allocator = std::allocator<T>>
        class DirectedGraph
        {
        public:
                using value_type = T;
                using reference = value_type &;
                using const_reference = const value_type &;
                using allocator_type = Allocator;
                using size_type = size_t;
                using difference_type = ptrdiff_t;

                using iterator = DirectedGraphIterator<DirectedGraph>;
                using const_iterator = ConstDirectedGraphIterator<DirectedGraph>;
                using reverse_iterator = std::reverse_iterator<iterator>;
                using const_reverse_iterator = std::reverse_iterator<const_iterator>;

                using iterator_adjacent_nodes = AdjacentNodesIterator<DirectedGraph>;
                using const_iterator_adjacent_nodes = ConstAdjacentNodesIterator<DirectedGraph>;
                using reverse_iterator_adjacent_nodes = std::reverse_iterator<iterator>;
                using const_reverse_iterator_adjacent_nodes = std::reverse_iterator<iterator>;

                DirectedGraph() noexcept(noexcept(Allocator{})) = default;
                explicit DirectedGraph(const Allocator &allocator) noexcept;
                DirectedGraph(std::initializer_list<T> list, const Allocator &allcator = Allocator{});

                template <typename Iter>
                DirectedGraph(Iter first, Iter last, const Allocator &allocator = Allocator{});

                DirectedGraph &operator=(std::initializer_list<T> init);

                void assign(std::initializer_list<T> init);

                template <typename Iter>
                void assign(Iter first, Iter last);

                [[nodiscard]] allocator_type getAllocator() const;

                std::pair<iterator, bool> insert(const T &value);
                std::pair<iterator, bool> insert(T &&value);
                // There is no benefit of using hint. Keep it for compatibility
                // Ignore and insert
                std::pair<iterator, bool> insert(const_iterator hint, const T &value);
                std::pair<iterator, bool> insert(const_iterator hint, T &&value);

                // Removes the element at pos.
                // Return iterator following the last removed element.
                iterator erase(const_iterator pos);
                iterator erase(const_iterator first, const_iterator last);
                size_type erase(const T &nodeValue);

                void updateNodeValue(iterator pos, const T &newValue);
                void updateNodeValue(iterator pos, T &&newValue);

                // Return true if the edge was created successfully,false otherwise.
                bool insertEdge(const T &fromNodeValue, const T &toNodeValue);

                // Return true if the given edge was erased,false otherwise.
                bool eraseEdge(const T &fromNodeValue, const T &toNodeValue);

                void clear() noexcept;

                // No bounds checking is done.
                reference operator[](size_type index);
                const_reference operator[](size_type index) const;

                reference at(size_type index);
                const_reference at(size_type index) const;

                template <typename Index, typename Func, typename... Args>
                requires((has_size_type<Index> || std::convertible_to<Index, size_t>)&&std::invocable<Func, Index, Args...>) //
                    void dfs(Index startIndex, Func &&fuc, Args &&...args);

                template <typename Index, typename Func, typename... Args>
                requires((has_size_type<Index> || std::convertible_to<Index, size_t>)&&std::invocable<Func, Index, Args...>) //
                    void bfs(Index startIndex, Func &&fuc, Args &&...args);

                iterator find(const T &nodeValue);
                const_iterator find(const T &nodeValue) const;

                bool contains(const T &nodeValue) const;

                iterator begin() noexcept;
                iterator end() noexcept;
                const_iterator begin() const noexcept;
                const_iterator end() const noexcept;
                const_iterator cbegin() const noexcept;
                const_iterator cend() const noexcept;

                reverse_iterator rbegin() noexcept;
                reverse_iterator rend() noexcept;
                const_reverse_iterator rbegin() const noexcept;
                const_reverse_iterator rend() const noexcept;
                const_reverse_iterator crbegin() const noexcept;
                const_reverse_iterator crend() const noexcept;

                iterator_adjacent_nodes begin(const T &nodeValue) noexcept;
                iterator_adjacent_nodes end(const T &nodeValue) noexcept;
                const_iterator_adjacent_nodes begin(const T &nodeValue) const noexcept;
                const_iterator_adjacent_nodes end(const T &nodeValue) const noexcept;
                const_iterator_adjacent_nodes cbegin(const T &nodeValue) const noexcept;
                const_iterator_adjacent_nodes cend(const T &nodeValue) const noexcept;

                reverse_iterator_adjacent_nodes rbegin(const T &nodeValue) noexcept;
                reverse_iterator_adjacent_nodes rend(const T &nodeValue) noexcept;
                const_reverse_iterator_adjacent_nodes rbegin(const T &nodeValue) const noexcept;
                const_reverse_iterator_adjacent_nodes rend(const T &nodeValue) const noexcept;
                const_reverse_iterator_adjacent_nodes crbegin(const T &nodeValue) const noexcept;
                const_reverse_iterator_adjacent_nodes crend(const T &nodeValue) const noexcept;

                bool operator==(const DirectedGraph &rhs) const;
                bool operator!=(const DirectedGraph &rhs) const;

                void swap(DirectedGraph &rhs) noexcept;

                [[nodiscard]] size_type size() const;
                [[nodiscard]] size_type maxSize() const;
                [[nodiscard]] size_type capacity() const;
                [[nodiscard]] bool empty() const;

        private:
                friend class DirectedGraphIterator<DirectedGraph>;
                friend class ConstDirectedGraphIterator<DirectedGraph>;
                friend class details::DirectedGraphNode<T, Allocator>;

                using nodesContainerType = std::vector<details::DirectedGraphNode<T, Allocator>>;
                nodesContainerType m_nodes;

                Allocator m_allocator;

                [[nodiscard]] typename nodesContainerType::iterator findNode(const T &nodeValue);
                [[nodiscard]] typename nodesContainerType::const_iterator findNode(const T &nodeValue) const;

                //[[nodiscard]] std::set<T, std::less<>, Allocator>
                // getAdjancentNodesValues(const typename details::DirectedGraphNode<T, Allocator>::adjancncyNodesListType &indicies) const;

                void removeAllLinks(typename nodesContainerType::const_iterator it);

                [[nodiscard]] size_t getIndexOfNode(const typename nodesContainerType::const_iterator &node) const noexcept;
        };

        template <typename T, typename A>
        void swap(DirectedGraph<T, A> &lhs, DirectedGraph<T, A> &rhs) noexcept
        {
                lhs.swap(rhs);
        }

        template <typename T, typename Allocator>
        DirectedGraph<T, Allocator>::DirectedGraph(const Allocator &allocator) noexcept
            : m_nodes{allocator},
              m_allocator{allocator}
        {
        }

        template <typename T, typename Allocator>
        DirectedGraph<T, Allocator>::DirectedGraph(std::initializer_list<T> list, const Allocator &allocator)
            : m_allocator{allocator}
        {
                assign(std::begin(list), std::end(list));
        }

        template <typename T, typename Allocator>
        template <typename Iter>
        DirectedGraph<T, Allocator>::DirectedGraph(Iter first, Iter last, const Allocator &allocator)
            : m_nodes{allocator},
              m_allocator{allocator}
        {
                assign(first, last);
        }

        template <typename T, typename Allocator>
        DirectedGraph<T, Allocator> &
        DirectedGraph<T, Allocator>::operator=(std::initializer_list<T> init)
        {
                DirectedGraph temp{init};
                swap(temp);
                return *this;
        }

        template <typename T, typename Allocator>
        void DirectedGraph<T, Allocator>::assign(std::initializer_list<T> list)
        {
                assign(std::begin(list), std::end(list));
        }

        template <typename T, typename Allocator>
        template <typename Iter>
        void DirectedGraph<T, Allocator>::assign(Iter first, Iter last)
        {
                clear();
                for (auto beg{first}; beg != last; ++beg)
                {
                        insert(*beg);
                }
        }

        template <typename T, typename Allocator>
        typename DirectedGraph<T, Allocator>::allocator_type
        DirectedGraph<T, Allocator>::getAllocator() const
        {
                return m_allocator;
        }

        template <typename T, typename Allocator>
        std::pair<typename DirectedGraph<T, Allocator>::iterator, bool>
        DirectedGraph<T, Allocator>::insert(const T &value)
        {
                T temp{value};
                return insert(std::move(temp));
        }

        template <typename T, typename Allocator>
        std::pair<typename DirectedGraph<T, Allocator>::iterator, bool>
        DirectedGraph<T, Allocator>::insert(T &&value)
        {
                auto iter{findNode(value)};
                if (iter != std::end(m_nodes))
                {
                        return {iterator{iter, *this}, false};
                }

                m_nodes.emplace_back(*this, std::move(value), m_allocator);

                return {iterator{std::prev(std::end(m_nodes)), *this}, true};
        }

        template <typename T, typename Allocator>
        std::pair<typename DirectedGraph<T, Allocator>::iterator, bool>
        DirectedGraph<T, Allocator>::insert(typename DirectedGraph<T, Allocator>::const_iterator pos, const T &value)
        {
                return insert(value);
        }

        template <typename T, typename Allocator>
        std::pair<typename DirectedGraph<T, Allocator>::iterator, bool>
        DirectedGraph<T, Allocator>::insert(typename DirectedGraph<T, Allocator>::const_iterator pos, T &&value)
        {
                return insert(std::move(value));
        }

        template <typename T, typename Allocator>
        typename DirectedGraph<T, Allocator>::iterator
        DirectedGraph<T, Allocator>::erase(typename DirectedGraph<T, Allocator>::const_iterator pos)
        {
                if (pos.m_iterator == std::end(m_nodes))
                {
                        return iterator{std::end(m_nodes), *this};
                }

                removeAllLinks(pos.m_iterator);

                return iterator{m_nodes.erase(pos.m_iterator), *this};
        }

        template <typename T, typename Allocator>
        typename DirectedGraph<T, Allocator>::iterator
        DirectedGraph<T, Allocator>::erase(typename DirectedGraph<T, Allocator>::const_iterator first,
                                           typename DirectedGraph<T, Allocator>::const_iterator last)
        {
                for (auto beg{first}; beg != last; ++beg)
                {
                        if (beg.m_iterator != std::end(m_nodes))
                        {
                                removeAllLinks(beg.m_iterator);
                        }
                }

                return iterator{m_nodes.erase(first, last), *this};
        }

        template <typename T, typename Allocator>
        typename DirectedGraph<T, Allocator>::size_type
        DirectedGraph<T, Allocator>::erase(const T &nodeValue)
        {
                const auto it{findNode(nodeValue)};
                if (it != std::end(m_nodes))
                {
                        removeAllLinks(it);
                        m_nodes.erase(it);
                        return 1;
                }
                return 0;
        }

        template <typename T, typename Allocator>
        void DirectedGraph<T, Allocator>::updateNodeValue(typename DirectedGraph<T, Allocator>::iterator pos,
                                                          const T &newValue)
        {
                auto temp{newValue};
                updateNodeValue(pos, std::move(temp));
        }

        template <typename T, typename Allocator>
        void DirectedGraph<T, Allocator>::updateNodeValue(typename DirectedGraph<T, Allocator>::iterator pos,
                                                          T &&newValue)
        {
                (*pos).value() = std::move(newValue);
        }

        template <typename T, typename Allocator>
        bool DirectedGraph<T, Allocator>::insertEdge(const T &fromNodeValue, const T &toNodeValue)
        {
                auto from{findNode(fromNodeValue)};
                auto to{findNode(toNodeValue)};

                if (from == std::end(m_nodes) || to == std::end(m_nodes))
                {
                        return false;
                }

                const size_t toIndex{getIndexOfNode(to)};
                return from->getAdjancncyNodeList().insert(toIndex).second;
        }

        template <typename T, typename Allocator>
        bool DirectedGraph<T, Allocator>::eraseEdge(const T &fromNodeValue, const T &toNodeValue)
        {
                auto from{findNode(fromNodeValue)};
                auto to{findNode(toNodeValue)};

                if (from == std::end(m_nodes) || to == std::end(m_nodes))
                {
                        return false;
                }

                const size_t toIndex{getIndexOfNode(to)};
                from->getAdjancncyNodeList().erase(toIndex);

                return true;
        }

        template <typename T, typename Allocator>
        void DirectedGraph<T, Allocator>::clear() noexcept
        {
                m_nodes.clear();
        }

        template <typename T, typename Allocator>
        typename DirectedGraph<T, Allocator>::reference
        DirectedGraph<T, Allocator>::operator[](typename DirectedGraph<T, Allocator>::size_type index)
        {
                return m_nodes[index].value();
        }

        template <typename T, typename Allocator>
        typename DirectedGraph<T, Allocator>::const_reference
        DirectedGraph<T, Allocator>::operator[](typename DirectedGraph<T, Allocator>::size_type index) const
        {
                return m_nodes[index].value();
        }

        template <typename T, typename Allocator>
        typename DirectedGraph<T, Allocator>::reference
        DirectedGraph<T, Allocator>::at(typename DirectedGraph<T, Allocator>::size_type index)
        {
                return m_nodes.at(index).value();
        }

        template <typename T, typename Allocator>
        typename DirectedGraph<T, Allocator>::const_reference
        DirectedGraph<T, Allocator>::at(typename DirectedGraph<T, Allocator>::size_type index) const
        {
                return m_nodes.at(index).value();
        }

        template <typename T, typename Allocator>
        template <typename Index, typename Func, typename... Args>
        requires((has_size_type<Index> || std::convertible_to<Index, std::size_t>)&&std::invocable<Func, Index, Args...>) //
            void DirectedGraph<T, Allocator>::dfs(Index startIndex, Func &&fuc, Args &&...args)
        {
                std::stack<std::size_t> stk;
                std::vector<std::int_fast8_t> visted(size(), 0);
                stk.push(startIndex);
                visted[startIndex] = 1;
                while (!stk.empty())
                {
                        size_t topIndex{stk.top()};
                        stk.pop();
                        std::invoke(std::forward<Func>(fuc), topIndex, std::forward<Args>(args)...);

                        const std::set<std::size_t> &topAdjancncyNodeList{m_nodes[topIndex].getAdjancncyNodeList()};
                        std::for_each(std::begin(topAdjancncyNodeList), std::end(topAdjancncyNodeList),
                                      [&stk, &visted](Index i)
                                      {
                                              if (visted[i] == 0)
                                              {
                                                      visted[i] = 1;
                                                      stk.push(i);
                                              }
                                      });
                }
        }

        template <typename T, typename Allocator>
        template <typename Index, typename Func, typename... Args>
        requires((has_size_type<Index> || std::convertible_to<Index, size_t>)&&std::invocable<Func, Index, Args...>) //
            void DirectedGraph<T, Allocator>::bfs(Index startIndex, Func &&fuc, Args &&...args)
        {
                std::queue<std::size_t> que;
                std::vector<std::int_fast8_t> visted(size(), 0);
                que.push(startIndex);
                visted[startIndex] = 1;
                while (!que.empty())
                {
                        size_t topIndex{que.front()};
                        que.pop();
                        std::invoke(std::forward<Func>(fuc), topIndex, std::forward<Args>(args)...);

                        const std::set<std::size_t> &topAdjancncyNodeList{m_nodes[topIndex].getAdjancncyNodeList()};
                        std::for_each(std::begin(topAdjancncyNodeList), std::end(topAdjancncyNodeList),
                                      [&que, &visted](Index i)
                                      {
                                              if (visted[i] == 0)
                                              {
                                                      visted[i] = 1;
                                                      que.push(i);
                                              }
                                      });
                }
        }

        template <typename T, typename Allocator>
        typename DirectedGraph<T, Allocator>::iterator
        DirectedGraph<T, Allocator>::find(const T &nodeValue)
        {
                return iterator{findNode(nodeValue), *this};
        }

        template <typename T, typename Allocator>
        typename DirectedGraph<T, Allocator>::const_iterator
        DirectedGraph<T, Allocator>::find(const T &nodeValue) const
        {
                return const_iterator{findNode(nodeValue), *this};
        }

        template <typename T, typename Allocator>
        bool DirectedGraph<T, Allocator>::contains(const T &nodeValue) const
        {
                return findNode(nodeValue) != std::end(m_nodes);
        }

        template <typename T, typename Allocator>
        typename DirectedGraph<T, Allocator>::iterator
        DirectedGraph<T, Allocator>::begin() noexcept
        {
                return iterator{std::begin(m_nodes), *this};
        }

        template <typename T, typename Allocator>
        typename DirectedGraph<T, Allocator>::iterator
        DirectedGraph<T, Allocator>::end() noexcept
        {
                return iterator{std::end(m_nodes), *this};
        }

        template <typename T, typename Allocator>
        typename DirectedGraph<T, Allocator>::const_iterator
        DirectedGraph<T, Allocator>::begin() const noexcept
        {
                return const_iterator{std::begin(m_nodes), *this};
        }

        template <typename T, typename Allocator>
        typename DirectedGraph<T, Allocator>::const_iterator
        DirectedGraph<T, Allocator>::end() const noexcept
        {
                return const_iterator{std::end(m_nodes), *this};
        }

        template <typename T, typename Allocator>
        typename DirectedGraph<T, Allocator>::const_iterator
        DirectedGraph<T, Allocator>::cbegin() const noexcept
        {
                return begin();
        }

        template <typename T, typename Allocator>
        typename DirectedGraph<T, Allocator>::const_iterator
        DirectedGraph<T, Allocator>::cend() const noexcept
        {
                return end();
        }

        template <typename T, typename Allocator>
        typename DirectedGraph<T, Allocator>::reverse_iterator
        DirectedGraph<T, Allocator>::rbegin() noexcept
        {
                return reverse_iterator{end()};
        }

        template <typename T, typename Allocator>
        typename DirectedGraph<T, Allocator>::reverse_iterator
        DirectedGraph<T, Allocator>::rend() noexcept
        {
                return reverse_iterator{begin()};
        }

        template <typename T, typename Allocator>
        typename DirectedGraph<T, Allocator>::const_reverse_iterator
        DirectedGraph<T, Allocator>::rbegin() const noexcept
        {
                return const_reverse_iterator{end()};
        }

        template <typename T, typename Allocator>
        typename DirectedGraph<T, Allocator>::const_reverse_iterator
        DirectedGraph<T, Allocator>::rend() const noexcept
        {
                return const_reverse_iterator{begin()};
        }

        template <typename T, typename Allocator>
        typename DirectedGraph<T, Allocator>::const_reverse_iterator
        DirectedGraph<T, Allocator>::crbegin() const noexcept
        {
                return rbegin();
        }

        template <typename T, typename Allocator>
        typename DirectedGraph<T, Allocator>::const_reverse_iterator
        DirectedGraph<T, Allocator>::crend() const noexcept
        {
                return rend();
        }

        template <typename T, typename Allocator>
        typename DirectedGraph<T, Allocator>::iterator_adjacent_nodes
        DirectedGraph<T, Allocator>::begin(const T &nodeValue) noexcept
        {
                auto iter{findNode(nodeValue)};
                if (iter != std::end(m_nodes))
                {
                        return iterator_adjacent_nodes{std::begin(iter->getAdjancncyNodeList()), *this};
                }

                return iterator_adjacent_nodes{};
        }

        template <typename T, typename Allocator>
        typename DirectedGraph<T, Allocator>::iterator_adjacent_nodes
        DirectedGraph<T, Allocator>::end(const T &nodeValue) noexcept
        {
                auto iter{findNode(nodeValue)};
                if (iter != std::end(m_nodes))
                {
                        return iterator_adjacent_nodes{std::end(iter->getAdjancncyNodeList()), *this};
                }

                return iterator_adjacent_nodes{};
        }

        template <typename T, typename Allocator>
        typename DirectedGraph<T, Allocator>::const_iterator_adjacent_nodes
        DirectedGraph<T, Allocator>::begin(const T &nodeValue) const noexcept
        {
                auto iter{findNode(nodeValue)};
                if (iter != std::end(m_nodes))
                {
                        return const_iterator_adjacent_nodes{std::begin(iter->getAdjancncyNodeList()), *this};
                }

                return const_iterator_adjacent_nodes{};
        }

        template <typename T, typename Allocator>
        typename DirectedGraph<T, Allocator>::const_iterator_adjacent_nodes
        DirectedGraph<T, Allocator>::end(const T &nodeValue) const noexcept
        {
                auto iter{findNode(nodeValue)};
                if (iter != std::end(m_nodes))
                {
                        return const_iterator_adjacent_nodes{std::end(iter->getAdjancncyNodeList()), *this};
                }

                return const_iterator_adjacent_nodes{};
        }

        template <typename T, typename Allocator>
        typename DirectedGraph<T, Allocator>::const_iterator_adjacent_nodes
        DirectedGraph<T, Allocator>::cbegin(const T &nodeValue) const noexcept
        {
                return begin();
        }

        template <typename T, typename Allocator>
        typename DirectedGraph<T, Allocator>::const_iterator_adjacent_nodes
        DirectedGraph<T, Allocator>::cend(const T &nodeValue) const noexcept
        {
                return end();
        }

        template <typename T, typename Allocator>
        typename DirectedGraph<T, Allocator>::reverse_iterator_adjacent_nodes
        DirectedGraph<T, Allocator>::rbegin(const T &nodeValue) noexcept
        {
                return reverse_iterator_adjacent_nodes{end(nodeValue)};
        }

        template <typename T, typename Allocator>
        typename DirectedGraph<T, Allocator>::reverse_iterator_adjacent_nodes
        DirectedGraph<T, Allocator>::rend(const T &nodeValue) noexcept
        {
                return reverse_iterator_adjacent_nodes{begin(nodeValue)};
        }

        template <typename T, typename Allocator>
        typename DirectedGraph<T, Allocator>::const_reverse_iterator_adjacent_nodes
        DirectedGraph<T, Allocator>::rbegin(const T &nodeValue) const noexcept
        {
                return const_reverse_iterator_adjacent_nodes{end(nodeValue)};
        }

        template <typename T, typename Allocator>
        typename DirectedGraph<T, Allocator>::const_reverse_iterator_adjacent_nodes
        DirectedGraph<T, Allocator>::rend(const T &nodeValue) const noexcept
        {
                return const_reverse_iterator_adjacent_nodes{begin(nodeValue)};
        }

        template <typename T, typename Allocator>
        typename DirectedGraph<T, Allocator>::const_reverse_iterator_adjacent_nodes
        DirectedGraph<T, Allocator>::crbegin(const T &nodeValue) const noexcept
        {
                return rbegin(nodeValue);
        }

        template <typename T, typename Allocator>
        typename DirectedGraph<T, Allocator>::const_reverse_iterator_adjacent_nodes
        DirectedGraph<T, Allocator>::crend(const T &nodeValue) const noexcept
        {
                return rend(nodeValue);
        }

        template <typename T, typename Allocator>
        bool DirectedGraph<T, Allocator>::operator==(const DirectedGraph &rhs) const
        {
                if (this->size() != rhs.size())
                {
                        return false;
                }

                for (auto &node : m_nodes)
                {
                        auto rhsNodeIter{findNode(node.value())};
                        if (rhsNodeIter == std::end(rhs.m_nodes))
                        {
                                return false;
                        }
                        if (node.getAdjancncyNodeList() != rhsNodeIter->getAdjancncyNodeList())
                        {
                                return false;
                        }
                }
                return true;
        }

        template <typename T, typename Allocator>
        bool DirectedGraph<T, Allocator>::operator!=(const DirectedGraph &rhs) const
        {
                return !(*this == rhs);
        }

        template <typename T, typename Allocator>
        void DirectedGraph<T, Allocator>::swap(DirectedGraph &rhs) noexcept
        {
                m_nodes.swap(rhs.m_nodes);
                std::swap(m_allocator, rhs.m_allocator);
        }

        template <typename T, typename Allocator>
        typename DirectedGraph<T, Allocator>::size_type
        DirectedGraph<T, Allocator>::size() const
        {
                return m_nodes.size();
        }

        template <typename T, typename Allocator>
        typename DirectedGraph<T, Allocator>::size_type
        DirectedGraph<T, Allocator>::maxSize() const
        {
                return m_nodes.max_size();
        }

        template <typename T, typename Allocator>
        typename DirectedGraph<T, Allocator>::size_type
        DirectedGraph<T, Allocator>::capacity() const
        {
                return m_nodes.capacity();
        }

        template <typename T, typename Allocator>
        bool DirectedGraph<T, Allocator>::empty() const
        {
                return m_nodes.empty();
        }

        template <typename T, typename Allocator>
        typename DirectedGraph<T, Allocator>::nodesContainerType::iterator
        DirectedGraph<T, Allocator>::findNode(const T &nodeValue)
        {
                return std::find_if(std::begin(m_nodes), std::end(m_nodes),
                                    [&nodeValue](const auto &value)
                                    { return nodeValue == value.value(); });
        }

        template <typename T, typename Allocator>
        typename DirectedGraph<T, Allocator>::nodesContainerType::const_iterator
        DirectedGraph<T, Allocator>::findNode(const T &nodeValue) const
        {
                return const_cast<DirectedGraph<T, Allocator> *>(this)->findNode(nodeValue);
        }

        template <typename T, typename Allocator>
        void DirectedGraph<T, Allocator>::removeAllLinks(typename nodesContainerType::const_iterator it)
        {
                auto index{getIndexOfNode(it)};
                auto toIndex{(*it).getAdjancncyNodeList()};
                std::for_each(std::begin(toIndex), std::end(toIndex),
                              [&index, this](size_t i)
                              {
                                      auto st{m_nodes[i].getAdjancncyNodeList()};
                                      if (auto iter{st.find(index)}; iter != std::end(st))
                                      {
                                              st.erase(iter);
                                      }
                              });
        }

        template <typename T, typename Allocator>
        size_t DirectedGraph<T, Allocator>::getIndexOfNode(const typename nodesContainerType::const_iterator &node) const noexcept
        {
                return static_cast<size_t>(std::distance(std::cbegin(m_nodes), node));
        }
} // namespace dgn
#endif // DIRECTEDGRAPH_DIRECTEDGRAPH_HPP
