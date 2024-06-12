#include <algorithm>
#include <iostream>
#include <numeric>
#include <random>
#include <time.h>
#include <vector>
#include <map>
#include <execution>
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
    MyCopyTestClass(string str):m_str(move(str)){}
    virtual ~MyCopyTestClass() = default;

    MyCopyTestClass& operator=(MyCopyTestClass&& rhs)noexcept {
        if (this == &rhs)
        {
            return *this;
        }

        m_str = move(rhs.m_str);
        cout << "move operator= " << m_str << endl;
        return *this;
    }

    void setString(string str) { m_str = move(str); }
    const string& getString() const { return m_str; }
};

void test2007()
{
    vector<MyCopyTestClass> vecstr{ MyCopyTestClass{"a"}, MyCopyTestClass{"b"},MyCopyTestClass("C") };
    vector<MyCopyTestClass> vecDest(vecstr.size());
    move(begin(vecstr), end(vecstr), begin(vecDest));
    for (const auto& val : vecDest)
    {
        cout << val.getString() << " ";
    }
    cout << endl;
}

void removeElements(vector<string>& strings)
{
    auto it{ remove(begin(strings), end(strings), "") };
    strings.erase(it, end(strings));
}

void test2008()
{
    map<int, int> myMap{ {4, 10}, {5,12}, {1,5} };
    for_each(cbegin(myMap), cend(myMap), [](const auto& p) {
        cout << p.first << "->" << p.second << endl;
        });

    vector<int> myVec;
    populateContainer(myVec);

    int sum{ 0 };
    int product{ 1 };
    for_each(cbegin(myVec), cend(myVec), [&sum, &product](int val) {
        sum += val;
        product *= val;

    });

    cout << " sum=" << sum << endl;
    cout << "product =" << product << endl;
}

class SumAndProduct
{
private:
    int m_sum{ 0 };
    int m_product{ 1 };
public:
    void operator()(int value)
    {
        m_sum += value;
        m_product *= value;
    }

    int getSum() const { return m_sum; }
    int getProduct() const { return m_product; }
};

void test2009()
{
    vector<int> myVec;
    populateContainer(myVec);

    SumAndProduct sap;
    sap = for_each(cbegin(myVec), cend(myVec), sap);
    cout << " sum =" << sap.getSum() << endl;
    cout << " product=" << sap.getProduct() << endl;
}

void test2010()
{
    vector<int> vec1;
    vector<int> vecOdd;
    vector<int> vecEven;

    populateContainer(vec1);
    vecOdd.resize(vec1.size());
    vecEven.resize(vec1.size());

    auto pairIter{ partition_copy(cbegin(vec1), cend(vec1), begin(vecEven), begin(vecOdd),[](int value) {
            return value % 2 == 0;
    }) };

    vecOdd.erase(pairIter.second, end(vecOdd));
    vecEven.erase(pairIter.first, end(vecEven));

    cout << "Evnt number" << endl;
    for (const auto& evenValue: vecEven)
    {
        cout << evenValue << " ";
    }
    cout << endl;

    cout << "Odd number" << endl;
    for (const auto& evenValue: vecOdd)
    {
        cout << evenValue << " ";
    }
    cout << endl;

    partition(begin(vec1), end(vec1), [](int value)
        {
            return value % 2 == 0;
        }
    );

    for (const auto& value : vec1)
    {
        cout << value << " ";
    }
    cout << endl;
}

void test2011()
{
    vector<int> myVec;
    populateContainer(myVec);
    sort(begin(myVec), end(myVec), greater<>());
    for (const auto& value : myVec)
    {
        cout << value << " ";
    }
    cout << endl;

    //random_device seeder;
   // // time t{ time(nullptr) };
//    const auto seed{ seeder.entropy() ? seeder() : time(nullptr)};
   // default_random_engine engine{ static_cast<default_random_engine::result_type>(seed) };
   // shuffle(begin(myVec), end(myVec), engine);

    vector<int> vec2;
    populateContainer(vec2);
    nth_element(begin(vec2), begin(vec2) + 2, end(vec2), greater<>());
    cout << vec2[2] << endl;  

    for (const auto& value : vec2)
    {
        cout << value << " ";
    }
    cout << endl;
}

void test2012()
{
    vector<int> myVec;
    populateContainer(myVec);

    nth_element(begin(myVec), begin(myVec) + 5, end(myVec), greater<>());
    for (const auto& value : myVec)
    {
        cout << value << " ";
    }
    cout << endl;

    sort(begin(myVec), begin(myVec) + 5);
    for_each_n(begin(myVec), 5, [](const auto& ele) {cout << ele << " "; });
}

void test2013()
{
    vector vec{ 1, 4, 2,5, 6,0 };
    sort(execution::par, begin(vec), end(vec));
    for (const auto& va : vec)
    {
        cout << va << " ";
    }
    cout << endl;

    vector<int> vec1(1000);
    vector<int> vec2(1000);

    iota(begin(vec1), end(vec1), 1);
    vec2 = vec1;

}

int main20()
{
    test2013();
    system("pause");
    return 0;
}