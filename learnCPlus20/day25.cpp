#include <set>;
#include <iostream>
#include <vector>;

using namespace std;

int main()
{
    set<int> orginalSet{ 1, 6, 3, 7,2,5 };
    for (const auto& value: orginalSet)
    {
        cout << " " << value;
    }
    cout << endl;

    auto iter = orginalSet.find(3);
    cout << static_cast<int>(distance(cbegin(orginalSet), iter))<< endl;
    orginalSet.erase(3);

    for (const auto& value: orginalSet)
    {
        cout << " " << value;
    }
    cout << endl;
    cout << "vector value:" << endl;
    vector<int> vect(begin(orginalSet), end(orginalSet));
    for (const auto& value : vect)
    {
        cout << " " << value;
    }
    cout << endl;

    system("pause");
    return 0;

}