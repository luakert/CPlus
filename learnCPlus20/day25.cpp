import directed_graph;
import directed_graph.node;
import directed_graph.to_dot;
import <iostream>;
import <string>;

using namespace std;
using namespace ProCpp;

template class directed_graph<wstring>;

int main()
{
    // set<int> orginalSet{ 1, 6, 3, 7,2,5 };
    // for (const auto& value: orginalSet)
    // {
    //     cout << " " << value;
    // }
    // cout << endl;

    // auto iter = orginalSet.find(3);
    // cout << static_cast<int>(distance(cbegin(orginalSet), iter))<< endl;
    // orginalSet.erase(3);

    // for (const auto& value: orginalSet)
    // {
    //     cout << " " << value;
    // }
    // cout << endl;
    // cout << "vector value:" << endl;
    // vector<int> vect(begin(orginalSet), end(orginalSet));
    // for (const auto& value : vect)
    // {
    //     cout << " " << value;
    // }
    // cout << endl;

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