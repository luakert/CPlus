#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

template<typename T>
void test2001(vector<T>& vec, const T& t)
{
    auto end{ cbegin(vec) + 3 };
    if (auto it {find(cbegin(vec), end, t)}; it != end )
    {
        cout << " find vlaue " << t << endl;
    }
    else
    {
        cout << "not find value " << t << endl;
    }
}

void test2003()
{
    vector<int> vec{ 1, 3, 4, 5,6, 7 };
    test2001(vec, 3);
    test2001(vec, 5);
}

void test2002()
{
    vector<int> myVector;
    while (true)
    {
        cout << "Enter a number to add (0 to stop):";
        int number;
        cin >> number;
        if (number == 0)
        {
            break;
        }

        myVector.push_back(number);
    }

    while (true)
    {
        if (myVector.size() == 0)
        {
            cout << "no vlaue input " << endl;
            break;
        }

        cout << "Enter a number to check (0 to stop):";
        int number;
        cin >> number;
        if (number == 0)
        {
            break;
        }

        auto end{ cbegin(myVector) + 5 };
        //auto begin{ cbegin(myVector) };
        auto it{ find(cbegin(myVector), end, number) };
        if (it == end)
        {
            cout << "not find " << number << endl;
        }
        else {
            cout << "found value " << number << endl;
        }
    }
}

void test2004()
{
    vector<int> myVector;
    while (true)
    {
        cout << "Enter a number to add (0 to stop):";
        int number;
        cin >> number;
        if (number == 0)
        {
            break;
        }

        myVector.push_back(number);
    }

    auto end{ cend(myVector) };
    if (auto it {find_if(cbegin(myVector), end, [](int value){return value >= 100;})}; it != end)
    {
        cout << "find perfect number" << *it << endl;
    }
    else
    {
        cout << "not find number" << endl;
    }

    auto isPerfect{ [totally = 0](int value) mutable {
        cout << ++totally << endl;
        return value >= 100;
    } };

    auto result{ find_if(cbegin(myVector),end, isPerfect) };
    if (result != end)
    {
        cout << "found number " << *result << endl;
    }
    // isPerfect(1);

    auto result2{ find_if(cbegin(myVector),end, ref(isPerfect)) };
    if (result2 != end)
    {
        cout << "found number " << *result2 << endl;
    }
    isPerfect(1);
}

int main()
{
    test2004();
    system("pause");
}