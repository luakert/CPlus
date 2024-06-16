#include <iostream>
#include <locale>
#include <regex>
#include <string>
#include <format>

using namespace std;

void test2101()
{
    const char8_t* s1{ u8R"(Raw UTF-8 encoded string literal)" };
    const wchar_t* s2{ LR"(Raw UTF-8 encoded string literal)" };
    const char16_t* s3{ uR"(Raw UTF-16 encoded string literal)" };
    const char32_t* s4{ UR"(Raw UTF-32 encoded string literal)" };

    // cout << s1 << " " << *s2 << " " << *s3 << " " << *s4 << endl;
    wcout << s2 << endl;

    const char8_t* fomula{ u8"\u03c0 r\u00B2" };
    string str(reinterpret_cast<const char*>(fomula));
    cout << str << endl;
    wcout.imbue(locale{ "" });
    wcout << 32322 << endl;

    cout.imbue(locale{ "zh_TW" });
    cout << 3222222 << endl;

    auto upper{ toupper('a', locale{"en-US"})};
    cout << upper << endl;

    locale uslocal{ "en-US" };
    locale cnlocal{ "zh-CN" };

   // const wchar_t* time2{ LR "(2022/2/23)" };
   // wstring usmoney{ use_facet<moneypunct<wchar_t>>(uslocal).curr_symbol() };
   // wstring cnmoney { use_facet<time_get<wchar_t>>(cnlocal).get_year(time2)};
    
    //wcout << L"In the us money symbol is " << usmoney << endl;
    //wcout << L"In the china money symbol is " << cnmoney << endl;
}

void test2102()
{
    regex pattern{ R"((\d{4})/(0?[1-9]|1[0-2])/(0?[1-9]|[1-2][0-9]|3[0-1]))" };
    while (true)
    {
        cout << " enter a data year/month/day q=quit: ";
        string str;
        if (!getline(cin, str) || str =="q")
        {
            break;
        }

        if (smatch m; regex_match(str, m, pattern))
        {
            int year {stoi(m[1])};
            int month {stoi(m[2])};
            int day {stoi(m[3])};
            cout << format(" valid date Year={}, month={}, day={}", year, month, day)<<endl;
        }
        else {
            cout << "input invalid date" << endl;
        }
    }
}

void test2103()
{
    regex pattern{ R"(//\s*(.+)$)" };
    while (true)
    {
        cout << " input a string with optional code comments //: ";
        string str;
        if (!getline(cin, str)|| str=="q")
        {
            break;
        }

        if (smatch result; regex_search(str, result, pattern))
        {
            cout << format(" Found comment '{}'", result[1].str()) << endl;
            // 这里可以更新查到的位置
            // cout << " first " << *result[1].first << " second=" << *result[1].second << endl;
        }
        else {
            cout << "not found comment " << endl;
        }
    }
}

void test2104()
{
    regex pattern{ R"(\w+)" };
    while (true)
    {
        cout << "Enter a world: ";
        string str;
        if (!getline(cin, str) || str =="q")
        {
            break;
        }

        const sregex_iterator end;
        for (sregex_iterator iter {cbegin(str), cend(str), pattern}; iter!=end; ++iter)
        {
            cout << format(R"("{}")", (*iter)[0].str()) << endl;
        }
    }
}

void test2105()
{
    regex pattern{ R"(^(\d{4})/(0?[1-9]|1[0-2])/(0?[1-9]|[1-2][0-9]|3[0-1])$)" };
    while (true)
    {
        cout << "Enter a world: ";
        string str;
        if (!getline(cin, str) || str =="q")
        {
            break;
        }

        const sregex_token_iterator end;
        vector<int> indices{ 2, 3 };
        for (sregex_token_iterator iter {cbegin(str), cend(str), pattern, indices}; iter != end; ++iter)
        {
            cout << iter->str() << endl;
        }
    }

}

void test2107()
{
    regex pattern{ R"(\s*[,;]\s*)" };
    while (true)
    {
        cout << "Enter a world: ";
        string str;
        if (!getline(cin, str) || str == "q")
        {
            break;
        }

        const sregex_token_iterator end;
        for (sregex_token_iterator iter{ cbegin(str), cend(str), pattern, -1 }; iter != end; ++iter)
        {
            cout << iter->str() << endl;
        }
    }
}

void test2108()
{
    const string str{ "<body><h1>Header</h1><p>Some text</p></body>" };
    regex r{ "<h1>(.*)</h1><p>(.*)</p>" };

    const string replacement{ "H1=$1 and P=$2" };
    string result{ regex_replace(str, r, replacement) };

    cout << format("Original string: '{}'", str) << endl;
	cout << format("New string     : '{}'", result) << endl;

    string resultNotContain{ regex_replace(str, r, replacement, regex_constants::format_no_copy) };
	cout << format("New string     : '{}'", resultNotContain) << endl;
}

void test2109()
{
    regex pattern{ R"((\w+))" };
    const string replacement{ "$1\n" };
    while (true)
    {
        cout << " enter wordl: ";
        string str{"this is how"};
        if (!getline(cin, str) || str == "q")
        {
            cout << "enter error or quit" << endl;
            break;
        }

        cout << regex_replace(str, pattern, replacement, regex_constants::format_no_copy) << endl;
    }
}

void test2120()
{
    regex r{ R"(^(.*?)//.*$)" };
    const string replacement{ "$1" };
    while (true)
    {
        cout << "enter code:";
        string str;
        if (!getline(cin, str, '@'))
        {
            break;
        }
        cout << regex_replace(str, r, replacement) << endl;
    }
}

int main21()
{
    test2120();
    system("pause");
    return 0;
}