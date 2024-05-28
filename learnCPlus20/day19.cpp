#include <iostream>
#include <unordered_set>
#include <span>
#include <format>
#include <functional>
#include <string_view>
#include <vector>
#include <cmath>
#include <set>

using namespace std;

using Matcher = bool(*)(int, int);
using MatcherHandler = void(*)(size_t, int, int);

void findMatcher(span<const int> values1, span<const int> values2, auto mathcer, auto handler)
{
    if (values1.size() != values2.size())
    {
        return;
    }

    for (size_t i = 0; i < values1.size(); i++)
    {
        if (mathcer(values1[i], values2[i]))
        {
            handler(i, values1[i], values2[i]);
        }
    }
}

bool intEqual(int one, int two)
{
    return one == two;
}

void printMatch(size_t postion, int values, int valuse2)
{
    cout << format(" task={}, {}, {}", postion, values, valuse2) << endl;
}

void test1901()
{
    vector v2{ 1, 2, 3, 4, 5, 6, 4};
    vector v3{ 3, 2, 6, 7, 2, 5, 4};

    findMatcher(v2, v3, intEqual, printMatch);
}

class IsLargerThan
{
private:
    int m_value;
public:
    explicit IsLargerThan(int value):m_value{value}{}
    bool operator()(int value, int value2) const
    {
        return value > m_value && value2 > m_value;
    }
};

void test1902()
{
    vector v1{ 2, 500, 6, 100, 101 };
    vector v2{ 102, 501, 6, 99, 101 };
    findMatcher(v1, v2, IsLargerThan{ 100 }, printMatch);
}

template<typename Iter, typename StartValue, typename Operation>
auto accumulateData(Iter begin, Iter end, StartValue start, Operation op)
{
    auto accumulated{ start };
    for (Iter it {begin}; it != end; ++it)
    {
        accumulated = op(accumulated, *it);
    }

    return accumulated;
}

double geometricMean(span<const int> values)
{
    auto mult{ accumulateData(cbegin(values), cend(values), 1, multiplies<>{}) };
    return pow(mult, 1.0 / values.size());
}

void test1903()
{
    vector<int> valuse{ 1, 2, 3 };
    double result{ accumulateData(cbegin(valuse), cend(valuse), 1.1, multiplies<>{}) };
    cout << result << endl;
}

class Hasher
{
public:
    using is_transparent = void;
    size_t operator()(string_view sv) const
    {
        return hash<string_view>{}(sv);
    }
};

void test1904()
{
    unordered_set<string, Hasher, equal_to<>> mySet;
    auto res1{ mySet.find("Kye") };
}

void func(int number, string_view sv)
{
    cout << format("func({}, {})", number, sv) << endl;
}

void increment(int& value)
{
    ++value;
}

void overloaded(int value) { cout << "int par " << value << endl; }
void overloaded(double value) { cout << "double par" << value << endl; }

class Handler
{
public:
    void handleMatch(size_t position, int vlaue, int value2)
    {
        cout << format("Match found at position {} ({}, {})", position, vlaue, value2) << endl;
    }
};

template<typename Matcher>
void printMatchString(const vector<string>& strings, Matcher matcher)
{
    for (const auto& str : strings)
    {
        if (matcher(str))
        {
            cout << str << "+=";
        }
    }
    cout << endl;
}

void test1905()
{
    string myString{ "abc" };
    auto f1{ bind(func, placeholders::_1, myString) };
    f1(16);

    auto f2{ bind(func, placeholders::_2, placeholders::_1) };
    f2("Test", 12);

    int index{ 0 };
    increment(index);
    cout << "after increment value=" << index << endl;

    auto incr{ bind(increment, index) };
    incr();
    cout << "after bind increment value=" << index << endl;

    auto incrref{ bind(increment, ref(index)) };
    incrref();
    cout << "after ref increment value=" << index << endl;

    auto f4{ bind((void(*)(double))overloaded, placeholders::_1) };
    f4(1.1f);

    auto f5{ bind((void(*)(int))overloaded, placeholders::_1) };
    f5(12);

    Handler handler;
    vector v1{ 2, 500, 6, 100, 101 };
    vector v2{ 102, 501, 6, 99, 101 };
    findMatcher(v1, v2, intEqual, bind(&Handler::handleMatch, &handler, placeholders::_1, placeholders::_2,
        placeholders::_3));

    auto  greaterEqualTo100{ bind(greater_equal<>{}, placeholders::_1, 100) };
   // auto result22 = greaterEqualTo100(103);
   // cout << typeid(result22).raw_name() << endl;
    findMatcher(v1, v2, greaterEqualTo100, printMatch);

    vector<string> vecstr{ "Hello", "", "", "world", " ", " this test" };
    // printMatchString(vecstr, not_fn(mem_fn(&string::empty)));
    printMatchString(vecstr,(mem_fn(&string::empty)));
}

int main()
{
    test1905();
    system("pause");
}