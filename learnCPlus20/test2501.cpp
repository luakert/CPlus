import directed_cust_graph;
import directed_cust_graph.to_dot;
import <iostream>;
import <utility>;
import <algorithm>;
import <sstream>;
import <string>;

using namespace ProCustCpp;
using namespace std;

// Force all code to be compiled for testing.
template class directed_cust_graph<wstring>;

int main()
{
	directed_cust_graph<int> graph;
	// Insert some nodes and edges.
	graph.insert(11);
	graph.insert(22);
	graph.insert(33);
	graph.insert(44);
	graph.insert(55);
	graph.insert_edge(11, 33);
	graph.insert_edge(22, 33);
	graph.insert_edge(22, 44);
	graph.insert_edge(22, 55);
	graph.insert_edge(33, 44);
	graph.insert_edge(44, 55);
	wcout << to_dot(graph, L"Graph1");

	// Try to insert a duplicate, and use structured bindings for the result.
	auto [iter22, inserted] { graph.insert(22)};
	if (!inserted) { std::cout << "Duplicate element.\n"; }

	// Print nodes using a for loop and iterators.
	for (auto iter{ graph.cbegin() }; iter != graph.cend(); ++iter)
	{
		std::cout << *iter << " ";
	}
	std::cout << std::endl;

	// Print nodes using a for loop and iterators retrieved with the non-member
	// functions std::cbegin() and std::cend().
	for (auto iter{ std::cbegin(graph) }; iter != std::cend(graph); ++iter)
	{
		std::cout << *iter << " ";
	}
	std::cout << std::endl;

	// Print nodes using a range-based for loop.
	for (auto& node : graph)
	{
		std::cout << node << std::endl;
	}
	std::cout << std::endl;

	// Search a node using the std::find() Standard Library algorithm.
	auto result{ std::find(std::begin(graph), std::end(graph), 22) };
	if (result != std::end(graph))
	{
		std::cout << "Node 22 found." << std::endl;
	}
	else
	{
		std::cout << "Node 22 NOT found." << std::endl;
	}

	// Count all nodes with values > 22.
	auto count{ std::count_if(std::begin(graph), std::end(graph),
		[](const auto& node) { return node > 22; }) };

	// Use the iterator-based erase() method in combination with std::find().
	graph.erase(std::find(std::begin(graph), std::end(graph), 44));

	// Print nodes in reverse order.
	for (auto iter{ graph.rbegin() }; iter != graph.rend(); ++iter)
	{
		std::cout << *iter << " ";
	}
	std::cout << std::endl;

	// Test adjaceny lists.
	{
		std::cout << "Adjacency list for node 22: ";

		auto iterBegin{ graph.cbegin(22) };
		auto iterEnd{ graph.cend(22) };
		if (iterBegin == directed_cust_graph<int>::const_iterator_adjacent_nodes{})
		{
			std::cout << "Value 22 not found." << std::endl;
		}
		else
		{
			for (auto iter{ iterBegin }; iter != iterEnd; ++iter)
			{
				std::cout << *iter << " ";
			}
		}

		std::cout << std::endl;
	}



	// Remove an edge.
	graph.erase_edge(22, 44);

	{
		// Test begin()/end() non-const
		std::cout << "Nodes: ";
		for (auto iter{ graph.begin() }; iter != graph.end(); ++iter)
		{
			std::cout << *iter << " ";
		}
		std::cout << std::endl;
	}

	{
		// Test begin()/end() const
		std::cout << "Nodes: ";
		const auto& cgraph{ graph };
		for (auto iter{ cgraph.begin() }; iter != cgraph.end(); ++iter)
		{
			std::cout << *iter << " ";
		}
		std::cout << std::endl;
	}

	{
		// Test cbegin()/cend()
		std::cout << "Nodes: ";
		for (auto iter{ std::cbegin(graph) }; iter != std::cend(graph); ++iter)
		{
			std::cout << *iter << " ";
		}
		std::cout << std::endl;
	}

	{
		// Test rbegin()/rend()
		std::cout << "Nodes: ";
		for (auto iter{ graph.rbegin() }; iter != graph.rend(); ++iter)
		{
			std::cout << *iter << " ";
		}
		std::cout << std::endl;
	}

	{
		// Test begin(nodeValue)/end(nodeValue) non-const
		std::cout << "Adjacency list for node 22: ";
		auto iterEnd{ graph.end(22) };
		for (auto iter{ graph.begin(22) }; iter != iterEnd; ++iter)
		{
			std::cout << *iter << " ";
		}
		std::cout << std::endl;
	}

	{
		// Test begin(nodeValue)/end(nodeValue) const
		std::cout << "Adjacency list for node 22: ";
		const auto& cgraph{ graph };
		auto iterEnd{ cgraph.end(22) };
		for (auto iter{ cgraph.begin(22) }; iter != iterEnd; ++iter)
		{
			std::cout << *iter << " ";
		}
		std::cout << std::endl;
	}

	{
		// Test cbegin(nodeValue)/cend(nodeValue)
		std::cout << "Adjacency list for node 22: ";
		auto iterEnd{ graph.cend(22) };
		for (auto iter{ graph.cbegin(22) }; iter != iterEnd; ++iter)
		{
			std::cout << *iter << " ";
		}
		std::cout << std::endl;
	}

	{
		// Test crbegin(nodeValue)/crend(nodeValue)
		std::cout << "Adjacency list for node 22: ";
		auto iterEnd{ graph.crend(22) };
		for (auto iter{ graph.crbegin(22) }; iter != iterEnd; ++iter)
		{
			std::cout << *iter << " ";
		}
		std::cout << std::endl;
	}

	wcout << to_dot(graph, L"Graph1");

	// Query information of a graph.
	cout << "Size: " << graph.size() << endl;
	cout << "MaxSize: " << graph.max_size() << endl;
	cout << "IsEmpty?: " << graph.empty() << endl;

	// Test swapping graphs.
	directed_cust_graph<int> otherGraph;
	swap(graph, otherGraph);

	cout << "After swapping:" << endl;
	cout << "Size: " << graph.size() << endl;
	cout << "MaxSize: " << graph.max_size() << endl;
	cout << "IsEmpty?: " << graph.empty() << endl;

	// Test copying graphs.
	directed_cust_graph<int> graphCopy{ otherGraph };
	cout << "otherGraph == graphCopy? " << (otherGraph == graphCopy) << endl;

	graphCopy.erase(std::find(std::begin(graphCopy), std::end(graphCopy), 33));
	cout << "otherGraph == graphCopy? " << (otherGraph == graphCopy) << endl;

	// Find a node using std::find(), and erase the node.
	result = std::find(std::begin(graphCopy), std::end(graphCopy), 22);
	if (result != std::end(graphCopy))
	{
		cout << "Node 22 found." << endl;
		auto next{ graphCopy.erase(result) };
		if (next != std::end(graphCopy))
		{
			cout << "Next after erasing 22: " << *next << endl;
		}
	}
	else
	{
		cout << "Node 22 NOT found." << endl;
	}

	// Erase a range of nodes.
	result = std::find(std::begin(graphCopy), std::end(graphCopy), 55);
	auto result2{ std::find(std::begin(graphCopy), std::end(graphCopy), 33) };
	auto next = graphCopy.erase(result, result2);
	if (next != std::end(graphCopy))
	{
		cout << "Next after erasing range [55,33): " << *next << endl;
	}
	wcout << to_dot(graphCopy, L"Graph1");

	// Clear the graph.
	graph.clear();

	// Test equality.
	directed_cust_graph<int> graph1;
	graph1.insert(11);
	graph1.insert(22);
	graph1.insert(33);
	graph1.insert_edge(11, 22);
	graph1.insert_edge(11, 33);
	graph1.insert_edge(22, 33);

	directed_cust_graph<int> graph2;
	graph2.insert(22);
	graph2.insert(11);
	graph2.insert(33);
	graph2.insert_edge(22, 33);
	graph2.insert_edge(11, 22);
	graph2.insert_edge(11, 33);

	wcout << to_dot(graph1, L"graph1");
	wcout << to_dot(graph2, L"graph2");

	cout << "are equal: " << (graph1 == graph2) << endl;

	// Test assignment of graphs.
	directed_cust_graph<int> graph3;
	graph3 = graph2;
	wcout << to_dot(graph3, L"graph3");

	// Test a graph with strings.
	directed_cust_graph<wstring> graphStrings;
	graphStrings.insert(L"String 1");
	wstring str{ L"String 2" };
	graphStrings.insert(str);
	graphStrings.insert(L"String 3");
	graphStrings.insert(L"String 4");
	graphStrings.insert_edge(L"String 1", str);
	graphStrings.insert_edge(L"String 2", str);
	graphStrings.insert_edge(L"String 3", str);

	wcout << to_dot(graphStrings, L"String Graph") << endl;

	{
		// Test rbegin()/rend()
		std::cout << "Nodes: ";
		for (auto iter{ graphStrings.rbegin() }; iter != graphStrings.rend(); ++iter)
		{
			std::wcout << *iter << L" ";
		}
		std::cout << std::endl;
	}

	auto result3{ std::find(std::begin(graphStrings), std::end(graphStrings), L"String 3") };
	if (result3 != std::end(graphStrings)) {
		cout << "Node String 3 found." << endl;
	}
	else
	{
		cout << "Node String 3 NOT found." << endl;
	}

    system("pause");
}
