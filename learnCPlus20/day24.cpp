#include <iostream>
#include <variant>
#include <utility>
#include <string>
#include <format>
#include <any>

using namespace std;

void test2401()
{
    variant<int, string, float> v;
    v = 12;
    v = "12"s;
    v = 12.5f;

    cout << "Type index " << v.index() << endl;
    cout << "Contains int " << holds_alternative<int>(v) << endl;

    cout << get<float>(v) << endl;

    try
    {
        cout << get<0>(v) << endl;
    }
    catch (const bad_variant_access& ex)
    {
        cout << ex.what() << endl;
    }

    cout << "Type index " << v.index() << endl;
    float* thefloat{ get_if<float>(&v) };
    string* theString{ std::get_if<string>(&v) };
    int* theInt{ std::get_if<int>(&v) };
    cout << "float=" << (thefloat ? *thefloat : 0.0) << endl;
    cout << "retrieved string " << (theString ? *theString : "null") << endl;
    cout << "retrieved int " << (theInt ? *theInt : 0) << endl;
}

void test2402()
{
    any empty;
    any anInt{ 3 };
    any anString{ "An std::string"s };

    cout << "empty has value " << empty.has_value() << endl;
    cout << "anInt has value " << anInt.has_value() << endl;

    int theInt{ any_cast<int>(anInt) };
    cout << theInt << endl;

    try
    {
        int test{ any_cast<int>(anString) };
    }
    catch (const bad_any_cast& ex)
    {
        cout << ex.what() << endl;
    }

    using MyTuple = tuple<int, string, bool>;
    MyTuple t1{ 16, "Test"s, false };
    cout << format("t1 =({}, {}, {})", get<0>(t1), get<1>(t1), get<2>(t1)) << endl;
    cout << "type of t1 " << typeid(get<1>(t1)).name() << endl;

    cout << "Tuple size=" << tuple_size<MyTuple>::value << endl;

    cout << "Tuple type=" << typeid(tuple_element<2, MyTuple>::type).name() << endl;

    tuple<int, string, bool> t2 {16, "Test"s, false };
    auto [i, str1, boolvalue] {t2};
    cout << " i=" << i << " t2=" << str1 << " boolean=" << boolvalue << endl;

    int a{ 0 };
    string str;
    bool b;
    cout << format("before i ={}, str={}, b=", a, str, b) << endl;
    tie(a, str, b) = t1;
    cout << format("After i={}, str={}, b={}", a, str, b) << endl;
}

int main()
{
    test2402();
    system("pause");
    return 1;
}