import directed_graph;
import directed_graph.node;
import directed_graph.to_dot;
import <iostream>;
import <sstream>;
import <string>;

using namespace std;
using namespace ProCpp;

template class directed_graph<wstring>;

int main()
{
    directed_graph<int> graph;
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

    system("pause");
    return 0;

}