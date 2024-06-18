#include <time.h>
#include <string>
#include <functional>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <random>
#include <vector>
#include <map>

using namespace std;

void test2301()
{
    random_device rd;
    cout << "Entropy " << rd.entropy() << endl;
    cout << " Min Value=" << rd.min() << " Max value =" << rd.max() << endl;
    cout << "Random number=" << rd() << endl;
}

void test2302()
{
    random_device rnd;
    const auto seeder{ rnd.entropy() ? rnd() : time(nullptr) };
    mt19937 engine{ static_cast<mt19937::result_type>(seeder) };
    uniform_int_distribution<int> distribution{ 1, 1000 };
    cout << distribution(engine) << endl;


}

void test2303()
{
    random_device rnd;
    const auto seeder{ rnd.entropy() ? rnd() : time(nullptr) };
    mt19937 engine{ static_cast<mt19937::result_type>(seeder) };
    uniform_int_distribution<int> distribution{ 1, 1000 };

    auto generator{ bind(distribution, engine) };
    vector<int> values(10);
    generate(begin(values), end(values), generator);
    for (auto value: values)
    {
        cout << value << " ";
    }
    cout << endl;
}

void fillVector(vector<int>& vec, const std::function<int()>& generator)
{
    generate(begin(vec), end(vec), generator);
}

template<typename T>
void fillVector(vector<int>& values, const T& generator)
{
    generate(begin(values), end(values), generator);
}

void test2304()
{
    const unsigned int START{ 1 };
    const unsigned int END { 99 };
    const unsigned int ITERATIONS { 1'000'000};

    random_device rnd;
    const auto seeder{ rnd.entropy() ? rnd() : time(nullptr) };
    mt19937 engine{ static_cast<mt19937::result_type>(seeder) };
    uniform_int_distribution<int> distribution{ START, END };
    auto generator{ bind(distribution, engine) };
    map<int, int> histogram;
    for (unsigned int i {0}; i< ITERATIONS; ++i)
    {
        int randomNumber{ generator() };
        ++(histogram[randomNumber]);
    }

    ofstream of{ "res.csv" };
    for (unsigned int i {START}; i< END; ++i)
    {
        of << i << "," << histogram[i] << endl;
    }
}

int main()
{
    test2304();
    system("pause");
    return 0;
}