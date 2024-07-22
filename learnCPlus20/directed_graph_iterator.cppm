module;

#include <cstddef>

export module directed_cust_graph.directed_graph_iterator;

import directed_cust_graph.const_directed_graph_iterator;
import <iterator>;


namespace ProCustCpp
{
    template<typename DirectedGraph>
    class direct_graph_iterator : public const_directed_graph<DirectedGraph>
    {
    public:
        using value_type = typename  DirectedGraph::value_type;
        using difference_type = ptrdiff_t;
        using iterator_category = std::bidirectional_iterator_tag;
        using pointer = const value_type*;
        using reference = const value_type&;
        using iterator_type = typename DirectedGraph::nodes_container_type::const_iterator;
        
        direct_graph_iterator() = default;
        direct_graph_iterator(iterator_type it, const DirectedGraph* graph);

        reference operator*();
        pointer operator->();
        
        direct_graph_iterator& operator++();
        direct_graph_iterator  operator++(int);

        direct_graph_iterator& operator--();
        direct_graph_iterator  operator--(int);
    };
    
    template<typename DirectedGraph>
    direct_graph_iterator<DirectedGraph>::direct_graph_iterator(iterator_type it, const DirectedGraph* graph)
        :const_directed_graph_iterator<DirectedGraph>{it, graph}{}


    template<typename DirectedGraph>
    typename direct_graph_iterator<DirectedGraph>::reference direct_graph_iterator<DirectedGraph>::operator*()
    {
        return const_cast<reference>(this->m_nodeIterator->value());
    }

    template<typename DirectedGraph>
    typename direct_graph_iterator<DirectedGraph>::pointer direct_graph_iterator<DirectedGraph>::operator->()
    {
        return const_cast<pointer>(&(this->m_nodeIterator->value()));
    }

    template<typename DirectedGraph>
    direct_graph_iterator<DirectedGraph>& direct_graph_iterator<DirectedGraph>::operator++()
    {
        this->increment();
        return this*;
    }

    template<typename DirectedGraph>
    direct_graph_iterator<DirectedGraph> direct_graph_iterator<DirectedGraph>::operator++(int)
    {
        auto oldIt{ *this };
        this->increment();
        return oldIt;
    }


}