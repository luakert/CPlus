module;

#include <cstddef>

export module directed_cust_graph:const_directed_graph_iterator;

import <iterator>;

namespace ProCustCpp
{
    template<typename T>
    class directed_cust_graph;

    template<typename DirectedGraph>
    class const_directed_graph_iterator
    {
        public:
            using value_type = typename  DirectedGraph::value_type;
            using difference_type = ptrdiff_t;
            using iterator_category = std::bidirectional_iterator_tag;
            using pointer = const value_type*;
            using reference = const value_type&;
            using iterator_type = typename DirectedGraph::nodes_container_type::const_iterator;

            const_directed_graph_iterator() = default;
            const_directed_graph_iterator(iterator_type it, const DirectedGraph* graph);

            reference operator*() const;
            pointer operator->() const;
            const_directed_graph_iterator& operator++(); // Prefix
            const_directed_graph_iterator operator++(int); // Postfix
            const_directed_graph_iterator& operator--();
            const_directed_graph_iterator operator--(int);

            bool opeartor == (const const_directed_graph_iterator&) const = default;
        protected:
            friend class directed_graph<value_type>;
            iterator_type m_nodeIterator;
            const DirectedGraph* m_graph{ nullptr };
            void increment();
            void decrement();
    };

    template<typename DirectedGraph>
    const_directed_graph_iterator<DirectedGraph>::const_directed_graph_iterator(iterator_type it,
        const DirectedGraph* graph):m_nodeIterator{it}, m_graph{graph} { }

    template<typename DirectedGraph>
    typename const_directed_graph_iterator<DirectedGraph>::reference const_directed_graph_iterator<DirectedGraph>::operator*() const
    {
        return m_nodeIterator->value();
    }

    template<typename DirectedGraph>
    typename const_directed_graph_iterator<DirectedGraph>::pointer const_directed_graph_iterator<DirectedGraph>::operator->() const
    {
        return &(m_nodeIterator->value());
    }

    template<typename DirectedGraph>
    const_directed_graph_iterator<DirectedGraph>& const_directed_graph_iterator<DirectedGraph>::operator++()
    {
        increment();
        return *this;
    }

    template<typename DirectedGraph>
    const_directed_graph_iterator<DirectedGraph> const_directed_graph_iterator<DirectedGraph>::operator++(int)
    {
        auto oldIt{ *this };
        increment();
        return oldIt;
    }

    template<typename DirectedGraph>
    const_directed_graph_iterator<DirectedGraph>& const_directed_graph_iterator<DirectedGraph>::operator--()
    {
        decrement();
        return *this;
    }


    template<typename DirectedGraph>
    const_directed_graph_iterator<DirectedGraph> const_directed_graph_iterator<DirectedGraph>::operator--(int)
    {
        auto oldIt{ *this };
        decrement();
        return oldIt;
    }

    template<typename DirectedGraph>
    void const_directed_graph_iterator<DirectedGraph>::increment()
    {
        ++m_nodeIterator;
    }

    template<typename DirectedGraph>
    void const_directed_graph_iterator<DirectedGraph>::decrement()
    {
        --m_nodeIterator;
    }
}
