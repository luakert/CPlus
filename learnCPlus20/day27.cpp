#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>
#include <format>
#include <vector>

using namespace std;

std::atomic_flag spinlock = ATOMIC_FLAG_INIT;
static const size_t NumberofThread{ 50 };
static const size_t LoopsPerThread{ 100 };

void dowork(size_t threadNumber, vector<size_t>& data)
{
    for (size_t i = 0; i < LoopsPerThread; ++i)
    {
        while(spinlock.test_and_set()){}

        data.push_back(threadNumber);
        spinlock.clear();
    }
}

void test2701()
{
    vector<size_t> data;
    vector<thread> threads;
    for (size_t i = 0; i < NumberofThread; i++)
    {
        threads.push_back(thread{ dowork, i, ref(data) });
    }

    for (auto& t :threads)
    {
        t.join();
    }

    cout << format("data contains {} elements expected{}.\n", data.size(), NumberofThread * LoopsPerThread);
}

int main()
{
    test2701();
    system("pause");
}