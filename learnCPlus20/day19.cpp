#include <iostream>
#include <unorder_set>
#include <span>
#include <format>
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

int main()
{
    test1903();
    system("pause");
}