module;

#include <cstddef>

export module directed_cust_graph_cust;
import directed_cust_graph.node;
import <vector>;
import <utility>;
import <set>;
import <algorithm>;

namespace ProCustCpp
{
    export template<typename T>
    class directed_cust_graph
    {
    public:
        bool insert(const T& node_value);
        bool insert(T&& node_value);

        bool erase(const T& node_value);

        bool insert_edge(const T& from_node_value, const T& to_node_value);

        bool erase_edge(const T& from_node_value, const T& to_node_value);

        void clear() noexcept;

        T& operator[](size_t index);
        const T& operator[](size_t index) const;

        bool operator==(const directed_cust_graph& rhs) const;
        bool operator!=(const directed_cust_graph& rhs) const;

        void swap(directed_cust_graph& other_graph) noexcept;
        [[nodiscard]] size_t size() const noexcept;

        [[nodiscard]] std::set<T> get_adjacent_nodes_values(const T& node_value) const;
    private:
        friend details::graph_node<T>;
        friend class const_directed_graph_iterator<directed_cust_graph>;
        using nodes_container_type = std::vector<details::graph_node<T>>;
        nodes_container_type m_nodes;

        typename nodes_container_type::iterator findNode(const T& node_value);
        typename nodes_container_type::const_iterator findNode(const T& node_value) const;
        std::size_t get_index_of_node(const typename nodes_container_type::const_iterator& node) const noexcept;
        void remove_all_link_to(typename nodes_container_type::const_iterator node_first);
        [[nodiscard]] std::set<T> get_adjacent_nodes_values(const typename details::graph_node<T>::adjacency_list_type& indices) const;
    };

    template<typename T>
    typename directed_cust_graph<T>::nodes_container_type::iterator directed_cust_graph<T>::findNode(const T& node_value)
    {
        return std::find_if(std::begin(m_nodes), std::end(m_nodes), [&node_value](const auto& node) {
            return node.value() == node_value;
            });
    }

    template<typename T>
    typename directed_cust_graph<T>::nodes_container_type::const_iterator directed_cust_graph<T>::findNode(const T& node_value) const
    {
        return const_cast<directed_cust_graph<T>*>(this)->findNode(node_value);
    }

    template<typename T>
    bool directed_cust_graph<T>::insert(T&& node_value)
    {
        auto iter{ findNode(node_value) };
        if (iter != std::end(m_nodes))
        {
            return false;
        }

        m_nodes.emplace_back(this, std::move(node_value));
        return true;
    }

    template<typename T>
    bool directed_cust_graph<T>::insert(const T& node_value)
    {
        T copy{ node_value };
        return insert(std::move(copy));
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
    size_t directed_cust_graph<T>::get_index_of_node(const typename nodes_container_type::const_iterator& node) const noexcept
    {
        const auto index{ std::distance(std::cbegin(m_nodes), node) };
        return static_cast<size_t>(index);
    }

    template<typename T>
    void directed_cust_graph<T>::remove_all_link_to(typename nodes_container_type::const_iterator node_iter)
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
    bool directed_cust_graph<T>::erase(const T& node_value)
    {
        auto iter{ findNode(node_value) };
        if (iter == std::end(m_nodes))
        {
            return false;
        }

        remove_all_link_to(iter);
        m_nodes.erase(iter);
        return true;
    }

    template<typename T>
    bool directed_cust_graph<T>::erase_edge(const T& from_node_value, const T& to_node_value)
    {
        const auto from{ findNode(from_node_value) };
        const auto to{ findNode(to_node_value) };
        const auto endIter{ std::end(m_nodes) };
        if (from == endIter || to == endIter)
        {
            return false;
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
    void  directed_cust_graph<T>::swap(directed_cust_graph& other) noexcept
    {
        m_nodes.swap(other.m_nodes);
    }

    export template<typename T>
        void swap(directed_cust_graph<T>& first, directed_cust_graph<T>& second)
    {
        first.swap(second);
    }

    template<typename T>
    T& directed_cust_graph<T>::operator[](size_t index)
    {
        return m_nodes[index].value();
    }

    template<typename T>
    const T& directed_cust_graph<T>::operator[](size_t index) const
    {
        return m_nodes[index].value();
    }

    template<typename T>
    bool directed_cust_graph<T>::operator==(const directed_cust_graph& rhs)const
    {
        if (m_nodes.size() != rhs.m_nodes.size())
        {
            return false;
        }

        for (auto&& node : m_nodes)
        {
            const auto rhsNodeIter{ rhs.findNode(node.value()) };
            if (rhsNodeIter == std::end(m_nodes))
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
    std::set<T> directed_cust_graph<T>::get_adjacent_nodes_values(const typename details::graph_node<T>::adjacency_list_type& indices) const
    {
        std::set<T> values;
        for (auto&& index : indices)
        {
            values.insert(m_nodes[index].value());
        }
        return values;
    }

    template<typename T>
    std::set<T> directed_cust_graph<T>::get_adjacent_nodes_values(const T& node_value) const
    {
        auto iter{ findNode(node_value) };
        if (iter == std::end(m_nodes))
        {
            return std::set<T>{};
        }

        return get_adjacent_nodes_values(iter->get_adjacent_nodes_indices());
    }

   
    template<typename T>
    bool directed_cust_graph<T>::operator!=(const directed_cust_graph& rhs) const
    {
        return !(*this == rhs);
    }


    template<typename T>
    size_t directed_cust_graph<T>::size() const noexcept
    {
        return m_nodes.size();
    }

}
