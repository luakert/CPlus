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

    int theInt{ static_cast<int>(anInt) };
    cout << theInt << endl;

    try
    {
        int test{ static_cast<int>(anString) };
    }
    catch (const bad_any_cast& ex)
    {
        cout << ex.what() << endl;
    }

    using MyTuple = tuple<int, string, bool>;
    MyTuple t1{ 16, "Test"s, false };
    cout << format("t1 =({}, {}, {})", get<0>(t1), get<1>(t1), get<2>(t1)) << endl;

}

int main()
{
    test2401();
    system("pause");
    return 1;
}