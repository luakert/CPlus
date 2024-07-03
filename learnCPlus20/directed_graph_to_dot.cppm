module;

#include <cstddef>

export module directed_graph.to_dot;

import directed_graph;
import <string>;
import <string_view>;
import <sstream>;
import <iostream>;
import <format>;

namespace ProCpp
{
    	// Returns a given graph in DOT format.
	export template <typename T>
	std::wstring to_dot(const directed_graph<T>& graph, std::wstring_view graph_name)
	{
        std::wstringstream stringstream;

		stringstream << std::format(L"digraph {} {{", graph_name.data()) << std::endl;
		for (size_t index{ 0 }; index < graph.size(); ++index)
		{
			const auto& node_value{ graph[index] };
			const auto adjacent_nodes{ graph.get_adjacent_nodes_values(node_value) };
			if (adjacent_nodes.empty())
			{
				stringstream << node_value << std::endl;
			}
			else
			{
				for (auto&& node : adjacent_nodes)
				{
					stringstream << std::format(L"{} -> {}", node_value, node) << std::endl;
				}
			}
		}
		stringstream << "}" << std::endl;

		return stringstream.str();
	}
}