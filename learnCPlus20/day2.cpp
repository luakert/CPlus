#include <iostream>
#include <string>
#include <format>
#include <charconv>

using namespace std;

void test01()
{
    string s1{ "111" };
    string s2{ "121" };

    auto result{ s1 <=> s2 };
    if (is_lt(result))
    {
        cout << "s1 is less than" << endl;
    }

    if (is_gt(result))
    {
        cout << "s1 is greater than" << endl;
    }

    if (is_eq(result))
    {
        cout << "s1 is equal s2" << endl;
    }

    if (s1 == s2)
    {
        cout << " s1 == s2" << endl;
    }
    else
    {
        cout << " s1 != s2" << endl;
    }
}

void testliteral() {
    auto str1{ "hello"s};
    if (str1.find("o")!= string::npos)
    {
        cout << "find o" << endl;
    }
}

void testConversion()
{
    // string to number
    long double num{ 3.14L };
    string str1{ to_string(num) };
    cout << format("num string is {}", str1) << endl;

    const string strnum{ " 124USD" };
    size_t index{ 0 };
    int value{ stoi(strnum, &index) };
    cout << format("number is {}", value) << endl;
    cout << format("first non-parsed character {}", strnum[index]) << endl;

    const size_t buffersize{ 50 };
    string out( buffersize, ' ');
    auto result{ to_chars(out.data(), out.data() + out.size(), 1235) };
    if (result.ec == errc{}) { cout << out << endl; }
    else
    {
        cout << make_error_code(result.ec).message()<< endl;
    }

    string out2( buffersize, ' ' );
    auto [ptr, error] {to_chars(out2.data(), out2.data() + out2.size(), 3333)};
    if (error == errc{}) { cout << out2 << endl; }
    
    double valuedouble{ 3.2455 };
    string out3( buffersize, ' ' );
    auto [ptr2, error2] {to_chars(out3.data(), out3.data() + out3.size(), valuedouble)};
    if (error2 == errc{}) { cout << out3<< endl; }

    double value2;
    auto [prt3, error3] {from_chars(out3.data(), out3.data() + out.size(), value2)};
    if (error3 == errc{}) {
        if (value2 == valuedouble)
        {
            cout << "roundtrip" << endl;
        }
        else {
            cout << "trans fail" << endl;
        }
    }
}

string_view extractionString(string_view fileName)
{
    return fileName.substr(fileName.rfind('.'));
}

void testString_View()
{
    string filename{ R"(C:\temp\my file.txt)" };
    cout << format("C++ string {}", extractionString(filename)) << endl;

    const char* cString{ R"(C:\temp\my fileCstring.txt)" };
    cout << format("C string {}", extractionString(cString)) << endl;

    cout << format("Literal {}", extractionString(R"(C:\temp\my literal.txt)"))<< endl;

    const char* raw{ "hello. wo.rld!" };
    size_t length{ 20 };
    cout << format("string_view {}", string_view{ raw, length }) << endl;
    cout << format("Raw {}", extractionString({ raw, length })) << endl;
    cout << format("Raw string_view {}", extractionString(string_view{ raw, length })) << endl;
}

int* my_alloc(int value) { return new int{ value }; }

void my_free(int* p) { delete p; }

void testCustom()
{
    // 
    unique_ptr<int, decltype(&my_free )> myIntSmartptr{my_alloc(42), my_free};
    unique_ptr<string> myStr { new string{"aa"} };
}

void test06()
{
    auto a = make_unique<int>(6);
    int* b = a.get();
    cout << "value is " << *a << " b=" << *b << endl;

    a.reset();

    if (a == nullptr)
    {
        cout << "a alread is null ptr" << endl;
    }

    cout << " b=" << *b << endl;
}

void testShareAlias()
{
    class Foo
    {
    public:
        Foo(int value):m_value(value){}
        int m_value;
    };
    // 主要用于访问实例中的变量，避免实例被释放，增强对实例的控制
    auto foo{ make_shared<Foo>(1) };
    auto alias{ shared_ptr<int> {foo,&foo->m_value} };
    foo->m_value = 3;
    cout << "foo =" << foo->m_value << " alias=" << *alias<< endl;
}

int main22()
{
    //testConversion();
    // testString_View();
    // test06();
   // testShareAlias();
    system("pause");
    return 1;
}