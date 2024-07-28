module;

#include <cstddef>

export module directed_cust_graph.directed_graph_iterator;

import directed_cust_graph.const_directed_graph_iterator;
import <iterator>;


export namespace ProCustCpp
{
    template<typename DirectedGraph>
    class directed_graph_iterator : public const_directed_graph_iterator<DirectedGraph>
    {
    public:
        using value_type = typename  DirectedGraph::value_type;
        using difference_type = ptrdiff_t;
        using iterator_category = std::bidirectional_iterator_tag;
        using pointer = const value_type*;
        using reference = const value_type&;
        using iterator_type = typename DirectedGraph::nodes_container_type::const_iterator;
        
        directed_graph_iterator() = default;
        directed_graph_iterator(iterator_type it, const DirectedGraph* graph);

        reference operator*();
        pointer operator->();
        
        directed_graph_iterator& operator++();
        directed_graph_iterator  operator++(int);

        directed_graph_iterator& operator--();
        directed_graph_iterator  operator--(int);
    };
    
    template<typename DirectedGraph>
    directed_graph_iterator<DirectedGraph>::directed_graph_iterator(iterator_type it, const DirectedGraph* graph)
        :const_directed_graph_iterator<DirectedGraph>{it, graph}{}


    template<typename DirectedGraph>
    typename directed_graph_iterator<DirectedGraph>::reference directed_graph_iterator<DirectedGraph>::operator*()
    {
        return const_cast<reference>(this->m_nodeIterator->value());
    }

    template<typename DirectedGraph>
    typename directed_graph_iterator<DirectedGraph>::pointer directed_graph_iterator<DirectedGraph>::operator->()
    {
        return const_cast<pointer>(&(this->m_nodeIterator->value()));
    }

    template<typename DirectedGraph>
    directed_graph_iterator<DirectedGraph>& directed_graph_iterator<DirectedGraph>::operator++()
    {
        this->increment();
        return *this;
    }

    template<typename DirectedGraph>
    directed_graph_iterator<DirectedGraph> directed_graph_iterator<DirectedGraph>::operator++(int)
    {
        auto oldIt{ *this };
        this->increment();
        return oldIt;
    }

    	// Defer the details to the decrement() helper in the base class.
	template<typename DirectedGraph>
	directed_graph_iterator<DirectedGraph>&
		directed_graph_iterator<DirectedGraph>::operator--()
	{
		this->decrement();
		return *this;
	}

	// Defer the details to the decrement() helper in the base class.
	template<typename DirectedGraph>
	directed_graph_iterator<DirectedGraph>
		directed_graph_iterator<DirectedGraph>::operator--(int)
	{
		auto oldIt{ *this };
		this->decrement();
		return oldIt;
	}


}