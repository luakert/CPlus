module;

#include <cstddef>

export module directed_cust_graph;

import directed_cust_graph.directed_graph_iterator;
import directed_cust_graph.const_directed_graph_iterator;

import <vector>;
import <iterator>;
import <utility>;
import <algorithm>;
import <memory>;
import <set>;

namespace ProCustCpp
{
    export template<typename T>
    class directed_cust_graph
    {
    public:
        using value_type = T;
		using reference = value_type&;
		using const_reference = const value_type&;
		using size_type = size_t;
		using difference_type = ptrdiff_t;

		using iterator = const_directed_graph_iterator<directed_graph>;
		using const_iterator = const_directed_graph_iterator<directed_graph>;
		using reverse_iterator = std::reverse_iterator<iterator>;
		using const_reverse_iterator = std::reverse_iterator<const_iterator>;

		using iterator_adjacent_nodes = adjacent_nodes_iterator<directed_graph>;
		using const_iterator_adjacent_nodes = const_adjacent_nodes_iterator<directed_graph>;
		using reverse_iterator_adjacent_nodes = std::reverse_iterator<iterator_adjacent_nodes>;
		using const_reverse_iterator_adjacent_nodes = std::reverse_iterator<const_iterator_adjacent_nodes>;

        iterator begin() noexcept;
        iterator end() noexcept;

        const_iterator begin() const noexcept;
        const_iterator end() const noexcept;
        const_iterator cbegin() const noexcept;
        const_iterator cend() const noexcept;

    private:
        friend class directed_graph_iterator<directed_cust_graph>;
        friend class const_directed_graph_iterator<directed_cust_graph>;

        using nodes_container_type = std::vector<details::graph_node<T>>;

        nodes_container_type m_nodes;
    };

    template<typename T>
    typename directed_cust_graph<T>::iterator directed_cust_graph<T>::begin() noexcept
    {
        return iterator{ std::begin(m_nodes), this };
    }

    template<typename T>
    typename directed_cust_graph<T>::iterator directed_cust_graph<T>::end() noexcept
    {
        return iterator{ std::end(m_nodes), this };
    }

    template<typename T>
    typename directed_cust_graph<T>::const_iterator directed_cust_graph<T>::begin() const noexcept
    {
        return const_cast<directed_cust_graph*>(this)->begin();
    }

    template<typename T>
    typename directed_cust_graph<T>::const_iterator directed_cust_graph<T>::end() const noexcept
    {
        return const_cast<directed_cust_graph*> (this)->end();
    }

    template<typename T>
    typename directed_cust_graph<T>::const_iterator directed_cust_graph<T>::cbegin() const noexcept
    {
        return begin();
    }

    template<typename T>
    typename directed_cust_graph<T>::const_iterator directed_cust_graph<T>::cend() const noexcept
    {
        return end();
    }


}
