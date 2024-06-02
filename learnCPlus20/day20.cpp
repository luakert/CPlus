#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
#include <utility>

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

template<typename container>
void populateContainer(container& con)
{
    while (true)
    {
        cout << "Enter number ";
        int number;
        cin >> number;
        if (number == 0)
        {
            break;
        }
        con.push_back(number);
    }
}

void test2005()
{
    vector vec{ 6, 5, 4, 4, 7, 2, 9 };
    auto beginIter{ begin(vec) };
    auto endIter{ end(vec) };

    auto it{ find_if_not(beginIter, endIter, [](int a) {return a < 8;}) };
    if (it != endIter)
    {
        cout << "First element not < 8 is " << *it << endl;
    }

    it = adjacent_find(beginIter, endIter);
    if (it != endIter)
    {
        cout << "Found tow consecutive equal elements with value" << *it << endl;
    }

    vector targets{ 4, 7 };
    it = find_first_of(beginIter, endIter, cbegin(targets), cend(targets));
    if (it != endIter)
    {
        cout << "Found one of 4, or 7 " << *it << endl;
    }

    vector sub{ 2, 9 };
    it = search(beginIter, endIter, cbegin(sub), cend(sub));
    if (it != endIter)
    {
        cout << "Found sub 2, 9" << endl;
    }
    else {
        cout << "unable to find sub 2,9" << endl;
    }

    it = search_n(beginIter, endIter, 2, 8);
    if (it != endIter)
    {
        cout << "Found two 8 " << endl;
    }
    else
    {
        cout << "unable to find two 8" << endl;
    }
}

void test2006()
{
    vector<int> vec(10);
    int value{ 1 };
    generate(begin(vec), end(vec), [&value] { value *= 2; return value; });
    for (auto val : vec)
    {

        cout << val << " ";
    }
    cout << endl;

    vector<int> myVec;
    populateContainer(myVec);
    for (const auto& value: myVec)
    {
        cout << value << " ";
    }
    cout << endl;

    transform(begin(myVec), end(myVec), begin(myVec), [](int i) {return i + 100; });
    for (const auto& value : myVec)
    {
        cout << value << " ";
    }
    cout << endl;

    vector<int> vec2, vec3;
    populateContainer(vec2);
    vec3.resize(vec2.size());

    copy(cbegin(vec2), cend(vec2), begin(vec3));
    for (const auto& value : vec3)
    {
        cout << value << endl;
    }

    vector<int> vec4;
    size_t tally{ 0 };
    cout << "Enter number of  elements  copy ";
    cin >> tally;
    tally = min(tally, vec2.size());
    vec4.resize(tally);
    copy_n(begin(vec2), tally, begin(vec4));
    for (auto& val:vec4)
    {
        cout << val << " ";
    }
    cout << endl;
}

class MyCopyTestClass
{
private:
    string m_str;
public:
    MyCopyTestClass() = default;
    MyCopyTestClass(const MyCopyTestClass& src) = default;
    MMyCopyTestClass(string str):m_str(str){}
    virtual ~MyCopyTestClass() = default;

    MyCopyTestClass& operator=(MyCopyTestClass&& rhs)noexcept {
        if (this == &rhs)
        {
            return *this;
        }

        m_str == move(rhs.m_str);
        cout << "move operator= " << m_str << endl;
        return *this;
    }

    void setString(string str) { m_str = move(str); }
    const string& getString() { return m_str; }
};

void test2007()
{
    vector<MyCopyTestClass> vecstr{ MyCopyTestClass{"a"}, MyCopyTestClass{"b"},MyCopyTestClass("C") }


}

int main()
{
    test2006();
    system("pause");
}