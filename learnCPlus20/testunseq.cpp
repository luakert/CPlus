#include <time.h>
import <vector>;
import <algorithm>;
import <execution>;
import <numeric>;
import <random>;
import <iostream>;
import <chrono>;

using namespace std;

int mainTest()
{
    std::vector<int> vec1(10000);
    std::vector<int> vec2(10000);

    std::iota(begin(vec1), end(vec1), 1);

    std::random_device seeder;
    // std::time_t t = std::time(nullptr);
    const auto seed{ seeder.entropy() ? seeder() : time(nullptr)};
    std::default_random_engine engine{ static_cast<std::default_random_engine::result_type>(seed) };
    // for (const auto& val : vec1)
    // {
    //     cout << val << " ";
    // }
    // cout << endl;
    
    std::shuffle(std::begin(vec1), std::end(vec1), engine);
    // for (const auto& val : vec1)
    // {
    //     cout << val << " ";
    // }
    // cout << endl;
    vec2 = vec1;
    auto start{ chrono::system_clock::now() };
    sort(begin(vec1), end(vec1));
    auto end { chrono::system_clock::now() };
    cout << " cost1 =" << chrono::duration<double, milli>{end - start}.count() << endl;

    auto start2 { chrono::system_clock::now() };
    sort(execution::par_unseq, vec2.begin(), vec2.end());
    auto end2 { chrono::system_clock::now() };
    cout << " cost2 =" << chrono::duration<double, milli>{end2 - start2}.count() << endl;

    if (is_sorted(cbegin(vec1), cend(vec1)))
    {
        cout << " vec1 is sorted" << endl;
    }

    if (is_sorted(cbegin(vec2), cend(vec2)))
    {
        cout << " vec2 is sorted" << endl;
    }

    system("pause");
    return 0;
}