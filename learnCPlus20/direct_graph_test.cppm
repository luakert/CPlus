module;

#include <cstddef>

export module directed_cust_graph;

import directed_cust_graph.directed_graph_iterator;
import directed_cust_graph.const_directed_graph_iterator;
import directed_cust_graph.graph_node;

import <vector>;
import <iterator>;
import <utility>;
import <algorithm>;
import <memory>;
import <set>;
import <pair>;

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
   		reverse_iterator rbegin() noexcept;
		reverse_iterator rend() noexcept;
		const_reverse_iterator rbegin() const noexcept;
		const_reverse_iterator rend() const noexcept;
		const_reverse_iterator crbegin() const noexcept;
		const_reverse_iterator crend() const noexcept;


        std::pair<iterator, bool> insert(const T& node_value);
        std::pair<iterator, bool> insert(T&& node_value);
        iterator insert(const_iterator hint, const T& node_value);
		iterator insert(const_iterator hint, T&& node_value);

        template<typename Iter>
        void insert(Iter first, Iter last);

        iterator erase(const_iterator pos);
        iterator erase(const_iterator first, const_iterator last);

        iterator_adjacent_nodes begin(const T& node_value) noexcept;
		iterator_adjacent_nodes end(const T& node_value) noexcept;
		const_iterator_adjacent_nodes begin(const T& node_value) const noexcept;
		const_iterator_adjacent_nodes end(const T& node_value) const noexcept;
		const_iterator_adjacent_nodes cbegin(const T& node_value) const noexcept;
		const_iterator_adjacent_nodes cend(const T& node_value) const noexcept;


        reverse_iterator_adjacent_nodes rbegin(const T& node_value) noexcept;
		reverse_iterator_adjacent_nodes rend(const T& node_value) noexcept;
		const_reverse_iterator_adjacent_nodes rbegin(const T& node_value) const noexcept;
		const_reverse_iterator_adjacent_nodes rend(const T& node_value) const noexcept;
		const_reverse_iterator_adjacent_nodes crbegin(const T& node_value) const noexcept;
		const_reverse_iterator_adjacent_nodes crend(const T& node_value) const noexcept;

    private:
        friend class directed_graph_iterator<directed_cust_graph>;
        friend class const_directed_graph_iterator<directed_cust_graph>;

        using nodes_container_type = std::vector<details::graph_node<T>>;

        void remove_all_links_to(typename nodes_container_type::const_iterator node_iter);

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

    template<typename T>
	typename directed_cust_graph<T>::reverse_iterator
		directed_cust_graph<T>::rbegin() noexcept
	{
		return reverse_iterator{ end() };
	}

	template<typename T>
	typename directed_cust_graph<T>::reverse_iterator
		directed_cust_graph<T>::rend() noexcept
	{
		return reverse_iterator{ begin() };
	}

	template<typename T>
	typename directed_cust_graph<T>::const_reverse_iterator
		directed_cust_graph<T>::rbegin() const noexcept
	{
		return const_reverse_iterator{ end() };
	}

	template<typename T>
	typename directed_cust_graph<T>::const_reverse_iterator
		directed_cust_graph<T>::rend() const noexcept
	{
		return const_reverse_iterator{ begin() };
	}

	template<typename T>
	typename directed_cust_graph<T>::const_reverse_iterator
		directed_cust_graph<T>::crbegin() const noexcept
	{
		return rbegin();
	}

	template<typename T>
	typename directed_cust_graph<T>::const_reverse_iterator
		directed_cust_graph<T>::crend() const noexcept
	{
		return rend();
	}

    template<typename T>
    std::pair<typename directed_cust_graph<T>::iterator, bool> directed_cust_graph<T>::insert(const T& node_value)
    {
        T copy{ node_value };
        return insert(std::move(copy));
    }


    template<typename T>
    std::pair<typename directed_cust_graph<T>::iterator, bool> directed_cust_graph<T>::insert(T&& node_value)
    {
        auto iter{ findNode(node_value) };
        if (iter != std::end(m_nodes))
        {
            return { iterator{iter, this}, false };
        }

        m_nodes.emplace_back(this, std::movd(node_value));
        return { iterator{--std::end(m_nodes), this}, true };
    }

    template<typename T>
	typename directed_cust_graph<T>::iterator directed_cust_graph<T>::insert(const_iterator hint, const T& node_value)
	{
		// Ignore the hint, just forward to another insert().
		return insert(node_value).first;
	}

	template<typename T>
	typename directed_cust_graph<T>::iterator directed_cust_graph<T>::insert(const_iterator hint, T&& node_value)
	{
		// Ignore the hint, just forward to another insert().
		return insert(std::move(node_value)).first;
	}

    template<typename T>
    typename directed_cust_graph<T>::iterator directed_cust_graph<T>::erase(const_iterator pos)
    {
        if (pos.m_nodeIterator == std::end(m_nodes))
        {
            return iterator{ std::end(m_nodes), this };
        }
        remove_all_links_to(pos.m_nodeIterator);
        return iterator{ m_nodes.erase(pos.m_nodeIterator), this };
    }

    template<typename T>
    typename directed_cust_graph<T>::iterator directed_cust_graph<T>::erase(const_iterator first, const_iterator last)
    {
        for (auto iter{first}; iter!= last; ++iter)
        {
            if (iter.m_nodeIterator != std::end(m_nodes))
            {
                remove_all_links_to(iter.m_nodeIterator);
            }
        }

        return iterator{ m_nodes.erase(first.m_nodeIterator, last.m_nodeIterator), this };
    }



    template<typename T>
    void directed_cust_graph<T>::remove_all_links_to(typename nodes_container_type::const_iterator node_iter)
    {
        const size_t node_index{ get_index_of_node(node_iter) };
        for (auto&& node : m_nodes)
        {
            auto& adjacencyIndices{ nodes.get_adjacent_nodes_indices() };
            adjacencyIndices.erase(node_index);
            std::vector<size_t> indices(std::begin(adjacencyIndices), std::end(adjacencyIndices));
            std::for_each(std::begin(index), std::end(indices),
                [node_index](size_t& index) {
                    if (index > node_index)
                    {
                        --index;
                    }
                }
            );
            adjacencyIndices.clear();
            adjacencyIndices.insert(std::begin(indices), std::end(indices));
        }
    }


    template<typename T>
    template<typename Iter>
    void directed_cust_graph<T>::insert(Iter first, Iter last)
    {
        std::copy(first, last, std::insert_iterator{ *this, begin() });
    }

    
	template<typename T>
	typename directed_cust_graph<T>::iterator_adjacent_nodes
		directed_cust_graph<T>::begin(const T& node_value) noexcept
	{
		auto iter{ findNode(node_value) };
		if (iter == std::end(m_nodes))
		{
			// Return a default constructed end iterator.
			return iterator_adjacent_nodes{};
		}
		return iterator_adjacent_nodes{ std::begin(iter->get_adjacent_nodes_indices()), this };
	}

	template<typename T>
	typename directed_cust_graph<T>::iterator_adjacent_nodes
		directed_cust_graph<T>::end(const T& node_value) noexcept
	{
		auto iter{ findNode(node_value) };
		if (iter == std::end(m_nodes))
		{
			// Return a default constructed end iterator.
			return iterator_adjacent_nodes{};
		}
		return iterator_adjacent_nodes{ std::end(iter->get_adjacent_nodes_indices()), this };
	}

	template<typename T>
	typename directed_cust_graph<T>::const_iterator_adjacent_nodes
		directed_cust_graph<T>::cbegin(const T& node_value) const noexcept
	{
		auto iter{ findNode(node_value) };
		if (iter == std::end(m_nodes))
		{
			// Return a default constructed end iterator.
			return const_iterator_adjacent_nodes{};
		}
		return const_iterator_adjacent_nodes{ std::cbegin(iter->get_adjacent_nodes_indices()), this };
	}

	template<typename T>
	typename directed_cust_graph<T>::const_iterator_adjacent_nodes
		directed_cust_graph<T>::cend(const T& node_value) const noexcept
	{
		auto iter{ findNode(node_value) };
		if (iter == std::end(m_nodes))
		{
			// Return a default constructed end iterator.
			return const_iterator_adjacent_nodes{};
		}
		return const_iterator_adjacent_nodes{ std::cend(iter->get_adjacent_nodes_indices()), this };
	}

	template<typename T>
	typename directed_cust_graph<T>::const_iterator_adjacent_nodes
		directed_cust_graph<T>::begin(const T& node_value) const noexcept
	{
		return cbegin(node_value);
	}

	template<typename T>
	typename directed_cust_graph<T>::const_iterator_adjacent_nodes
		directed_cust_graph<T>::end(const T& node_value) const noexcept
	{
		return cend(node_value);
	}


	template<typename T>
	typename directed_cust_graph<T>::reverse_iterator_adjacent_nodes
		directed_cust_graph<T>::rbegin(const T& node_value) noexcept
	{
		return reverse_iterator_adjacent_nodes{ end(node_value) };
	}

	template<typename T>
	typename directed_cust_graph<T>::reverse_iterator_adjacent_nodes
		directed_cust_graph<T>::rend(const T& node_value) noexcept
	{
		return reverse_iterator_adjacent_nodes{ begin(node_value) };
	}

	template<typename T>
	typename directed_cust_graph<T>::const_reverse_iterator_adjacent_nodes
		directed_cust_graph<T>::rbegin(const T& node_value) const noexcept
	{
		return const_reverse_iterator_adjacent_nodes{ end(node_value) };
	}

	template<typename T>
	typename directed_cust_graph<T>::const_reverse_iterator_adjacent_nodes
		directed_cust_graph<T>::rend(const T& node_value) const noexcept
	{
		return const_reverse_iterator_adjacent_nodes{ begin(node_value) };
	}

	template<typename T>
	typename directed_cust_graph<T>::const_reverse_iterator_adjacent_nodes
		directed_cust_graph<T>::crbegin(const T& node_value) const noexcept
	{
		return rbegin(node_value);
	}

	template<typename T>
	typename directed_cust_graph<T>::const_reverse_iterator_adjacent_nodes
		directed_cust_graph<T>::crend(const T& node_value) const noexcept
	{
		return rend(node_value);
	}



}
