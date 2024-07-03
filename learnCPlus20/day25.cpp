import directed_graph;
import directed_graph.to_dot;
import directed_graph.node;
import <iostream>;
import <sstream>;
import <string>;

using namespace ProCpp;
using namespace std;

// Force all code to be compiled for testing.
template class directed_graph<wstring>;

int main()
{
	directed_graph<int> graph;
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

	// Remove an edge and a node.
	graph.erase_edge(22, 44);
	graph.erase(44);
	wcout << to_dot(graph, L"Graph1");

	// Print the size of the graph.
	cout << "Size: " << graph.size() << endl;

	// Test swapping graphs.
	directed_graph<int> otherGraph;
	otherGraph.swap(graph);

	cout << "After swapping:" << endl;
	cout << "Size: " << graph.size() << endl;

	// Test copying graphs.
	directed_graph<int> graphCopy{ otherGraph };
	cout << "otherGraph == graphCopy? " << (otherGraph == graphCopy) << endl;

	graphCopy.erase(33);
	cout << "otherGraph == graphCopy? " << (otherGraph == graphCopy) << endl;

	// Test equality
	directed_graph<int> graph1;
	graph1.insert(11);
	graph1.insert(22);
	graph1.insert(33);
	graph1.insert_edge(11, 22);
	graph1.insert_edge(11, 33);
	graph1.insert_edge(22, 33);

	directed_graph<int> graph2;
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
	directed_graph<int> graph3;
	graph3 = graph2;
	wcout << to_dot(graph3, L"graph3");

	// Test a graph with strings.
	directed_graph<wstring> graphStrings;
	graphStrings.insert(L"String 1");
	wstring str{ L"String 2" };
	graphStrings.insert(str);
	graphStrings.insert(L"String 3");
	graphStrings.insert(L"String 4");
	graphStrings.insert_edge(L"String 1", str);
	graphStrings.insert_edge(L"String 2", str);
	graphStrings.insert_edge(L"String 3", str);

	wcout << to_dot(graphStrings, L"String Graph") << endl;
    system("pause");
    return 0;
}