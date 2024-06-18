#include <time.h>
#include <iostream>
#include <format>
#include <string>
#include <ratio>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace chrono;

void test2201()
{
    using r = ratio<1, 60>;
    intmax_t num{ r::num };
    intmax_t den{ r::den };

    using r2 = ratio<1, 30>;
    using result = ratio_add<r, r2>::type;
    cout << format("result={}/{}", result::num, result::den) << endl;

    using res = ratio_less<r, r2>;
    cout << format("r compareto r2 ={}", res::value) << endl;

    duration<long, ratio<60>> d1 {123};
    cout << d1.count() << endl;

    auto d2{ duration<double>::max() };
    cout << d2.count() << endl;

    using r3 = ratio<60>;
    cout << "num=" << r3::num << " den=" << r3::den << endl;

    duration<long, ratio<60>> d3{ 10 };
    duration<long, ratio<1>> d4{ 13 };

    if (d3 > d4)
    {
        cout << "d3 > d4" << endl;
    }

    ++d4;
    d4 *= 2;

    duration<long> d5{ d3 + d4 };
    cout << "seconds d3 + d4= " << d5.count() << endl;

    duration<long> d6{ 30 };
    duration<double, ratio<60>> d7 { d6 };
    cout << "d7=" << d7.count() << endl;

    minutes d9{ 10 };
   // cout << format("d9 = {} secondes", typeid(d9).raw_name()) << endl;

    auto t{ hours{1} + minutes{2} + seconds{4} };
    cout << "seconds=" << seconds{ t }.count() << endl;

    //  trans error
    // seconds se{ 60 };
    // minutes mim{ s };

    minutes min2{ 1 };
    seconds se{ min2 };
    cout << "transform result= " << se.count() << endl;

    // using literals
    auto liter{ 10min };
    cout << "literals =" << minutes{ liter }.count() << endl;
}

void test2202()
{
    system_clock::time_point tpoint{ system_clock::now() };
    time_t tt{ system_clock::to_time_t(tpoint) };

    cout << tpoint << endl;
    stringstream formatStr;
    formatStr << tpoint;
    string afterFormatStr{ formatStr.str() };
    string_view sv{ afterFormatStr };
    cout << sv.substr(0, 22) << endl;

    // tm* t{ localtime_s(&tt) };
    tm t;
    errno_t err = localtime_s(&t, &tt);
    cout << put_time(&t, "%H:%M:%S") << endl;

    stringstream ss;
    ss << put_time(&t, "%H:%M:%S");
    string timeStr{ ss.str() };
    cout << timeStr << endl;
}

void test2203()
{
    system_clock::time_point tpoint;
    // cout << duration<long, seconds> {tpoint}.count() << endl;
    tpoint += minutes{ 10 };
    auto d1{ tpoint.time_since_epoch() };
    duration<double> d2{ d1 };
    cout << " seconds=" << d2.count() << endl;

    auto today { floor<days>(system_clock::now()) };
    cout << today << endl;
    year_month_day ymd{ today };
    cout << ymd.year() << endl;
    // year_month_day ymd{ today };
   //  cout << ymd << endl;
   // using date::operator<<;
    //cout << int(today.) << endl;
    // cout << today.year() << endl;
    // year_month_day ymd = today;
    // cout << ymd.year() << endl;

    system_clock::time_point t1{ sys_days{2020y / June / 22d} };

    year_month_day yearmonthday{ floor<days>(t1) };
    year_month_day today2{ floor<days>(system_clock::now()) };
    cout << today2 << endl;

}


int main22()
{
    test2203();
    system("pause");
    return 0;
}