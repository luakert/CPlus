#include <iostream>
#include <variant>
#include <string>
#

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

int main()
{
    test2401();
    system("pause");
    return 1;
}