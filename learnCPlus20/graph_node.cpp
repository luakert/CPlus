module;

#include <cstdlib>

export module directed_graph.node;

import <set>;

namespace ProCpp
{
    template<typename T>
    class directed_graph;
namespace details
{

    export template<typename T>
    class graph_node
    {
    private:
        friend class directed_graph<T>;
        directed_graph<T>* m_graph;

        using adjacency_list_type = std::set<size_t>;
        [[nodiscard]] adjacency_list_type& get_adjacent_nodes_indices();
        [[nodiscard]] const adjacency_list_type& get_adjacent_nodes_indices() const;

        T m_data;
        adjacency_list_type m_adjacentNodeIndices;
    public:
        graph_node(directed_graph<T>* graph, const T& t);
        graph_node(directed_graph<T>* graph, T&& t);

        [[nodiscard]] T& value() noexcept;
        [[nodiscard]] const T& value() const noexcept;

        bool operator==(const graph_node&) const = default;
    };

    template<typename T>
    graph_node<T>::graph_node(directed_graph<T>* graph, const T& t) :m_graph{graph}, m_data{t}
    {

    }

    template<typename T>
    graph_node<T>::graph_node(directed_graph<T>* graph, T&& t) :m_graph{graph}, m_data{std::move(t)} {}

    template<typename T>
    T& graph_node<T>::value()noexcept { return m_data; }

    template<typename T>
    const T& graph_node<T>::value()const noexcept { return m_data; }

    template<typename T>
    typename graph_node<T>::adjacency_list_type& graph_node<T>::get_adjacent_nodes_indices()
    {
        return m_adjacentNodeIndices;
    }

    template<typename T>
    const typename graph_node<T>::adjacency_list_type& graph_node<T>::get_adjacent_nodes_indices() const
    {
        return m_adjacentNodeIndices;
    }

    }
}