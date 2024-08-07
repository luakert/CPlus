module;

#include <cstddef>

export module directed_cust_graph;

export import directed_cust_graph.adjacent_nodes_iterator;
export import directed_cust_graph.const_adjacent_nodes_iterator;
export import directed_cust_graph.directed_graph_iterator;
export import directed_cust_graph.const_directed_graph_iterator;
export import directed_cust_graph.graph_cust_node;
import <vector>;
import <iterator>;
import <utility>;
import <algorithm>;
import <memory>;
import <set>;

export namespace ProCustCpp
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

		using iterator = const_directed_graph_iterator<directed_cust_graph>;
		using const_iterator = const_directed_graph_iterator<directed_cust_graph>;
		using reverse_iterator = std::reverse_iterator<iterator>;
		using const_reverse_iterator = std::reverse_iterator<const_iterator>;

		using iterator_adjacent_nodes = adjacent_nodes_iterator<directed_cust_graph>;
		using const_iterator_adjacent_nodes = const_adjacent_nodes_iterator<directed_cust_graph>;
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

        		// Returns true if the edge was successfully created, false otherwise.
		bool insert_edge(const T& from_node_value, const T& to_node_value);

		// Returns true if the given edge was erased, false otherwise.
		bool erase_edge(const T& from_node_value, const T& to_node_value);

		// Removes all nodes from the graph.
		void clear() noexcept;

		// Returns a reference to the node with given index.
		// No bounds checking is done.
		reference operator[](size_type index);
		const_reference operator[](size_type index) const;

		reference at(size_type index);
		const_reference at(size_type index) const;

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

        bool operator==(const directed_cust_graph& rhs) const;
		bool operator!=(const directed_cust_graph& rhs) const;

		// Swaps all nodes between this graph and the given graph.
		void swap(directed_cust_graph& other_graph) noexcept;

		// Returns the number of nodes in the graph.
		[[nodiscard]] size_type size() const noexcept;
		[[nodiscard]] size_type max_size() const noexcept;
		[[nodiscard]] bool empty() const noexcept;

    private:
        friend class directed_graph_iterator<directed_cust_graph>;
        friend class const_directed_graph_iterator<directed_cust_graph>;

        using nodes_container_type = std::vector<details::graph_cust_node<T>>;

        void remove_all_links_to(typename nodes_container_type::const_iterator node_iter);

        nodes_container_type m_nodes;
        [[nodiscard]] typename nodes_container_type::iterator findNode(const T& node_value);
		[[nodiscard]] typename nodes_container_type::const_iterator findNode(const T& node_value) const;
        [[nodiscard]] std::set<T> get_adjacent_nodes_values(const typename details::graph_cust_node<T>::adjacency_list_type& indices) const;
        [[nodiscard]] size_t get_index_of_node(const typename nodes_container_type::const_iterator& node) const noexcept;
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

        m_nodes.emplace_back(this, std::move(node_value));
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
            auto& adjacencyIndices{ node.get_adjacent_nodes_indices() };
            adjacencyIndices.erase(node_index);
            std::vector<size_t> indices(std::begin(adjacencyIndices), std::end(adjacencyIndices));
            std::for_each(std::begin(indices), std::end(indices),
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
	size_t directed_cust_graph<T>::get_index_of_node(const typename nodes_container_type::const_iterator& node) const noexcept
	{
		const auto index{ std::distance(std::cbegin(m_nodes), node) };
		return static_cast<size_t>(index);
	}

	template<typename T>
	bool directed_cust_graph<T>::insert_edge(const T& from_node_value, const T& to_node_value)
	{
		const auto from{ findNode(from_node_value) };
		const auto to{ findNode(to_node_value) };
		if (from == std::end(m_nodes) || to == std::end(m_nodes))
		{
			return false;
		}

		const size_t to_index{ get_index_of_node(to) };
		return from->get_adjacent_nodes_indices().insert(to_index).second;
	}

    template<typename T>
	typename directed_cust_graph<T>::nodes_container_type::iterator
		directed_cust_graph<T>::findNode(const T& node_value)
	{
		return std::find_if(std::begin(m_nodes), std::end(m_nodes),
			[&node_value](const auto& node) { return node.value() == node_value; });
	}

	template<typename T>
	typename directed_cust_graph<T>::nodes_container_type::const_iterator
		directed_cust_graph<T>::findNode(const T& node_value) const
	{
		return const_cast<directed_cust_graph<T>*>(this)->findNode(node_value);
	}

    	template<typename T>
	typename directed_cust_graph<T>::reference
		directed_cust_graph<T>::operator[](size_type index)
	{
		return m_nodes[index].value();
	}

	template<typename T>
	typename directed_cust_graph<T>::const_reference
		directed_cust_graph<T>::operator[](size_type index) const
	{
		return m_nodes[index].value();
	}

    	template<typename T>
	typename directed_cust_graph<T>::reference
		directed_cust_graph<T>::at(size_type index)
	{
		return m_nodes.at(index).value();
	}

	template<typename T>
	typename directed_cust_graph<T>::const_reference
		directed_cust_graph<T>::at(size_type index) const
	{
		return m_nodes.at(index).value();
	}

    template<typename T>
	std::set<T> directed_cust_graph<T>::get_adjacent_nodes_values(
		const typename details::graph_cust_node<T>::adjacency_list_type& indices) const
	{
		std::set<T> values;
		for (auto&& index : indices)
		{
			values.insert(m_nodes[index].value());
		}
		return values;
	}


	template<typename T>
	bool directed_cust_graph<T>::operator==(const directed_cust_graph& rhs) const
	{
		if (m_nodes.size() != rhs.m_nodes.size()) { return false; }

		for (auto&& node : m_nodes)
		{
			const auto rhsNodeIter{ rhs.findNode(node.value()) };
			if (rhsNodeIter == std::end(rhs.m_nodes))
			{
				return false;
			}
			const auto adjacent_values_lhs{ get_adjacent_nodes_values(node.get_adjacent_nodes_indices()) };
			const auto adjacent_values_rhs{ rhs.get_adjacent_nodes_values(rhsNodeIter->get_adjacent_nodes_indices()) };
			if (adjacent_values_lhs != adjacent_values_rhs)
			{
				return false;
			}
		}
		return true;
	}

	template<typename T>
	bool directed_cust_graph<T>::operator!=(const directed_cust_graph& rhs) const
	{
		return !(*this == rhs);
	}

    template<typename T>
	void directed_cust_graph<T>::swap(directed_cust_graph& other_graph) noexcept
	{
		m_nodes.swap(other_graph.m_nodes);
	}

	template<typename T>
	typename directed_cust_graph<T>::size_type directed_cust_graph<T>::size() const noexcept
	{
		return m_nodes.size();
	}

	template<typename T>
	typename directed_cust_graph<T>::size_type directed_cust_graph<T>::max_size() const noexcept
	{
		return m_nodes.max_size();
	}

	template<typename T>
	bool directed_cust_graph<T>::empty() const noexcept
	{
		return m_nodes.empty();
	}

	template<typename T>
	bool directed_cust_graph<T>::erase_edge(const T& from_node_value, const T& to_node_value)
	{
		const auto from{ findNode(from_node_value) };
		const auto to{ findNode(to_node_value) };
		if (from == std::end(m_nodes) || to == std::end(m_nodes))
		{
			return false; // nothing to erase
		}

		const size_t to_index{ get_index_of_node(to) };
		from->get_adjacent_nodes_indices().erase(to_index);
		return true;
	}

   	template<typename T>
	void directed_cust_graph<T>::clear() noexcept
	{
		m_nodes.clear();
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
