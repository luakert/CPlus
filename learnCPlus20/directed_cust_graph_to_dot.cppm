export module directed_cust_graph.to_dot;

import directed_cust_graph;
import <string>;
import <string_view>;
import <sstream>;
import <format>;

export namespace ProCustCpp
{

	// Returns a given graph in DOT format.
	export
	template <typename T>
	std::wstring to_dot(const directed_cust_graph<T>& graph, std::wstring_view graph_name)
	{
		std::wstringstream wss;

		wss << std::format(L"digraph {} {{", graph_name.data()) << std::endl;
		for (auto&& node : graph)
		{
			const auto b{ graph.cbegin(node) };
			const auto e{ graph.cend(node) };
			if (b == e)
			{
				wss << node << std::endl;
			}
			else
			{
				for (auto iter{ b }; iter != e; ++iter)
				{
					wss << std::format(L"{} -> {}", node, *iter) << std::endl;
				}
			}
		}
		wss << "}" << std::endl;

		return wss.str();
	}

}